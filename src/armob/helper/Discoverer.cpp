/*
 * File: Discoverer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Discoverer.h"

#include <asm/arm/arm64/DecodedInstruction.h>

#include <armob/DiscoveredSymbols.h>
#include <armob/DiscoveredDetails.h>
#include <armob/WorkContext.h>

#include <asm/GenericDetail.h>
#include <asm/GenericDetailFactory.h>



namespace ARMOB {
namespace Helper {

/*************************************************************************/
Discoverer::Discoverer(WorkContext* pWorkContext):
    pWorkContext(pWorkContext),
    pDiscoveredSymbols(pWorkContext->getSymbols()),
    pHeader(pWorkContext->getHeader64()){
}
/*************************************************************************/
Discoverer::~Discoverer() throw(){

}
/*************************************************************************/
void Discoverer::discover(){
    
    discoverSymbols();
    discoverPLTSymbols();    
   
    build(WorkContext::CTextSection);
    build(WorkContext::CPltSection);
    
    resolve(WorkContext::CTextSection);
    resolve(WorkContext::CPltSection);
}
/*************************************************************************/
void Discoverer::discoverSymbols(){
        
    const typename ELF::Elf64::SymbolTable::SymbolList& lstSymbols(
        pHeader->hasSymbolTable() ? pHeader->getSymbolTable()->getSymbols() : pHeader->getDynSymbolTable()->getSymbols());

	int iIdx = 0;

	for(const auto& s : lstSymbols){
        std::string strName(s->getName());
        if(strName[0] != '$'){
		    pDiscoveredSymbols->addCode(s->get_value(), s->get_size(), strName);
        }
	}

}
/*************************************************************************/
void Discoverer::discoverPLTSymbols(){


    ELF::SectionBook::PLTInfo pltInfo;

    if(!ELF::SectionBook::TheInstance.getPLTInfo(pHeader, &pltInfo)){
        return;
    }

    typedef std::list< const char* > NamesList;
    
    NamesList lstPLTNames;

    if(pHeader->hasRelocationPltInfo()){
        const ELF::Elf64::RelocationInfo::RelocationTable& tabRelocations(
            pHeader->getRelocationPltInfo()->getRelocationTable());
        
        for(const auto& d: tabRelocations){
            lstPLTNames.push_back(pHeader->getDynSymbolTable()->get(d->getSymbolOffset())->getName());
        }
    } 


    const typename ELF::Elf64::Section* pPLTSection = pHeader->lookup(".plt");

    ELF::Elf64::S::Addr iAddrData    = pPLTSection->get_addr();
    ELF::Elf64::S::Addr iCursor      = iAddrData;
    ELF::Elf64::S::Addr iAddrDataEnd = iAddrData + pPLTSection->get_size();

    iCursor += pltInfo.iPLTPrologSize;
    NamesList::const_iterator it = lstPLTNames.begin();

    while(iCursor < iAddrDataEnd){
        std::stringstream ssName;
        if(it != lstPLTNames.end()){
          ssName << (*it);  
        }else{
          ssName <<"0x"<<std::hex<<(iCursor-iAddrData)<<std::dec;
        }
        ssName<<"@PLT";
        pDiscoveredSymbols->addCode(iCursor, pltInfo.iPLTEntrySize, ssName.str());
        iCursor += pltInfo.iPLTEntrySize;
        it++;
    }
}
/*************************************************************************/
void Discoverer::build(const std::string& strSectionName){
    
    ARMOB::DiscoveredSymbols::SymbolSet setCodeSymbols(
        pDiscoveredSymbols->getSymbols(Symbol::ST_Code));
    
    const ELF::Elf64::Section* pSection = pHeader->lookup(strSectionName);

	DiscoveredDetails *pDiscoveredDetails = pWorkContext->getDetails(strSectionName);

    const uint8_t* pData         = pSection->getData<uint8_t>();
    ELF::Elf64::S::Addr iAddress = pSection->get_addr();
    size_t  iSize                = pSection->get_size();
    const   int  iStep           = 4;

    ASM::ItemList& lstInstructions(pDiscoveredDetails->getInstructions());

    for(  ARMOB::DiscoveredSymbols::SymbolSet::iterator it = setCodeSymbols.begin();
            it != setCodeSymbols.end(); it++){

        ARMOB::DiscoveredSymbols::SymbolSet::iterator itNext = it;
        itNext++;

        if(itNext != setCodeSymbols.end()){
            if(it->second->getSize() == 0){
                it->second->setSize(itNext->first - it->first);
                std::cout<<"New size: "<<it->second->getName()<<" to: "<<(itNext->first - it->first)<<std::endl;
            }
        }
            
    }

    ARMOB::DiscoveredSymbols::SymbolSet::iterator it = setCodeSymbols.begin();

    int iCounter = 0;
    for(size_t  iOffset = 0; iOffset < iSize; iOffset += iStep){
        
        while(it != setCodeSymbols.end() && 
                it->second->getAddress() + it->second->getSize() <= iAddress + iOffset){
                std::cout<<"Skiping"<<it->second->getName()<<", sz: "<<it->second->getSize()<<" "<<iCounter<<std::endl;
                it++;
                iCounter = 0;
        }

        ASM::ItemList::iterator itNew = pDiscoveredDetails->appendNewInstruction(pData + iOffset, iStep, iAddress + iOffset);
        ASM::ARM::ARM64::DecodedInstruction d(*itNew);

        iCounter ++;

        if( it->first  == iAddress + iOffset){
            it->second->setStart(itNew);
        }else if( it->second->getAddress() + it->second->getSize() - iStep  == iAddress + iOffset){
            std::cout<<"End of instructions for: "<<it->second->getName()<<std::endl;
            it->second->setEnd(itNew);
        }
    }
}
/*************************************************************************/

void Discoverer::resolve(const std::string& strSectionName){

	DiscoveredDetails *pDiscoveredDetails = pWorkContext->getDetails(strSectionName);


    for(auto& item : pDiscoveredDetails->getInstructions()){

      ASM::ARM::ARM64::DecodedInstruction d(item); 
 
      if(d.checkMemoryReference()){

           const ASM::GenericDetail::Addresses& refAddresses(item.getGenericDetail()->getCurrentAddresses());
          
           const ARMOB::DiscoveredSymbols::SymbolSet& setSymbols(pDiscoveredSymbols->getSymbols(Symbol::ST_Code));
           ARMOB::DiscoveredSymbols::SymbolSet::const_iterator it = Tools::LowerBound(setSymbols, refAddresses.iReference);
           
         //  std::cout<<"Reference from:"<<(void*)(refAddresses.iOpCode)<<" to "<<(void*)(refAddresses.iReference)<<std::endl;
           

           if(it != setSymbols.end()  &&
              refAddresses.iReference >= it->second->getAddress() &&
              refAddresses.iReference < it->second->getAddress() + it->second->getSize()) {

          //   std::cout<<"Reference from:"<<(void*)(refAddresses.iOpCode)<<" to "<<(void*)(refAddresses.iReference)
            //    <<" found in: "<<it->second->getName()<<"["<<(void*)it->second->getAddress()<<"]"<<"+"<<(void*)(refAddresses.iReference - it->second->getAddress())<<std::endl;



            it->second->forAll([&item, refAddresses](auto& it){
                 if(it->getGenericDetail()->getCurrentAddresses().iOpCode == refAddresses.iReference){
                        item.getGenericDetail()->setReference(it->getGenericDetail());
                    }
            });
        }
      }
  }
}
/*************************************************************************/
}
}
