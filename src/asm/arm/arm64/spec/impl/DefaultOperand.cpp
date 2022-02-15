/*
 * File: DefaultOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DefaultOperand.h"

#include "../OperandBook.h"
#include "../FieldBook.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {

/*************************************************************************/
static inline const Field* _fieldForOperand(const Field* tabFields, OperandId iOperandId){

    std::string strOperandSpec(OperandBook::TheInstance.getSpec(iOperandId));
    FieldId iFieldId = FieldBook::TheInstance.getId(strOperandSpec);
    
	for(int i=0; i<Encoding::CMaxFields && tabFields->iFieldId != F_None; i++, tabFields++){
		if(tabFields->iFieldId == iFieldId){
			return tabFields;
		}
	}

	throw Tools::Exception()<<"Cannot determine field for default operand: "
		<<OperandBook::TheInstance.getSpec(iOperandId);
}
/*************************************************************************/
DefaultOperand::DefaultOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift, bool bIsMemoryReference):
 Spec::Operand(iOperandId, bIsMemoryReference),
 pField(_fieldForOperand(tabFields, iOperandId)),
 iShift(iShift),
 sName(FieldBook::TheInstance.getName(pField->iFieldId)){
}
/*************************************************************************/
DefaultOperand::~DefaultOperand() throw(){
}

/*************************************************************************/
void DefaultOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{
	pField->setValue(iOpCode, iValue >> iShift);
	std::cout<<"updated field[1]:"<<sName<<"::"<<(void*)(long)iOpCode<<std::endl;
}
/*************************************************************************/
int32_t DefaultOperand::getValue(uint32_t iOpCode) const{
	return pField->getValue(iOpCode) << iShift;
}
/*************************************************************************/
void DefaultOperand::disassemble(uint32_t iOpCode, std::ostream& os)const{
	os<<sName<<":";
	printHex(getValue(iOpCode), os);
}
/*************************************************************************/
}
}
}
}
}
