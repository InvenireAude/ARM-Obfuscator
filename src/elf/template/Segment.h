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
#include <elf/Image.h>

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

Segment(const ELF::Image *pImage, size_t iOffset):
	Impl::Component(pImage){
	std::cerr<<"Offset :"<<iOffset<<", sizeof: "<<sizeof(segment)<<std::endl;
	 memcpy(&segment, 
	 	pImage->getData(iOffset, sizeof(segment)), 
	 	sizeof(segment));
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
protected:
	typename S::Segment_ segment;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Segment_H_ */
