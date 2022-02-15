/*
 * File: Disassembler.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Disassembler.h"

#include <armob/DiscoveredSymbols.h>

#include <asm/ItemList.h>
#include <asm/arm/arm64/DecodedInstruction.h>

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
class SymbolResolver : public ASM::ARM::ARM64::DecodedInstruction::SymbolResolver {
	public:
        SymbolResolver(DiscoveredSymbols* pDiscoveredSymbols):
            pDiscoveredSymbols(pDiscoveredSymbols),
            setSymbols(pDiscoveredSymbols->getSymbols(Symbol::ST_Code)){};

	virtual void print(std::ostream& os, uint64_t iAddress)const{
      
        ARMOB::DiscoveredSymbols::SymbolSet::const_iterator it = Tools::LowerBound(setSymbols, iAddress);   

        if(it != setSymbols.end()  &&
              iAddress >= it->second->getAddress() &&
              iAddress < it->second->getAddress() + it->second->getSize()) {

                os<<" <"<<it->second->getName();
                if(iAddress != it->second->getAddress()){
                    os<<"+"<<(void*)(iAddress - it->second->getAddress());
                }
                os<<">";
        }
    };

    DiscoveredSymbols* pDiscoveredSymbols;
    DiscoveredSymbols::SymbolSet setSymbols;
    
};
/*************************************************************************/
void Disassembler::print(const std::string& strName, std::ostream& os){
 
    Symbol* pSymbol = pDiscoveredSymbols->getSymbol(strName);

    SymbolResolver sr(pDiscoveredSymbols);

    pSymbol->forAll([&os, &sr](auto& it){
        ASM::ARM::ARM64::DecodedInstruction d(*it);
        d.print(std::cout, &sr);
        std::cout<<std::endl;   
    });

}
/*************************************************************************/
}
}
