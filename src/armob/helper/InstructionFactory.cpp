/*
 * File: InstructionFactory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "InstructionFactory.h"

#include <asm/arm/arm64/DecodedInstruction.h>

#include <armob/WorkContext.h>
#include <armob/DiscoveredDetails.h>

#include <asm/GenericDetail.h>
#include <asm/GenericDetailFactory.h>

#include <asm/arm/arm64/spec/EncodingBook.h>

#include <elf/elf.h>


namespace ARMOB {
namespace Helper {

/*************************************************************************/
InstructionFactory::InstructionFactory(DiscoveredDetails*   pDiscoveredDetails):
    pDiscoveredDetails(pDiscoveredDetails){
}
/*************************************************************************/
InstructionFactory::~InstructionFactory() throw(){

}
/*************************************************************************/
ASM::ItemList::iterator InstructionFactory::create(ASM::ItemList::iterator it, 
                                                    ASM::ARM::ARM64::Spec::EncodingId iEncodingId){

    const ASM::ARM::ARM64::Spec::Encoding*  pEncoding =  ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.get(iEncodingId);
    std::cout<<"create blank: "<<ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.getName(pEncoding)<<std::endl;
    ASM::Item* pNew = pDiscoveredDetails->getWorkContext()->getGenericDetailFactory()->create((const uint8_t*)&(pEncoding->opCode), 4, 0);
    ASM::ARM::ARM64::DecodedInstruction d(*pNew, iEncodingId);
    return pDiscoveredDetails->getInstructions().insertAfter(it, pNew);
}
/*************************************************************************/
ASM::ItemList::iterator InstructionFactory::createJump(ASM::ItemList::iterator it, 
                                                       ASM::ARM::ARM64::Spec::EncodingId iEncodingId,
                                                       ASM::ItemList::iterator itReference){

    const ASM::ARM::ARM64::Spec::Encoding*  pEncoding =  ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.get(iEncodingId);
    std::cout<<"create jump: "<<ASM::ARM::ARM64::Spec::EncodingBook::TheInstance.getName(pEncoding)<<std::endl;
    ASM::Item* pNew = pDiscoveredDetails->getWorkContext()->getGenericDetailFactory()->create((const uint8_t*)&(pEncoding->opCode), 4, 0);
    ASM::ARM::ARM64::DecodedInstruction d(*pNew, iEncodingId);
    
    pNew->getGenericDetail()->setReference(itReference->getGenericDetail());
    pNew->getGenericDetail()->getCurrentAddresses().iReference = 0x1;
    return pDiscoveredDetails->getInstructions().insertAfter(it, pNew);
}
/*************************************************************************/
}
}
