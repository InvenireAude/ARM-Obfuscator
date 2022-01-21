/*
 * File: Symbol.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Symbol_H_
#define _ELF_Elf32_Symbol_H_

#include <tools/common.h>
#include "Structures.h"
#include "SymbolTable.h"

#include <elf/Image.h>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
/** The Symbol class.
 *T
 */
class SymbolTable;

class Symbol {
public:

	virtual ~Symbol() throw();
	Symbol(const SymbolTable* pSymbolTable, const Symbol_* pSymbolData);

	inline static size_t CElfSize = sizeof(Symbol_);

	Elf32::Word get_name()const;
	Elf32::Addr get_value()const;
	Elf32::Word get_size()const;
	uint8_t     get_info()const;
	uint8_t     get_other()const;
	Elf32::Half get_shndx()const;

	const char* getName()const;

	const uint8_t* getData()const;

	template<class T>
	const T* getData()const{
		return reinterpret_cast<const T*>(getData());
	}

protected:
	const SymbolTable* pSymbolTable;

	Symbol_ symbol;
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Symbol_H_ */
