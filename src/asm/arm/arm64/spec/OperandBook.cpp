/*
 * File: OperandBook.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "OperandBook.h"

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

const OperandBook::SpecByIdMap OperandBook::TheSpecById = {
#include "auto_operand_specs.h.in"
 };
/*************************************************************************/
static OperandBook TheInstance;
/*************************************************************************/
OperandBook::OperandBook(){
}
/*************************************************************************/
OperandBook::~OperandBook() throw(){
}
/*************************************************************************/
const char* OperandBook::getSpec(OperandId iOperandId)const{

	SpecByIdMap::const_iterator it = TheSpecById.find(iOperandId);

	if(it == TheSpecById.end()){
		throw Tools::Exception()<<"No specification for operand: "<<(int)iOperandId;
	}

	return it->second;
};
/*************************************************************************/
}
}
}
}
