/*
 * File: Operand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Operand.h"

#include "OperandBook.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
Operand::Operand(OperandId iOperandId, bool bIsMemoryReference):
 iOperandId(iOperandId),
 bIsMemoryReference(bIsMemoryReference){
}
/*************************************************************************/
Operand::~Operand() throw(){
}
/*************************************************************************/
void Operand::printHex(int32_t iValue, std::ostream& os)const{
	 
	if(iValue & 0x80000000){
		os<<"-";
		iValue =~ iValue;
	}
	
	os<<"0x"<<std::hex<<iValue<<std::dec;
}
/*************************************************************************/
uint64_t Operand::applyMemoryReference(uint64_t iAddress, uint32_t iOpCode) const{
	if(bIsMemoryReference){
		return iAddress + getValue(iOpCode);
	}else{
		
		throw Tools::Exception()<<"Operand ["<<OperandBook::TheInstance.getSpec(iOperandId)
				<<"]apply memory reference called on non-memory operand.";
	}
}
/*************************************************************************/
void Operand::setMemoryReference(uint32_t& iOpCode, uint64_t iAddress, int64_t iReference)const{

	if(bIsMemoryReference){
		setValue(iOpCode, iReference - iAddress);
	}else{
		
		throw Tools::Exception()<<"Operand ["<<OperandBook::TheInstance.getSpec(iOperandId)
				<<"]apply memory reference called on non-memory operand.";
	}
}
/*************************************************************************/
}
}
}
}
