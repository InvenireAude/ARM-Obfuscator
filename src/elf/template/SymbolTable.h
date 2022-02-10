/*
 * File: SymbolTable.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_SymbolTable_H_
#define _ELF_Template_SymbolTable_H_

#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>

#include <list>
#include <unordered_map>

namespace ELF {
namespace Template {

template<class S>
class Header;

template<class S>
class Section;

template<class S>
class Symbol;

/*************************************************************************/
/** The SymbolTable class.
 *
 */
template<class S>
class SymbolTable : public ELF::Impl::Component {
public:

	typedef std::list< std::unique_ptr< Symbol<S> > > SymbolList;
	typedef std::unordered_map< std::string, Symbol<S>* > SymbolByNameMap;
	
	inline const SymbolList& getSymbols()const{
		return lstSymbols;
	}

	const Symbol<S>* lookup(const std::string& strName)const{
		
		typename SymbolByNameMap::const_iterator it = hmSymbolByName.find(strName);

		if(it == hmSymbolByName.end())
			throw Tools::Exception()<<"Symbol not found : ["<<strName<<"]";

		return it->second;
	}

	const Header<S>* getHeader()const{
		return pHeader;
	}

	const Section<S> *getSymbolSection()const{
		return 	pSymbolSection;
	}

	const Section<S> *getSymStrSection()const{
		return 	pSymStrSection;
	}


SymbolTable(Header<S> *pHeader, const char* sSymTab, const char* sStrTab):
 	ELF::Impl::Component(pHeader->getContent()),
 	pHeader(pHeader){

 	pSymbolSection = pHeader->lookup(sSymTab);
 	pSymStrSection = pHeader->lookup(sStrTab);

 	size_t iOffset = pSymbolSection->get_offset();
 	size_t iSize   = pSymbolSection->get_size();

 	std::cerr<<"Symbol table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
 		<<sizeof(typename S::Symbol_)<<std::endl;
 
 	size_t iNumEntries = iSize / sizeof(typename S::Symbol_);
 
 	typename S::Symbol_ *pSymbolData = pSymbolSection->template getData< typename S::Symbol_ >();

 	while(iNumEntries > 0){

		std::unique_ptr< Symbol<S> > ptrSymbol(new Symbol<S>(this, pSymbolData));
		hmSymbolByName[pSymStrSection->getString(ptrSymbol->get_name())] = ptrSymbol.get();
		lstSymbols.push_back(std::move(ptrSymbol));

		pSymbolData++;
		iNumEntries--;
	}

}

/*************************************************************************/
~SymbolTable() throw(){
}

protected:

	Header<S> *pHeader;

	Section<S> *pSymbolSection;
	Section<S> *pSymStrSection;

	SymbolList      lstSymbols;
	SymbolByNameMap hmSymbolByName;

};

/*************************************************************************/
}
}

#endif /* _ELF_Template_SymbolTable_H_ */
