/*
 * File: Identification.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Identification.h"

#include "Content.h"

#include <string.h>

namespace ELF {


/*************************************************************************/
Identification::Identification(const Content* pContent){

	const uint8_t* pData = pContent->getData(0x0L, EI_NIDENT);

	memcpy(_d, pData, EI_NIDENT);

	if( _d[EI_MAG0] != 0x7f ||
		_d[EI_MAG1] != 'E' ||
		_d[EI_MAG2] != 'L' ||
		_d[EI_MAG3] != 'F'){
			throw Tools::Exception()<<"Identification failed: "<<"magic number is incorrect.";
		}


	std::cerr<<"Class   is: "<<(int)_d[EI_CLASS]<<std::endl;
	std::cerr<<"Data    is: "<<(int)_d[EI_DATA]<<std::endl;
	std::cerr<<"Version is: "<<(int)_d[EI_VERSION]<<std::endl;

	std::cerr<<"Class   is: "<<Map::Class.getString(_d[EI_CLASS])<<std::endl;
}
/*************************************************************************/
Identification::~Identification() throw(){
}

/*************************************************************************/
Class Identification::getClass()const{
	return static_cast<Class>(_d[EI_CLASS]);
}
/*************************************************************************/
Data Identification::getDataEncoding()const{
	return static_cast<Data>(_d[EI_DATA]);
}
/*************************************************************************/
Version Identification::getVersion()const{
	return static_cast<Version>(_d[EI_VERSION]);
}
/*************************************************************************/
OSABI Identification::getOSABI()const{
	return static_cast<OSABI>(_d[EI_OSABI]);
}
/*************************************************************************/
}
;