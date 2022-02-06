/*
 * File: RegisterOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "RegisterOperand.h"
#include "../Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {


const std::string& _sizeToRegisterName(uint8_t iSize){

	static const std::string _w("w");
	static const std::string _x("x");
	static const std::string _r("r");

	if(iSize == 32){
		return _w;
	}	
	if(iSize == 64){
		return _x;
	}

	return _r;
}
/*************************************************************************/
RegisterOperand::RegisterOperand(const Field* tabFields, OperandId iOperand, uint8_t iSize):
DefaultOperand(tabFields, iOperand, 0),
strRegisterName(_sizeToRegisterName(iSize)){}
/*************************************************************************/
RegisterOperand::~RegisterOperand() throw(){
}
/*************************************************************************/
void RegisterOperand::disassemble(uint32_t iOpCode, std::ostream& os)const{
	os<<strRegisterName<<getValue(iOpCode);
}
/*************************************************************************/
}
}
}
}
}
