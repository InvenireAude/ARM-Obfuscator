/*
 * File: Segment.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Segment.h"

#include <string.h>
#include <elf/Image.h>
#include <elf/utils/Converter.h>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
Segment::Segment(const ELF::Image *pImage, size_t iOffset):
	Impl::Component(pImage){
	std::cerr<<"Offset :"<<iOffset<<", sizeof: "<<sizeof(segment)<<std::endl;
	 memcpy(&segment, 
	 	pImage->getData(iOffset, sizeof(segment)), 
	 	sizeof(segment));
}
/*************************************************************************/
Segment::~Segment() throw(){
}
/*************************************************************************/
Elf32::Word Segment::get_type()const{
	return pConverter->convert(segment.p_type);
}
Elf32::Off  Segment::get_offset()const{
	return pConverter->convert(segment.p_offset);
}
Elf32::Addr Segment::get_vaddr()const{
	return pConverter->convert(segment.p_vaddr);
}
Elf32::Addr Segment::get_paddr()const{
	return pConverter->convert(segment.p_paddr);
}
Elf32::Word Segment::get_filesz()const{
	return pConverter->convert(segment.p_filesz);
}
Elf32::Word Segment::get_memsz()const{
	return pConverter->convert(segment.p_memsz);
}
Elf32::Word Segment::get_flags()const{
	return pConverter->convert(segment.p_flags);
}
Elf32::Word Segment::get_align()const{
	return pConverter->convert(segment.p_align);
}
/*************************************************************************/
}
}
