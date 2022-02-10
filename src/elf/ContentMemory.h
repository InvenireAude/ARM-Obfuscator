/*
 * File: ContentMemory.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_ContentMemory_H_
#define _ELF_ContentMemory_H_

#include <tools/common.h>

#include "Content.h"

namespace ELF {

/*************************************************************************/
/** The ContentMemory class.
 *
 */
class Identification;

namespace Utils {
	class Converter;
};

class ContentMemory : public Content {
public:

	virtual ~ContentMemory() throw();
	
	ContentMemory(const uint8_t* pSource, size_t iSize);


	virtual uint8_t* getData(size_t iOffset);

    virtual uint8_t* getData(size_t iOffset, size_t iDataLen);

	virtual size_t   getSize()const;
	
protected:

	uint8_t *pMemory;
	size_t iSize;
	size_t iAvailableMemory;
};

/*************************************************************************/
}

#endif /* _ELF_ContentMemory_H_ */
