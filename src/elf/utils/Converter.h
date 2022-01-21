/*
 * File: Converter.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Utils_Converter_H_
#define _ELF_Utils_Converter_H_

#include <inttypes.h>

#include <tools/common.h>

#include <elf/Specification.h>

namespace ELF {
namespace Utils {

/*************************************************************************/
/** The Converter class.
 *
 */
class Converter {
public:

	virtual ~Converter(){};
	virtual uint16_t convert(uint16_t iValue)const = 0;
	virtual uint32_t convert(uint32_t iValue)const = 0;
	virtual uint64_t convert(uint64_t iValue)const = 0;

	static Converter* Create(Data iEncoding);
};
/*************************************************************************/
}
}

#endif /* _ELF_Utils_Converter_H_ */
