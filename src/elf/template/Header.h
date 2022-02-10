/*
 * File: Header.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Header_H_
#define _ELF_Template_Header_H_


#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>

#include<list>
#include<vector>
#include<unordered_map>

#include <string.h>

namespace ELF {
namespace Template {

/*************************************************************************/
/** The Header class.
 *
 */


template<class S>
class Section;

template<class S>
class Segment;

template<class S>
class SymbolTable;

template<class S>
class Header : public Impl::Component{
public:

	const typename S::Header_*  getRaw()const{
		return &header;
	}

	typedef std::vector< std::unique_ptr<Section<S> > > SectionList;
	typedef std::list< std::unique_ptr< Segment<S> > > SegmentList;

	const SectionList& getSections()const{
		return lstSections;
	}

	const SegmentList& getSegments()const{
		return lstSegments;
	}

	const Section<S>* getStringsSection()const{
		return lstSections[get_shstrndx()].get();
	}

	const Section<S>* lookup(const std::string& strName)const{

		typename SectionByNameMap::const_iterator it = hmSectionByName.find(strName);

		if(it == hmSectionByName.end())
			throw Tools::Exception()<<"Section not found : ["<<strName<<"]";

		return it->second;	
	}

	bool hasSymbolTable()const{
		return !ptrSymbolTable == false;
	}

	bool hasDynSymbolTable()const{
		return !ptrDynSymbolTable == false;
	}
	
	SymbolTable<S>* getSymbolTable()const{
	
		if(!ptrSymbolTable)
			throw Tools::Exception()<<"Symbol table not found";

		return ptrSymbolTable.get();
	};

	SymbolTable<S>* getDynSymbolTable()const{
	
		if(!ptrDynSymbolTable)
			throw Tools::Exception()<<"Dynamic symbol table not found";

		return ptrDynSymbolTable.get();
	};

/*************************************************************************/
Header(const ELF::Content* pContent):
	Impl::Component(pContent){

	memcpy(&header, 
		   pContent->getData(0, sizeof(header)), 
		   sizeof(header));
	
	if(get_shnum() != 0 && get_shoff() != 0){
		size_t iOffset = get_shoff();
		
		for(int i=0; i<get_shnum(); i++, iOffset+=get_shentsize()){
			std::cerr<<"Offset :"<<iOffset<<std::endl;
		lstSections.emplace_back(new Section<S>(this, iOffset));
		}

	}


	if(get_phnum() != 0 && get_phoff() != 0){
		size_t iOffset = get_phoff();
		
		for(int i=0; i<get_phnum(); i++, iOffset+=get_phentsize()){
			std::cerr<<"Offset :"<<iOffset<<std::endl;
			lstSegments.emplace_back(new Segment<S>(pContent, iOffset));
		}

	}

	for(const auto& s : lstSections){
		hmSectionByName[getStringsSection()->getString(s->get_name())] = s.get();
	}

	if(hmSectionByName.find(".symtab") != hmSectionByName.end()){
		ptrSymbolTable.reset( new SymbolTable(this,".symtab",".strtab") );
	}

	if(hmSectionByName.find(".dynsym") != hmSectionByName.end()){
		ptrDynSymbolTable.reset( new SymbolTable(this,".dynsym",".dynstr"));
	}
}
/*************************************************************************/
~Header() throw(){
}
/*************************************************************************/

typename S::Half get_type()const{
	return pConverter->convert(header.e_type);
}
typename S::Half get_machine()const{
	return pConverter->convert(header.e_machine);
}
typename S::Word get_version()const{
	return pConverter->convert(header.e_version);
}
typename S::Addr get_entry()const{
	return pConverter->convert(header.e_entry);
}
typename S::Off 	get_phoff()const{
	return pConverter->convert(header.e_phoff);
}
typename S::Off 	get_shoff()const{
	return pConverter->convert(header.e_shoff);
}
typename S::Word get_flags()const{
	return pConverter->convert(header.e_flags);
}
typename S::Half get_ehsize()const{
	return pConverter->convert(header.e_ehsize);
}
typename S::Half get_phentsize()const{
	return pConverter->convert(header.e_phentsize);
}
typename S::Half get_phnum()const{
	return pConverter->convert(header.e_phnum);
}
typename S::Half get_shentsize()const{
	return pConverter->convert(header.e_shentsize);
}
typename S::Half get_shnum()const{
	return pConverter->convert(header.e_shnum);
}
typename S::Half get_shstrndx()const{
	return pConverter->convert(header.e_shstrndx);
}

protected:
	typename S::Header_ header;

	SectionList lstSections;
	SegmentList lstSegments;

	typedef std::unordered_map< std::string, Section<S>* > SectionByNameMap;
	SectionByNameMap hmSectionByName;

	std::unique_ptr< SymbolTable<S> > ptrSymbolTable;
	std::unique_ptr< SymbolTable<S> > ptrDynSymbolTable;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Header_H_ */
