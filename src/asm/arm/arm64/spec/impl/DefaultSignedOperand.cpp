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
DefaultSignedOperand::DefaultSignedOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift):
DefaultOperand(tabFields, iOperandId, iShift){}
/*************************************************************************/
DefaultSignedOperand::~DefaultSignedOperand() throw(){
}

/*************************************************************************/
void DefaultSignedOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{
	pField->setValue(iOpCode, iValue >> iShift);
	std::cout<<"updated field[2]: "<<sName<<"::"<<(void*)(long)iOpCode<<std::endl;
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
