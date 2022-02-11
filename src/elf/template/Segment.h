/*
 * File: Segment.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Segment_H_
#define _ELF_Template_Segment_H_

#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>

#include <string.h>

namespace ELF {
namespace Template {

/*************************************************************************/
/** The Segment class.
 *
 */

template<class S>
class Segment : public Impl::Component {
public:


	const typename S::Segment_*  getRaw()const{
		return &segment;
	}

Segment(ELF::Content *pContent, size_t iOffset):
	Impl::Component(pContent),
	segment(*reinterpret_cast<typename S::Segment_*>(pContent->getData(iOffset, sizeof(typename S::Segment_)))){
	std::cerr<<"Offset :"<<(void*)iOffset<<", sizeof: "<<sizeof(segment)<<std::endl;
}

/*************************************************************************/
typename S::Word get_type()const{
	return pConverter->convert(segment.p_type);
}
typename S::Off  get_offset()const{
	return pConverter->convert(segment.p_offset);
}
typename S::Addr get_vaddr()const{
	return pConverter->convert(segment.p_vaddr);
}
typename S::Addr get_paddr()const{
	return pConverter->convert(segment.p_paddr);
}
typename S::Word get_filesz()const{
	return pConverter->convert(segment.p_filesz);
}
typename S::Word get_memsz()const{
	return pConverter->convert(segment.p_memsz);
}
typename S::Word get_flags()const{
	return pConverter->convert(segment.p_flags);
}
typename S::Word get_align()const{
	return pConverter->convert(segment.p_align);
}

void set_type(typename S::Word p_type){
	segment.p_type = pConverter->convert(p_type);
}
void set_offset(typename S::Off p_offset){
	segment.p_offset = pConverter->convert(p_offset);
}
void set_vaddr(typename S::Addr p_vaddr){
	segment.p_vaddr = pConverter->convert(p_vaddr);
}
void set_paddr(typename S::Addr p_paddr){
	segment.p_paddr = pConverter->convert(p_paddr);
}
void set_filesz(typename S::Word p_filesz){
	segment.p_filesz = pConverter->convert(p_filesz);
}
void set_memsz(typename S::Word p_memsz){
	segment.p_memsz = pConverter->convert(p_memsz);
}
void set_flags(typename S::Word p_flags){
	segment.p_flags = pConverter->convert(p_flags);
}
void set_align(typename S::Word p_align){
	segment.p_align = pConverter->convert(p_align);
}

protected:
	typename S::Segment_& segment;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Segment_H_ */
