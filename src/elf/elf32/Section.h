/*
 * File: Section.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Section_H_
#define _ELF_Elf32_Section_H_

#include "Structures.h"

#include <elf/impl/Component.h>
#include <elf/Image.h>

namespace ELF {
namespace Elf32 {

class Header;

/*************************************************************************/
/** The Section class.
 *
 */
class Section : public Impl::Component {
public:

	virtual ~Section() throw();
	Section(const Header *pHeader, size_t iOffset);

	const Section_*  getRaw()const{
		return &section;
	}

	Elf32::Word get_name()const;
	Elf32::Word get_type()const;
	Elf32::Word get_flags()const;
	Elf32::Addr get_addr()const;
	Elf32::Off  get_offset()const;
	Elf32::Word get_size()const;
	Elf32::Word get_link()const;
	Elf32::Word get_info()const;
	Elf32::Word get_addralign()const;
	Elf32::Word get_entsize()const;

	const char* getString(size_t iOffset)const;

	const char* getName()const;

	template<class T>
	const T* getData()const{
		std::cerr<<"Get data for offset: "<<get_offset();
		return reinterpret_cast<const T*>(pImage->getData(get_offset()));
	}

protected:
	
	const Header *pHeader;

	Section_ section;
	
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Section_H_ */
