/*
 * File: Field.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Field.h"

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/

const Field::NameByIdMap Field::TheNameById = {
#include "auto_field_names.h.in"
 };
/*************************************************************************/
const Field Field::TheInstance;
/*************************************************************************/
Field::Field(){

	for(const auto& e : TheNameById){
		hmIdByName[e.second] = e.first;
	}
}
/*************************************************************************/
Field::~Field() throw(){
}
/*************************************************************************/
const char* Field::getName(FieldId iFieldId)const{

	NameByIdMap::const_iterator it = TheNameById.find(iFieldId);

	if(it == TheNameById.end()){
		return "???";
	}

	return it->second;
};
/*************************************************************************/
const FieldId Field::getId(const std::string& strName)const{

	IdByNameMap::const_iterator it = hmIdByName.find(strName);

	if(it == hmIdByName.end()){
		throw Tools::Exception()<<"Field not found: "<<strName;
	}

	return it->second;
};
/*************************************************************************/
}
}
}
}
