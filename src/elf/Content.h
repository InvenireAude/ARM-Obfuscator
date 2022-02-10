/*
 * File: Content.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Content_H_
#define _ELF_Content_H_

#include <tools/common.h>

namespace ELF {

/*************************************************************************/
/** The Content class.
 *
 */
class Identification;

namespace Utils {
	class Converter;
};

class Content {
public:

	virtual ~Content() throw();
	
	Content();
	
	inline Identification* getIdentification()const{
		return ptrIdentification.get();
	}

	inline const Utils::Converter* getConverter()const{
		return ptrConverter.get();
	}

	inline const uint8_t* getData(size_t iOffset)const{
		return const_cast<Content*>(this)->getData(iOffset);
	}

	inline const uint8_t* getData(size_t iOffset, size_t iDataLen)const{
		return const_cast<Content*>(this)->getData(iOffset, iDataLen);
	}

	virtual uint8_t* getData(size_t iOffset) = 0;
	virtual uint8_t* getData(size_t iOffset, size_t iDataLen) = 0;
	virtual size_t   getSize()const = 0;
	
protected:
	
	std::unique_ptr<Identification>   ptrIdentification;
	std::unique_ptr<Utils::Converter> ptrConverter;


	void setup(std::unique_ptr<Identification>&&   ptrIdentification);

};

/*************************************************************************/
}

#endif /* _ELF_Content_H_ */
