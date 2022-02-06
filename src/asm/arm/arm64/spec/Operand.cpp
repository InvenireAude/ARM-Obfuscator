/*
 * File: Operand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Operand.h"


namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
Operand::Operand(OperandId iOperandId, bool bIsMemoryReference):bIsMemoryReference(bIsMemoryReference){
}
/*************************************************************************/
Operand::~Operand() throw(){
}
/*************************************************************************/
void Operand::printHex(int32_t iValue, std::ostream& os)const{
	 
	if(iValue & 0x80000000){
		os<<"-";
		iValue =~iValue;
	}
	
	os<<"0x"<<std::hex<<iValue<<std::dec;
}
/*************************************************************************/
}
}
}
}
