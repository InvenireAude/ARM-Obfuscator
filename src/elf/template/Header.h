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
class DynamicInfo;

template<class S>
class GotInfo;

template<class S>
class GotPltInfo;

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

	Section<S>* getStringsSection()const{
		return lstSections[get_shstrndx()].get();
	}

	Section<S>* lookup(const std::string& strName)const{

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
	
	bool hasDynamicInfo()const{
		return !ptrDynamicInfo == false;
	}
	
	bool hasGotInfo()const{
		return !ptrGotInfo == false;
	}

	bool hasGotPltInfo()const{
		return !ptrGotPltInfo == false;
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

	DynamicInfo<S>* getDynamicInfo()const{
	
		if(!ptrDynamicInfo)
			throw Tools::Exception()<<"Dynamic information not found";

		return ptrDynamicInfo.get();
	};

	GotInfo<S>* getGotInfo()const{
	
		if(!ptrGotInfo)
			throw Tools::Exception()<<"Got information not found";

		return ptrGotInfo.get();
	};

	GotPltInfo<S>* getGotPltInfo()const{
	
		if(!ptrGotPltInfo)
			throw Tools::Exception()<<"GotPlt information not found";

		return ptrGotPltInfo.get();
	};

/*************************************************************************/
Header(ELF::Content* pContent):
	Impl::Component(pContent),
	header(*pContent->getData<typename S::Header_>()){

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
		std::cerr<<"by name :"<<getStringsSection()->getString(s->get_name())<<std::endl;
		hmSectionByName[getStringsSection()->getString(s->get_name())] = s.get();
	}

	if(hmSectionByName.find(".symtab") != hmSectionByName.end()){
		ptrSymbolTable.reset( new SymbolTable(this,".symtab",".strtab") );
	}

	if(hmSectionByName.find(".dynsym") != hmSectionByName.end()){
		ptrDynSymbolTable.reset( new SymbolTable(this,".dynsym",".dynstr"));
	}

	if(hmSectionByName.find(".dynamic") != hmSectionByName.end()){
		ptrDynamicInfo.reset( new DynamicInfo(this,".dynamic"));
	}

	if(hmSectionByName.find(".got") != hmSectionByName.end()){
		ptrGotInfo.reset( new GotInfo(this));
	}

	if(hmSectionByName.find(".got.plt") != hmSectionByName.end()){
		ptrGotPltInfo.reset( new GotPltInfo(this));
	}

}
/*************************************************************************/
~Header() throw(){
}
/*************************************************************************/
void write(){

	(*pContent->getData<typename S::Header_>()) = header;

	size_t iOffset = get_shoff();
	for(auto& s: lstSections){
		s->write(iOffset);
		iOffset+=get_shentsize();
	}

	iOffset = get_phoff();
	for(auto& s: lstSegments){
		s->write(iOffset);
		iOffset+=get_phentsize();
	}
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

void set_type(typename S::Half e_type){
	header.e_type = pConverter->convert(e_type);
}
void set_machine(typename S::Half e_machine){
	header.e_machine = pConverter->convert(e_machine);
}
void set_version(typename S::Word e_version){
	header.e_version = pConverter->convert(e_version);
}
void set_entry(typename S::Addr e_entry){
	header.e_entry = pConverter->convert(e_entry);
}
void set_phoff(typename S::Off e_phoff){
	header.e_phoff = pConverter->convert(e_phoff);
}
void set_shoff(typename S::Off e_shoff){
	header.e_shoff = pConverter->convert(e_shoff);
}
void set_flags(typename S::Word e_flags){
	header.e_flags = pConverter->convert(e_flags);
}
void set_ehsize(typename S::Half e_ehsize){
	header.e_ehsize = pConverter->convert(e_ehsize);
}
void set_phentsize(typename S::Half e_phentsize){
	header.e_phentsize = pConverter->convert(e_phentsize);
}
void set_phnum(typename S::Half e_phnum){
	header.e_phnum = pConverter->convert(e_phnum);
}
void set_shentsize(typename S::Half e_shentsize){
	header.e_shentsize = pConverter->convert(e_shentsize);
}
void set_shnum(typename S::Half e_shnum){
	header.e_shnum = pConverter->convert(e_shnum);
}
void set_shstrndx(typename S::Half e_shstrndx){
	header.e_shstrndx = pConverter->convert(e_shstrndx);
}

	void insertSpaceAfter(typename S::Off iOffset, size_t iSize){

		pContent->makeSpace(reinterpret_cast<size_t>(iOffset), iSize);
		set_shoff(get_shoff()+iSize);

	    std::cout<<"offset :"<<(void*)iOffset<<std::endl;

		for(auto& s: lstSections)
		if(s->get_type()){

			std::cout<<"Checking section :"<<(void*)s->get_offset()<<std::endl;

			if( s->get_offset() <= iOffset && 
			 s->get_offset() + s->get_size() > iOffset){
					std::cout<<"Update section :"<<(void*)s->get_offset()<<std::endl;
					s->set_size(s->get_size() + iSize);
			}else if( s->get_offset() > iOffset ){
					std::cout<<"Moving section :"<<(void*)s->get_offset()<<std::endl;
				s->set_offset(s->get_offset() + iSize);
				s->set_addr(s->get_addr() + iSize);
			}
		}


		for(auto& s: lstSegments){

			if( s->get_offset() <= iOffset && 
			 s->get_offset() + s->get_filesz() > iOffset){
					std::cout<<"Update segment :"<<(void*)s->get_offset()<<std::endl;
					s->set_filesz(s->get_filesz() + iSize);
					s->set_memsz(s->get_memsz() + iSize);
			}else if( s->get_offset() > iOffset ){
				std::cout<<"Moving segment :"<<(void*)s->get_offset()<<std::endl;
				s->set_offset(s->get_offset() + iSize);
				s->set_paddr(s->get_paddr() + iSize);
				s->set_vaddr(s->get_vaddr() + iSize);
			}
		}

	}

protected:
	typename S::Header_ header;

	SectionList lstSections;
	SegmentList lstSegments;

	typedef std::unordered_map< std::string, Section<S>* > SectionByNameMap;
	SectionByNameMap hmSectionByName;

	std::unique_ptr< SymbolTable<S> > ptrSymbolTable;
	std::unique_ptr< SymbolTable<S> > ptrDynSymbolTable;
	std::unique_ptr< DynamicInfo<S> > ptrDynamicInfo;
	std::unique_ptr< GotInfo<S> >     ptrGotInfo;
	std::unique_ptr< GotPltInfo<S> >  ptrGotPltInfo;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Header_H_ */
