/*
 * File: SymbolDiscoverer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "SymbolDiscoverer.h"

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

    ARMOB::DiscoveredSymbols::SymbolSet::iterator it = setCodeSymbols.begin();

    for(size_t  iOffset = 0; iOffset < iSize; iOffset += iStep){
        
        while(it != setCodeSymbols.end() && 
                it->second->getAddress() + it->second->getSize() <= iAddress + iOffset){
                it++;
        }

        lstInstructions.append(new (pFactory->allocate())ASM::GenericInstruction(pData + iOffset, iStep, iAddress + iOffset));
   
        if( it->first  == iAddress + iOffset){
            it->second->setStart(lstInstructions.getTail());
        }else if( it->second->getAddress() + it->second->getSize() - iStep  == iAddress + iOffset){
            it->second->setEnd(lstInstructions.getTail());
        }
    }
}
/*************************************************************************/
}
}
