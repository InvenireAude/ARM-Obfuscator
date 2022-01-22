/*
 * File: ContentFile.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_ContentFile_H_
#define _ELF_ContentFile_H_

#include <tools/common.h>

#include "Content.h"

namespace ELF {

/*************************************************************************/
/** The ContentFile class.
 *
 */
class Identification;

namespace Utils {
	class Converter;
};

class ContentFile : public Content {
public:

	virtual ~ContentFile() throw();
	
	ContentFile(const std::string& strName);


	virtual const uint8_t* getData(size_t iOffset)const;

    virtual const uint8_t* getData(size_t iOffset, size_t iDataLen)const;

protected:

	int fd;
	const uint8_t *pMemory;
	size_t iSize;
	
};

/*************************************************************************/
}

#endif /* _ELF_ContentFile_H_ */
