/*
 * File: Disassembler.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Disassembler.h"

#include <armob/DiscoveredSymbols.h>

#include <asm/GenericInstruction.h>
#include <asm/arm/arm64/Decoder.h>

#include <elf/elf.h>


namespace ARMOB {
namespace Helper {

/*************************************************************************/
Disassembler::Disassembler(DiscoveredSymbols* pDiscoveredSymbols):
    pDiscoveredSymbols(pDiscoveredSymbols){
}
/*************************************************************************/
Disassembler::~Disassembler() throw(){

}
/*************************************************************************/
void Disassembler::print(const std::string& strName, std::ostream& os){
 
    Symbol* pSymbol = pDiscoveredSymbols->getSymbol(strName);
    ARMOB::InstructionList::iterator it = pSymbol->getStart();

    if(it == pDiscoveredSymbols->getInstructions().end()){
        return;
    }

    std::cerr<<"sz: "<<sizeof(it)<<std::endl;

   while(it   != pDiscoveredSymbols->getInstructions().end() &&
         it++ != pSymbol->getEnd()){

        ASM::ARM::ARM64::Decoder d(&*it);
        d.print(std::cout);
        std::cout<<std::endl;   
    }

}
/*************************************************************************/
}
}
