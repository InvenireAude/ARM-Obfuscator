/*
 * File: Helper.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Utils_Helper_H_
#define _ELF_Utils_Helper_H_

#include <tools/common.h>

namespace ELF {
namespace Utils {

/*************************************************************************/
/** The Helper class.
 *
 */
class Helper {
public:

	static std::string StrToHex(const std::string& strData);
	static std::string StrToPrintableAndHex(const std::string& strData);
	static std::string CharToHex(const char cChar);
	static std::string StrToPrintableOrHex(const std::string& strData);
	static char HexDigit(int  iValue);
	static char  HexDigit(unsigned char cValue);
	static unsigned char HexValue(char cValue);
	static void  BinarytoHex(const void *pData, size_t iDataLen, std::string& strOutput);
	static std::string  BinarytoHex(const void *sData, size_t iDataLen);
};

/*************************************************************************/
}
}

#endif /* _ELF_Utils_Helper_H_ */
