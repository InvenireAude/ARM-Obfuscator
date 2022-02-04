/*
 * File: FieldBook.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "FieldBook.h"

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/

const FieldBook::NameByIdMap FieldBook::TheNameById = {
#include "auto_field_names.h.in"
 };
/*************************************************************************/
const FieldBook FieldBook::TheInstance;
/*************************************************************************/
FieldBook::FieldBook(){

	for(const auto& e : TheNameById){
		hmIdByName[e.second] = e.first;
	}
}
/*************************************************************************/
FieldBook::~FieldBook() throw(){
}
/*************************************************************************/
const char* FieldBook::getName(FieldId iFieldId)const{

	NameByIdMap::const_iterator it = TheNameById.find(iFieldId);

	if(it == TheNameById.end()){
		return "???";
	}

	return it->second;
};
/*************************************************************************/
const FieldId FieldBook::getId(const std::string& strName)const{

	IdByNameMap::const_iterator it = hmIdByName.find(strName);

	if(it == hmIdByName.end()){
		throw Tools::Exception()<<"FieldBook not found: "<<strName;
	}

	return it->second;
};
/*************************************************************************/
}
}
}
}
