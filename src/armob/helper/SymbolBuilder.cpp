/*
 * File: SymbolBuilder.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "SymbolBuilder.h"

#include <asm/arm/arm64/DecodedInstruction.h>

#include <armob/DiscoveredSymbols.h>

#include <asm/GenericDetail.h>
#include <asm/GenericDetailFactory.h>

#include <asm/arm/arm64/spec/EncodingBook.h>

#include <elf/elf.h>


namespace ARMOB {
namespace Helper {

/*************************************************************************/
SymbolBuilder::SymbolBuilder(const ELF::Artefact* pArtefact, 
                                   DiscoveredSymbols* pDiscoveredSymbols):
    pArtefact(pArtefact),
    pDiscoveredSymbols(pDiscoveredSymbols){
}
/*************************************************************************/
SymbolBuilder::~SymbolBuilder() throw(){

}
/*************************************************************************/
ASM::ItemList::iterator SymbolBuilder::createBlankInstruction(ASM::ItemList::iterator it, ASM::ARM::ARM64::Spec::EncodingId iEncodingId){

    const ASM::ARM::ARM64::Spec::Encoding*  pEncoding =  ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.get(iEncodingId);
    std::cout<<"create blank: "<<ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.getName(pEncoding)<<std::endl;
    ASM::Item* pNew = pDiscoveredSymbols->getGenericDetailFactory()->create((const uint8_t*)&(pEncoding->opCode), 4, 0);
    ASM::ARM::ARM64::DecodedInstruction d(*pNew, iEncodingId);
    return pDiscoveredSymbols->getInstructions().insertAfter(it, pNew);
}
/*************************************************************************/
}
}
