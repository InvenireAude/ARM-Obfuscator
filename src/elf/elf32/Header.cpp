/*
 * File:convert(Header.cp)p
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Header.h"

#include "../Image.h"
#include "Section.h"
#include "Segment.h"
#include "SymbolTable.h"

#include <string.h>
#include <elf/utils/Converter.h>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
Header::Header(const ELF::Image* pImage):
	Impl::Component(pImage){

	memcpy(&header, 
		   pImage->getData(0, sizeof(header)), 
		   sizeof(header));
	
	if(get_shnum() != 0 && get_shoff() != 0){
		size_t iOffset = get_shoff();
		
		for(int i=0; i<get_shnum(); i++, iOffset+=get_shentsize()){
			std::cerr<<"Offset :"<<iOffset<<std::endl;
			lstSections.emplace_back(new Section(this, iOffset));
		}

	}


	if(get_phnum() != 0 && get_phoff() != 0){
		size_t iOffset = get_phoff();
		
		for(int i=0; i<get_phnum(); i++, iOffset+=get_phentsize()){
			std::cerr<<"Offset :"<<iOffset<<std::endl;
			lstSegments.emplace_back(new Segment(pImage, iOffset));
		}

	}

	for(const auto& s : lstSections){
		hmSectionByName[getStringsSection()->getString(s->get_name())] = s.get();
	}

	if(hmSectionByName.find(".symtab") != hmSectionByName.end()){
		ptrSymbolTable.reset( new SymbolTable(this) );
	}
}
/*************************************************************************/
Header::~Header() throw(){
}
/*************************************************************************/

Elf32::Half Header::get_type()const{
	return pConverter->convert(header.e_type);
}
Elf32::Half Header::get_machine()const{
	return pConverter->convert(header.e_machine);
}
Elf32::Word Header::get_version()const{
	return pConverter->convert(header.e_version);
}
Elf32::Addr Header::get_entry()const{
	return pConverter->convert(header.e_entry);
}
Elf32::Off 	Header::get_phoff()const{
	return pConverter->convert(header.e_phoff);
}
Elf32::Off 	Header::get_shoff()const{
	return pConverter->convert(header.e_shoff);
}
Elf32::Word Header::get_flags()const{
	return pConverter->convert(header.e_flags);
}
Elf32::Half Header::get_ehsize()const{
	return pConverter->convert(header.e_ehsize);
}
Elf32::Half Header::get_phentsize()const{
	return pConverter->convert(header.e_phentsize);
}
Elf32::Half Header::get_phnum()const{
	return pConverter->convert(header.e_phnum);
}
Elf32::Half Header::get_shentsize()const{
	return pConverter->convert(header.e_shentsize);
}
Elf32::Half Header::get_shnum()const{
	return pConverter->convert(header.e_shnum);
}
Elf32::Half Header::get_shstrndx()const{
	return pConverter->convert(header.e_shstrndx);
}

}
}
