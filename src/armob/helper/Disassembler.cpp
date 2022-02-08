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
class SymbolResolver : public ASM::ARM::ARM64::Decoder::SymbolResolver {
	public:
        SymbolResolver(DiscoveredSymbols* pDiscoveredSymbols):
            pDiscoveredSymbols(pDiscoveredSymbols),
            setSymbols(pDiscoveredSymbols->getSymbols(Symbol::ST_Code)){};

	virtual void print(std::ostream& os, uint64_t iAddress)const{
        DiscoveredSymbols::SymbolSet::const_iterator it = setSymbols.find(iAddress);

        if(it != setSymbols.end()){
            os<<" : "<<it->second->getName();
        }
    };

    DiscoveredSymbols* pDiscoveredSymbols;
    DiscoveredSymbols::SymbolSet setSymbols;
    
};
/*************************************************************************/
void Disassembler::print(const std::string& strName, std::ostream& os){
 
    Symbol* pSymbol = pDiscoveredSymbols->getSymbol(strName);
    ARMOB::InstructionList::iterator it = pSymbol->getStart();

    SymbolResolver sr(pDiscoveredSymbols);

    if(it == pDiscoveredSymbols->getInstructions().end()){
        return;
    }

    std::cerr<<"sz: "<<sizeof(it)<<std::endl;

   while(it   != pDiscoveredSymbols->getInstructions().end() &&
         it++ != pSymbol->getEnd()){

        ASM::ARM::ARM64::Decoder d(&*it);
        d.print(std::cout, &sr);
        std::cout<<std::endl;   
    }

}
/*************************************************************************/
}
}
