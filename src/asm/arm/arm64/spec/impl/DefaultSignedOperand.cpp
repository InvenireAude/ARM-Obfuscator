/*
 * File: DefaultSignedOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DefaultSignedOperand.h"
#include "../Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {

/*************************************************************************/
DefaultSignedOperand::DefaultSignedOperand(const Field* tabFields, OperandId iOperand, uint8_t iShift):
DefaultOperand(tabFields, iOperand, iShift){}
/*************************************************************************/
DefaultSignedOperand::~DefaultSignedOperand() throw(){
}

/*************************************************************************/
void DefaultSignedOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{
	//pField->setValue(iOpCode, iValue >> iShift);
}
/*************************************************************************/
int32_t DefaultSignedOperand::getValue(uint32_t iOpCode) const{
	return pField->getSignedValue(iOpCode) << iShift;
}
/*************************************************************************/
}
}
}
}
}
