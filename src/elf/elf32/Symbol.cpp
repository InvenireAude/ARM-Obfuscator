/*
 * File: Symbol.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Symbol.h"

#include <elf/impl/Component.h>
#include <elf/utils/Converter.h>
#include <string.h>

#include "SymbolTable.h"
#include "Section.h"
#include "Header.h"


#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

namespace ELF {
namespace Elf32 {

/*************************************************************************/
Symbol::Symbol(const SymbolTable* pSymbolTable, const Symbol_* pSymbolData):
	pSymbolTable(pSymbolTable){

	memcpy(&symbol, pSymbolData, CElfSize);
}
/*************************************************************************/
Symbol::~Symbol() throw(){	
}
/*************************************************************************/
const char* Symbol::getName()const{
	return pSymbolTable->getSymStrSection()->getString(get_name());
}
/*************************************************************************/
const uint8_t* Symbol::getData()const{
	
	std::cerr<<" 1: "<<(void*)(long)get_value()<<std::endl;
	std::cerr<<" 2: "<<(void*)(long)pSymbolTable->getHeader()->getSections()[get_shndx()]->get_offset()<<std::endl;
	std::cerr<<" 3: "<<(void*)(long)pSymbolTable->getHeader()->getSections()[get_shndx()]->get_addr()<<std::endl;

	return pSymbolTable->getImage()->getData(
		pSymbolTable->getHeader()->getSections()[get_shndx()]->get_offset() +
		get_value() - pSymbolTable->getHeader()->getSections()[get_shndx()]->get_addr());

}
/*************************************************************************/
Elf32::Word Symbol::get_name()const{
	return pSymbolTable->getConverter()->convert(symbol.st_name);
}
Elf32::Addr Symbol::get_value()const{
	return pSymbolTable->getConverter()->convert(symbol.st_value);
}
Elf32::Word Symbol::get_size()const{
	return pSymbolTable->getConverter()->convert(symbol.st_size);
}
uint8_t     Symbol::get_info()const{
	return symbol.st_info;
}
uint8_t     Symbol::get_other()const{
	return symbol.st_other;
}
Elf32::Half Symbol::get_shndx()const{
	return pSymbolTable->getConverter()->convert(symbol.st_shndx);
}

}
}
