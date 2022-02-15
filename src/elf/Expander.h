/*
 * File: Expander.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Expander_H_
#define _ELF_Expander_H_

#include <tools/common.h>

#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>

namespace ELF {

/*************************************************************************/
/** The Expander class.
 *
 */ 

// TODO make template 32/64 bit
class Expander {
public:


	Expander(Elf64::Header* pHeader);

	const size_t getDataSegmentShift() const{
		return iDataSegmentShift;
	}

	void expand(size_t iNeededSpace);
	void updateDataSegmentSymbols();
	
protected:

	Elf64::Header* pHeader;

	void insertSpaceAfter(Elf64::S::Off iOffset, size_t iSize);

	size_t iDataSegmentShift;
	size_t iOrginalDataStart;

	size_t iAfterTextShift;
	size_t iOrginalAfterText;

	ELF::Elf64::Section *pTextSection;
    ELF::Elf64::Section *pEhFrameSection;
    ELF::Elf64::Section *pDynamicSection;
};

/*************************************************************************/
}

#endif /* _Expander_Expander_H_ */
