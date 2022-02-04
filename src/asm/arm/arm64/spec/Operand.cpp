/*
 * File: Operand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Operand.h"

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

const Operand::SpecByIdMap Operand::TheSpecById = {
#include "auto_operand_specs.h.in"
 };
/*************************************************************************/
static Operand TheInstance;
/*************************************************************************/
Operand::Operand(){
}
/*************************************************************************/
Operand::~Operand() throw(){
}
/*************************************************************************/
const char* Operand::getSpec(OperandId iOperandId)const{

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
