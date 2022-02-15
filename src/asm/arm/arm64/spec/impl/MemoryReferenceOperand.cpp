/*
 * File: MemoryReferenceOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "MemoryReferenceOperand.h"
#include "../Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {

/*************************************************************************/
MemoryReferenceOperand::MemoryReferenceOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift):
DefaultOperand(tabFields, iOperandId, iShift, true){}
/*************************************************************************/
MemoryReferenceOperand::~MemoryReferenceOperand() throw(){
}
/*************************************************************************/
void MemoryReferenceOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{
	pField->setValue(iOpCode, iValue >> iShift);
	std::cout<<"updated field[3]"<<sName<<"::"<<(void*)(long)iOpCode<<std::endl;
}
/*************************************************************************/
int32_t MemoryReferenceOperand::getValue(uint32_t iOpCode) const{
	return pField->getSignedValue(iOpCode) << iShift;
}
/*************************************************************************/
void MemoryReferenceOperand::disassemble(uint32_t iOpCode, std::ostream& os)const{
	printHex(getValue(iOpCode), os);
}
/*************************************************************************/
}
}
}
}
}
