/*
 * File: Symbol.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Symbol_H_
#define _ELF_Template_Symbol_H_


#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Image.h>

namespace ELF {
namespace Template {

/*************************************************************************/
/** The Symbol class.
 *T
 */
template<class S>
class SymbolTable;

template<class S>
class Symbol {
public:


	inline static size_t CElfSize = sizeof(typename S::Symbol_);

	template<class T>
	const T* getData()const{
		return reinterpret_cast<const T*>(getData());
	}


/*************************************************************************/
Symbol(const SymbolTable<S>* pSymbolTable, const typename S::Symbol_* pSymbolData):
	pSymbolTable(pSymbolTable){

	memcpy(&symbol, pSymbolData, CElfSize);
}
/*************************************************************************/
~Symbol() throw(){	
}
/*************************************************************************/
const char* getName()const{
	return pSymbolTable->getSymStrSection()->getString(get_name());
}
/*************************************************************************/
const uint8_t* getData()const{
	
	std::cerr<<" 1: "<<(void*)(long)get_value()<<std::endl;
	std::cerr<<" 2: "<<(void*)(long)pSymbolTable->getHeader()->getSections()[get_shndx()]->get_offset()<<std::endl;
	std::cerr<<" 3: "<<(void*)(long)pSymbolTable->getHeader()->getSections()[get_shndx()]->get_addr()<<std::endl;

	return pSymbolTable->getImage()->getData(
		pSymbolTable->getHeader()->getSections()[get_shndx()]->get_offset() +
		get_value() - pSymbolTable->getHeader()->getSections()[get_shndx()]->get_addr());

}
/*************************************************************************/
typename S::Word get_name()const{
	return pSymbolTable->getConverter()->convert(symbol.st_name);
}
typename S::Addr get_value()const{
	return pSymbolTable->getConverter()->convert(symbol.st_value);
}
typename S::Word get_size()const{
	return pSymbolTable->getConverter()->convert(symbol.st_size);
}
uint8_t     get_info()const{
	return symbol.st_info;
}
uint8_t     get_other()const{
	return symbol.st_other;
}
typename S::Half get_shndx()const{
	return pSymbolTable->getConverter()->convert(symbol.st_shndx);
}


protected:
	const SymbolTable<S>* pSymbolTable;

	typename S::Symbol_ symbol;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Symbol_H_ */
