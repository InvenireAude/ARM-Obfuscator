/*
 * File: DefaultOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DefaultOperand.h"
#include "../Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {

/*************************************************************************/
DefaultOperand::DefaultOperand(){
}

/*************************************************************************/
DefaultOperand::~DefaultOperand() throw(){
}

/*************************************************************************/
void DefaultOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{
	//pField->setValue(iOpCode, iValue);
}
/*************************************************************************/
int32_t DefaultOperand::getValue(uint32_t iOpCode) const{
	return pField->getValue(iOpCode);
}
/*************************************************************************/
}
}
}
}
}
