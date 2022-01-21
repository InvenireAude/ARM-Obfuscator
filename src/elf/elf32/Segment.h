/*
 * File: Segment.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Segment_H_
#define _ELF_Elf32_Segment_H_

#include "Structures.h"

#include <elf/impl/Component.h>

namespace ELF {
namespace Elf32 {

/*************************************************************************/
/** The Segment class.
 *
 */
class Segment : public Impl::Component {
public:

	virtual ~Segment() throw();
	Segment(const ELF::Image *pImage, size_t iOffset);

	const Segment_*  getRaw()const{
		return &segment;
	}

	Elf32::Word get_type()const;
	Elf32::Off  get_offset()const;
	Elf32::Addr get_vaddr()const;
	Elf32::Addr get_paddr()const;
	Elf32::Word get_filesz()const;
	Elf32::Word get_memsz()const;
	Elf32::Word get_flags()const;
	Elf32::Word get_align()const;

protected:
	Segment_ segment;
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Segment_H_ */
