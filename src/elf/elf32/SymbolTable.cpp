/*
 * File: SymbolTable.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "SymbolTable.h"

#include "Header.h"
#include "Section.h"
#include "Symbol.h"

namespace ELF {
namespace Elf32 {

/*************************************************************************/
SymbolTable::SymbolTable(const Header *pHeader):
 	ELF::Impl::Component(pHeader->getImage()),
 	pHeader(pHeader){

 pSymbolSection = pHeader->lookup(".symtab");
 pSymStrSection = pHeader->lookup(".strtab");

 size_t iOffset = pSymbolSection->get_offset();
 size_t iSize   = pSymbolSection->get_size();

 std::cerr<<"Symbol table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"<<sizeof(Symbol_)<<std::endl;
 
 size_t iNumEntries = iSize / sizeof(Symbol_);
 
 const Symbol_ *pSymbolData = pSymbolSection->getData<Symbol_>();

 while(iNumEntries > 0){

	std::unique_ptr<Symbol> ptrSymbol(new Symbol(this, pSymbolData));
	hmSymbolByName[pSymStrSection->getString(ptrSymbol->get_name())] = ptrSymbol.get();
	lstSymbols.push_back(std::move(ptrSymbol));

	pSymbolData++;
	iNumEntries--;
 }

}
/*************************************************************************/
SymbolTable::~SymbolTable() throw(){
}
/*************************************************************************/
}
}
