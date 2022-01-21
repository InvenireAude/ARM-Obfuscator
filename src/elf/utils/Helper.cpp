/*
 * File: Helper.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Helper.h"


namespace ELF {
namespace Utils {


/*************************************************************************/
std::string Helper::StrToPrintableAndHex(const std::string& strData){

	const char *s=strData.c_str();

	std::string strResult;

	char c;
	bool bFirst=true;
	while( (c=*s++) != 0 ){

		if(!bFirst)
			strResult+=' ';
		else
			bFirst=false;

		if(c > ' ')
			strResult+=c;
		  else
			strResult+='.';
		strResult+=':';
		strResult+=CharToHex(c);
	}

	return strResult;

}
/*************************************************************************/
std::string Helper::CharToHex(const char cChar){
	std::string strResult;

	strResult = HexDigit( (cChar >> 4) & 0x0f);
	strResult += HexDigit(cChar & 0x0f);
	return strResult;
}
/*************************************************************************/
std::string Helper::StrToPrintableOrHex(const std::string& strData){

	const char *s=strData.c_str();

	std::string strResult;

	unsigned char c;

	while( (c=*s++) != 0 ){

		if(c > ' ')
			strResult+=c;
		  else{
			strResult+='[';
			strResult+=CharToHex(c);
			strResult+=']';
		  }
	}

	return strResult;

}
/*************************************************************************/
char Helper::HexDigit(int  iValue){
	return HexDigit((unsigned char)iValue);
}
/*************************************************************************/
char  Helper::HexDigit(unsigned char cValue){

	if(cValue < 10)
		return cValue + '0';
	else
	  if(cValue < 16)
		return cValue - 10 + 'A';
	  else
	    throw Tools::Exception()<<"Hex value out of range.";

}
/*************************************************************************/
unsigned char Helper::HexValue(char cValue){

	if(cValue >= '0' && cValue <= '9')
		return cValue - '0';
	else if(cValue >= 'A' && cValue <= 'F')
		return cValue - 'A' + 10;
	else if(cValue >= 'a' && cValue <= 'f')
		return cValue - 'a' + 10;
	  else
	     throw Tools::Exception()<<"Hex value out of range:"<<(int)cValue<<"["<<cValue<<"]";

}
/*************************************************************************/
void  Helper::BinarytoHex(const void *pData, size_t iDataLen, std::string& strOutput){

  const unsigned char* sData = reinterpret_cast<const unsigned char*>(pData);

	while(iDataLen){
		strOutput+=HexDigit(*sData >> 4);
		strOutput+=HexDigit(*sData & 0x0F);
		sData++;
		iDataLen--;
	}

}
/*************************************************************************/
std::string  Helper::BinarytoHex(const void *sData, size_t iDataLen){

  std::string strValue;
  
  BinarytoHex(sData, iDataLen, strValue);
  return strValue;

}
/*************************************************************************/
}
}
