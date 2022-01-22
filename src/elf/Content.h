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

	virtual const uint8_t* getData(size_t iOffset)const = 0;

	virtual const uint8_t* getData(size_t iOffset, size_t iDataLen)const = 0;

protected:
	
	std::unique_ptr<Identification>   ptrIdentification;
	std::unique_ptr<Utils::Converter> ptrConverter;


	void setup(std::unique_ptr<Identification>&&   ptrIdentification);
};

/*************************************************************************/
}

#endif /* _ELF_Content_H_ */
