/*
 * File: Image.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Image_H_
#define _ELF_Image_H_

#include <tools/common.h>

namespace ELF {

/*************************************************************************/
/** The Image class.
 *
 */
class Identification;


namespace Utils {
	class Converter;
};

class Image {
public:

	virtual ~Image() throw();
	
	Image(const std::string& strName);

	
	inline Identification* getIdentification()const{
		return ptrIdentification.get();
	}

	inline const Utils::Converter* getConverter()const{
		return ptrConverter.get();
	}

	const uint8_t* getData(size_t iOffset)const{
		
		if(iOffset >= iSize){
			throw Tools::Exception()<<"Bad offset: "<<iOffset<<", size is: "<<iSize;
		}

		return pMemory + iOffset;
	}

	const uint8_t* getData(size_t iOffset, size_t iDataLen)const{
		
		if(iOffset >= iSize || iOffset + iDataLen > iSize){
			throw Tools::Exception()<<"Bad offset: "<<iOffset
				<<", or data length: "<<iDataLen<<", size is: "<<iSize;
		}

		return pMemory + iOffset;
	}

protected:

	int fd;
	const uint8_t *pMemory;
	size_t iSize;
	
	std::unique_ptr<Identification>   ptrIdentification;
	std::unique_ptr<Utils::Converter> ptrConverter;

	void identify();

};

/*************************************************************************/
}

#endif /* _ELF_Image_H_ */
