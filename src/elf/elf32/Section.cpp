/*
 * File: Section.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Section.h"

#include "Header.h"

#include <string.h>
#include <elf/Image.h>
#include <elf/utils/Converter.h>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
Section::Section( const Header *pHeader, size_t iOffset):
	Impl::Component(pHeader->getImage()),
	pHeader(pHeader){
	std::cerr<<"Offset :"<<iOffset<<", sizeof: "<<sizeof(section)<<std::endl;
	 memcpy(&section, 
	 	pImage->getData(iOffset, sizeof(section)), 
	 	sizeof(section));
}
/*************************************************************************/
Section::~Section() throw(){
}
/*************************************************************************/
const char* Section::getName()const{
	return pHeader->getStringsSection()->getString(get_name());
}
/*************************************************************************/
const char* Section::getString(size_t iOffset)const{
	
	if(iOffset > get_size())
		throw Tools::Exception()<<"String offset is out of bounds, section size: "<<get_size();

	return reinterpret_cast<const char*>(pImage->getData(get_offset()) + iOffset);
}
/*************************************************************************/
Elf32::Word Section::get_name()const{
	return pConverter->convert(section.sh_name);
}
Elf32::Word Section::get_type()const{
	return pConverter->convert(section.sh_type);
}
Elf32::Word Section::get_flags()const{
	return pConverter->convert(section.sh_flags);
}
Elf32::Addr Section::get_addr()const{
	return pConverter->convert(section.sh_addr);
}
Elf32::Off  Section::get_offset()const{
	return pConverter->convert(section.sh_offset);
}
Elf32::Word Section::get_size()const{
	return pConverter->convert(section.sh_size);
}
Elf32::Word Section::get_link()const{
	return pConverter->convert(section.sh_link);
}
Elf32::Word Section::get_info()const{
	return pConverter->convert(section.sh_info);
}
Elf32::Word Section::get_addralign()const{
	return pConverter->convert(section.sh_addralign);
}
Elf32::Word Section::get_entsize()const{
	return pConverter->convert(section.sh_entsize);
}
/*************************************************************************/
}
}
