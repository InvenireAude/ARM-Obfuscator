/*
 * File: ValueMap.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "ValueMap.h"


namespace Tools {

/*************************************************************************/
ValueMap::ValueMap(const std::string& strName, const std::initializer_list< std::pair<int, std::string> >& values):
	strName(strName){

	for(const auto& e: values){
		hmValues[e.first] = e.second;
	}
}
/*************************************************************************/
ValueMap::~ValueMap() throw(){
}
/*************************************************************************/
}
