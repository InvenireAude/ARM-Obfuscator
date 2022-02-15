/*
 * File: SymbolDiscoverer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "SymbolDiscoverer.h"

#include <asm/arm/arm64/Decoder.h>

#include <armob/DiscoveredSymbols.h>

#include <asm/GenericInstruction.h>
#include <asm/InstructionFactory.h>


#include <elf/elf.h>


namespace ARMOB {
namespace Helper {

/*************************************************************************/
SymbolDiscoverer::SymbolDiscoverer(const ELF::Artefact* pArtefact, 
                                   DiscoveredSymbols* pDiscoveredSymbols):
    pArtefact(pArtefact),
    pDiscoveredSymbols(pDiscoveredSymbols){
}
/*************************************************************************/
SymbolDiscoverer::~SymbolDiscoverer() throw(){

}
/*************************************************************************/
void SymbolDiscoverer::discover(){
    
    if(pArtefact->getIdentification()->getClass() != ELF::ELFCLASS64){
        throw Tools::Exception()<<"Only 64bit elfs are supported.";
    }

    const ELF::Elf64::Header* pHeader = pArtefact->getHeader64();

    const typename ELF::Elf64::SymbolTable::SymbolList& lstSymbols(pHeader->getSymbolTable()->getSymbols());

	int iIdx = 0;

	for(const auto& s : lstSymbols){
        std::string strName(s->getName());
        if(strName[0] != '$'){
		    pDiscoveredSymbols->addCode(s->get_value(), s->get_size(), strName);
        }
	}
}
/*************************************************************************/
void SymbolDiscoverer::build(){
    
    ARMOB::DiscoveredSymbols::SymbolSet setCodeSymbols(
        pDiscoveredSymbols->getSymbols(Symbol::ST_Code));
    
    const ELF::Elf64::Header* pHeader = pArtefact->getHeader64();

    const ELF::Elf64::Section* pSection = pHeader->lookup(".text");

    const uint8_t* pData         = pSection->getData<uint8_t>();
    ELF::Elf64::S::Addr iAddress = pSection->get_addr();
    size_t  iSize                = pSection->get_size();
    const   int  iStep           = 4;

    ASM::GenericInstructionList& lstInstructions(pDiscoveredSymbols->getInstructions());
    ASM::InstructionFactory* pFactory = pDiscoveredSymbols->getInstructionFactory();

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

        lstInstructions.append(new (pFactory->allocate())ASM::GenericInstruction(pData + iOffset, iStep, iAddress + iOffset));
        iCounter ++;

        if( it->first  == iAddress + iOffset){
            it->second->setStart(lstInstructions.getTail());
        }else if( it->second->getAddress() + it->second->getSize() - iStep  == iAddress + iOffset){
            std::cout<<"End of instructions for: "<<it->second->getName()<<std::endl;
            it->second->setEnd(lstInstructions.getTail());
        }
    }
}
/*************************************************************************/


/*************************************************************************/

void SymbolDiscoverer::resolve(){

 ASM::GenericInstruction* pInstruction = pDiscoveredSymbols->getInstructions().getHead();
 ASM::GenericInstruction* pTail = pDiscoveredSymbols->getInstructions().getTail();

  while(true){

      ASM::ARM::ARM64::Decoder d(pInstruction);
 
      if(d.checkMemoryReference()){

           const ASM::GenericInstruction::Addresses& refAddresses(pInstruction->getCurrentAddresses());
          
           const ARMOB::DiscoveredSymbols::SymbolSet& setSymbols(pDiscoveredSymbols->getSymbols(Symbol::ST_Code));
           ARMOB::DiscoveredSymbols::SymbolSet::const_iterator it = Tools::LowerBound(setSymbols, refAddresses.iReference);
           
         //  std::cout<<"Reference from:"<<(void*)(refAddresses.iOpCode)<<" to "<<(void*)(refAddresses.iReference)<<std::endl;
           

           if(it != setSymbols.end()  &&
              refAddresses.iReference >= it->second->getAddress() &&
              refAddresses.iReference < it->second->getAddress() + it->second->getSize()) {

          //   std::cout<<"Reference from:"<<(void*)(refAddresses.iOpCode)<<" to "<<(void*)(refAddresses.iReference)
            //    <<" found in: "<<it->second->getName()<<"["<<(void*)it->second->getAddress()<<"]"<<"+"<<(void*)(refAddresses.iReference - it->second->getAddress())<<std::endl;


            if(it->second->hasInstructions()){
                ASM::GenericInstruction* pCursor = it->second->getStart();

                while(true){

                    if(pCursor->getCurrentAddresses().iOpCode == refAddresses.iReference){
                        pInstruction->setReference(pCursor);
                    }

                    if( pCursor->isTail() ||
                        pCursor == it->second->getEnd())
                            break; //strange ...

                    pCursor = pCursor->getNext();
                }
            }

           }

      };

        if(pInstruction == pTail)
            break; //strange ...

        pInstruction = pInstruction->getNext();
  }
}
/*************************************************************************/
}
}
