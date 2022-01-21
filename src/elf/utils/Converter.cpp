/*
 * File: Converter.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Converter.h"


namespace ELF {
namespace Utils {

class ConverterIdent : public Converter{
public:

	virtual uint16_t convert(uint16_t iValue)const;
	virtual uint32_t convert(uint32_t iValue)const;
	virtual uint64_t convert(uint64_t iValue)const;

};
/*************************************************************************/
uint16_t ConverterIdent::convert(uint16_t iValue)const{
	return iValue;
}
/*************************************************************************/
uint32_t ConverterIdent::convert(uint32_t iValue)const{
	return iValue;
}
/*************************************************************************/
uint64_t ConverterIdent::convert(uint64_t iValue)const{
	return iValue;
}
class ConverterSwap : public Converter{
public:

	virtual uint16_t convert(uint16_t iValue)const;
	virtual uint32_t convert(uint32_t iValue)const;
	virtual uint64_t convert(uint64_t iValue)const;

};
/*************************************************************************/
//TODO  the most portable ??
uint16_t ConverterSwap::convert(uint16_t iValue)const{
	return __builtin_bswap16(iValue);
}
/*************************************************************************/
uint32_t ConverterSwap::convert(uint32_t iValue)const{
	return __builtin_bswap32(iValue);
}
/*************************************************************************/
uint64_t ConverterSwap::convert(uint64_t iValue)const{
	return __builtin_bswap64(iValue);
}
/*************************************************************************/
Converter* Converter::Create(Data iEncoding){

	// TODO host or image in the big endian format ...

	switch(iEncoding){
		case ELFDATA2MSB:
			return new ConverterSwap();
		case ELFDATA2LSB:
			return new ConverterIdent();
		default:
		throw Tools::Exception()<<"Unsported conversion :"<<Map::Data.getString(iEncoding);
	}
}
/*************************************************************************/
}
}
