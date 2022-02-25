/*
 * File: Builder.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Builder.h"

#include <asm/arm/arm64/DecodedInstruction.h>

#include <armob/DiscoveredSymbols.h>
#include <armob/DiscoveredDetails.h>
#include <armob/WorkContext.h>

#include <asm/GenericDetail.h>
#include <asm/GenericDetailFactory.h>

#include <elf/Expander.h>

namespace ARMOB {
namespace Helper {

/*************************************************************************/
Builder::Builder(WorkContext* pWorkContext):
    pWorkContext(pWorkContext),
    pDiscoveredSymbols(pWorkContext->getSymbols()),
    pHeader(pWorkContext->getHeader64()),
    ptrExpander(new ELF::Expander(pHeader)){
}
/*************************************************************************/
Builder::~Builder() throw(){

}
/*************************************************************************/
void Builder::syncSize(Symbol* pSymbol){
      
    pSymbol->updateSize();

    //We do not want to much of the ELF specific code in Symbol class.
    pHeader->getSymbolTable()->lookup(pSymbol->getName())->set_size(pSymbol->getSize());   
}
/*************************************************************************/
void Builder::syncAddresses(ELF::Elf64::SymbolTable *pSymbolTable){

    ELF::Elf64::SymbolTable::SymbolList& lstElfSymbols(pSymbolTable->getSymbols());

    for(auto& s: lstElfSymbols){

        if(!s->isHidden()){

            ARMOB::Symbol* pSymbol = pDiscoveredSymbols->getSymbol(s->getName());

            if(pSymbol->hasInstructions()){
                pSymbol->updateSize();
                ELF::Elf64::Symbol *pElfSymbol = pSymbolTable->lookup(pSymbol->getName());
                pElfSymbol->set_size(pSymbol->getSize());   
                pElfSymbol->set_value(pSymbol->getStart()->getGenericDetail()->getCurrentAddresses().iOpCode);
                //TOOD other tabales -> header method ?
                std::cout<<"TEST update: "<<pSymbol->getName()<<", v: "<<(void*)pElfSymbol->get_value()<<" "<<lstElfSymbols.size()<<std::endl;
            }
        }
    }
}
/*************************************************************************/
void Builder::syncAddresses(){
    syncAddresses(pHeader->getSymbolTable());
    syncAddresses(pHeader->getDynSymbolTable());
}
/*************************************************************************/
void Builder::build(){

    size_t iExpansion = recomputeAddresses(WorkContext::CTextSection);
    
    if(iExpansion){
        ptrExpander->expand(iExpansion);
        ptrExpander->updateDataSegmentSymbols();
    }  

    syncAddresses();
    pHeader->write();
    updateReferences(WorkContext::CTextSection);
    updateReferences(WorkContext::CPltSection);
    write(WorkContext::CTextSection);
    write(WorkContext::CPltSection);

}
/*************************************************************************/
size_t Builder::recomputeAddresses(const std::string& strSectionName){
    
    std::cout<<"Update addresses for section: "<<strSectionName<<std::endl;

    DiscoveredDetails* pDetails(pWorkContext->getDetails(strSectionName));

    size_t iStartAddress = pHeader->lookup(strSectionName)->get_addr();
    size_t iCurrentAddress = iStartAddress;

    for(auto& item: pDetails->getInstructions()){
        //std::cout<<"Update address: "<<(void*)item.getGenericDetail()->getCurrentAddresses().iOpCode<<" to "<<(void*)iCurrentAddress<<std::endl;
        item.getGenericDetail()->getCurrentAddresses().iOpCode = iCurrentAddress;
        iCurrentAddress += item.getGenericDetail()->getOpCodeLength();
    }

    size_t iNewTextCodeSize = iCurrentAddress - iStartAddress;
    size_t iOldTextSize = pHeader->lookup(strSectionName)->get_size();

    if(iNewTextCodeSize > iOldTextSize){
        return iNewTextCodeSize - iOldTextSize;
    }

    return 0L;
}
/*************************************************************************/
void Builder::updateReferences(const std::string& strSectionName){
    
    std::cout<<"Update references for section: "<<strSectionName<<std::endl;
    DiscoveredDetails* pDetails(pWorkContext->getDetails(strSectionName));

    for(auto& item: pDetails->getInstructions()){
            
        if(item.getGenericDetail()->getCurrentAddresses().iReference){
            
            ASM::ARM::ARM64::DecodedInstruction d(item);
            d.updateOpcodeReference(ptrExpander->getDataSegmentShift());            
            item.callUpdateReference();
        }
        
    }
}
/*************************************************************************/
void Builder::write(const std::string& strSectionName){

     std::cout<<"Write bytecode for section: "<<strSectionName<<std::endl;

    DiscoveredDetails* pDetails(pWorkContext->getDetails(strSectionName));

    uint8_t* pTextStart = pHeader->lookup(strSectionName)->getData<uint8_t>();
    uint8_t* pCursor = pTextStart;
    
    for(auto& item: pDetails->getInstructions()){
        
        memcpy(pCursor, item.getGenericDetail()->getOpcode(), item.getGenericDetail()->getOpCodeLength());
        // std::cout<<"Update opcode: "<<(void*)item.getGenericDetail()->getCurrentAddresses().iOpCode<<std::endl;

        pCursor += item.getGenericDetail()->getOpCodeLength();

    }

    pHeader->lookup(strSectionName)->set_size(pCursor - pTextStart);
}
/*************************************************************************/
}
}
