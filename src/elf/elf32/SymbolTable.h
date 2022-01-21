/*
 * File: SymbolTable.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_SymbolTable_H_
#define _ELF_Elf32_SymbolTable_H_

#include <tools/common.h>
#include <elf/impl/Component.h>

#include <list>
#include <unordered_map>

namespace ELF {
namespace Elf32 {

class Header;
class Section;
class Symbol;

/*************************************************************************/
/** The SymbolTable class.
 *
 */
class SymbolTable : public ELF::Impl::Component {
public:

	virtual ~SymbolTable() throw();
	SymbolTable(const Header *pHeader);

	typedef std::list< std::unique_ptr<Symbol> > SymbolList;
	typedef std::unordered_map< std::string, Symbol* > SymbolByNameMap;
	
	inline const SymbolList& getSymbols()const{
		return lstSymbols;
	}

	const Symbol* lookup(const std::string& strName)const{
		
		SymbolByNameMap::const_iterator it = hmSymbolByName.find(strName);

		if(it == hmSymbolByName.end())
			throw Tools::Exception()<<"Symbol not found : ["<<strName<<"]";

		return it->second;
	}

	const Header* getHeader()const{
		return pHeader;
	}

	const Section *getSymbolSection()const{
		return 	pSymbolSection;
	}

	const Section *getSymStrSection()const{
		return 	pSymStrSection;
	}

protected:
	const Header *pHeader;

	const Section *pSymbolSection;
	const Section *pSymStrSection;

	SymbolList      lstSymbols;
	SymbolByNameMap hmSymbolByName;

};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_SymbolTable_H_ */
