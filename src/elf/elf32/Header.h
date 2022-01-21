/*
 * File: Header.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Header_H_
#define _ELF_Elf32_Header_H_


#include "Structures.h"
#include <elf/impl/Component.h>

#include<list>
#include<vector>
#include<unordered_map>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
/** The Header class.
 *
 */

class Section;
class Segment;
class SymbolTable;

class Header : public Impl::Component{
public:

	virtual ~Header() throw();
	Header(const ELF::Image *pImage);

	Elf32::Half 	get_type()const;
	Elf32::Half 	get_machine()const;
	Elf32::Word 	get_version()const;
	Elf32::Addr 	get_entry()const;
	Elf32::Off 		get_phoff()const;
	Elf32::Off 		get_shoff()const;
	Elf32::Word 	get_flags()const;
	Elf32::Half 	get_ehsize()const;
	Elf32::Half 	get_phentsize()const;
	Elf32::Half 	get_phnum()const;
	Elf32::Half 	get_shentsize()const;
	Elf32::Half 	get_shnum()const;
	Elf32::Half 	get_shstrndx()const;

	const Header_*  getRaw()const{
		return &header;
	}

	typedef std::vector< std::unique_ptr<Section> > SectionList;
	typedef std::list< std::unique_ptr<Segment> > SegmentList;

	const SectionList& getSections()const{
		return lstSections;
	}

	const SegmentList& getSegments()const{
		return lstSegments;
	}

	const Section* getStringsSection()const{
		return lstSections[get_shstrndx()].get();
	}

	const Section* lookup(const std::string& strName)const{

		SectionByNameMap::const_iterator it = hmSectionByName.find(strName);

		if(it == hmSectionByName.end())
			throw Tools::Exception()<<"Section not found : ["<<strName<<"]";

		return it->second;
	}

	bool hasSymbolTable()const{
		return !ptrSymbolTable == false;
	}
	
	SymbolTable* getSymbolTable()const{
	
		if(!ptrSymbolTable)
			throw Tools::Exception()<<"Symbol table not found";

		return ptrSymbolTable.get();
	};

protected:
	Header_ header;

	SectionList lstSections;
	SegmentList lstSegments;

	typedef std::unordered_map< std::string, Section* > SectionByNameMap;
	SectionByNameMap hmSectionByName;

	std::unique_ptr<SymbolTable> ptrSymbolTable;
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Header_H_ */
