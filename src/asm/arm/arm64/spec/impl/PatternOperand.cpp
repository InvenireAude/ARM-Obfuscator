/*
 * File: PatternOperand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "PatternOperand.h"

#include "../OperandBook.h"
#include "../FieldBook.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
namespace Impl {

/*************************************************************************/
static inline const Field* _fieldForOperand(const Field* tabFields, const std::string& strField){

    FieldId iFieldId = FieldBook::TheInstance.getId(strField);
    
	for(int i=0; i<Encoding::CMaxFields && tabFields->iFieldId != F_None; i++, tabFields++){
		if(tabFields->iFieldId == iFieldId){
			return tabFields;
		}
	}

	throw Tools::Exception()<<"Cannot determine field for pattern operand, field: "<<strField;
}
/*************************************************************************/
PatternOperand::PatternOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift,const std::string& strSpec, bool bIsMemoryReference, uint32_t iMask):
 Spec::Operand(iOperandId, bIsMemoryReference),
 iShift(iShift),
 strName(strSpec),
 iMask(iMask){
 
 size_t iStart = 0;
 size_t iNext  = 0; 
 int iFieldId = 0;

 while(iStart != std::string::npos){
	 iNext = strSpec.find(':',iStart);
	 std::string strValue(iNext != std::string::npos ? strSpec.substr(iStart, iNext - iStart) :  strSpec.substr(iStart));
	// std::cout<<"Pattern operand: "<<strSpec<<", n:"<<iFieldId<<" "<<strValue<<std::endl;
	
	 tabUsedFields[iFieldId++] = _fieldForOperand(tabFields, strValue);
	 iStart = iNext;
	 if(iStart != std::string::npos){
		 iStart++;
	 }
 } 

 tabUsedFields[iFieldId] = nullptr;


}
/*************************************************************************/
PatternOperand::~PatternOperand() throw(){
}

/*************************************************************************/
void PatternOperand::setValue(uint32_t& iOpCode, int32_t iValue) const{

	int iLastIdx = 0;

	iValue >>= iShift;

	std::cout<<"TEST setValue:"<<(void*)(long)iValue<<std::endl;

	while(tabUsedFields[iLastIdx] != nullptr){
		iLastIdx++;
	}	

	while(iLastIdx != 0){
		 iLastIdx--;
		 static uint32_t CFullMask = ~0;
		 uint32_t iMask = ~(CFullMask << tabUsedFields[iLastIdx]->iWidth);
		 std::cout<<"setValue:"<<(void*)(long)(iMask&iValue)<<FieldBook::TheInstance.getName(tabUsedFields[iLastIdx]->iFieldId)<<std::endl;
		 tabUsedFields[iLastIdx]->setValue(iOpCode, iMask & iValue);
		 iValue >>= tabUsedFields[iLastIdx]->iWidth;
	}

}
/*************************************************************************/
int32_t PatternOperand::getValue(uint32_t iOpCode) const{
	int32_t iValue = 0;
	
	for(int i=0; tabUsedFields[i] != nullptr; i++){
		iValue <<= tabUsedFields[i]->iWidth;
		iValue |= tabUsedFields[i]->getValue(iOpCode);
	}

	return iValue << iShift;
}
/*************************************************************************/
void PatternOperand::disassemble(uint32_t iOpCode, std::ostream& os)const{
	os<<strName<<":";
	printHex(getValue(iOpCode), os);
}
/*************************************************************************/
uint64_t PatternOperand::applyMemoryReference(uint64_t iAddress, uint32_t iOpCode) const{
	if(bIsMemoryReference){
		return (iAddress + getValue(iOpCode)) & iMask;
	}else{
		
		throw Tools::Exception()<<"Operand ["<<OperandBook::TheInstance.getSpec(iOperandId)
				<<"]apply memory reference called on non-memory operand.";
	}
}
/*************************************************************************/
void PatternOperand::setMemoryReference(uint32_t& iOpCode, uint64_t iAddress, int64_t iReference)const{
	
	            // std::cout<<"TEST set: "
                //   <<"\t"<<(void*)iAddress
                //    <<"\t"<<(void*)iReference
                //    <<"\t"<<(void*)(iReference - iAddress)
				//    <<"\t"<<(void*)(iReference - iAddress + ~iMask)
                //   <<std::endl;

	if(bIsMemoryReference){
		setValue(iOpCode, iReference - iAddress  + ~iMask);
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
}
