/*
 * File: DecodedInstruction.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_DecodedInstruction_H_
#define _ASM_ARM_ARM64_DecodedInstruction_H_

#include <asm/arm/arm64/spec/enums.h>
#include <asm/arm/arm64/spec/Encoding.h>

namespace ASM {
class GenericDetail;
class Item;
namespace ARM {
namespace ARM64 {

/*************************************************************************/
/** The DecodedInstruction class.
 *
 */
class DecodedInstruction {
public:

	virtual ~DecodedInstruction() throw();
	DecodedInstruction();

	class SymbolResolver {
		public:
		virtual ~SymbolResolver(){};
		virtual void print(std::ostream& os, uint64_t iAddress)const = 0;
	};

	DecodedInstruction(GenericDetail* pGenericDetail);
	DecodedInstruction(GenericDetail* pGenericDetail, Spec::EncodingId iEncodingId);
	DecodedInstruction(Item& item);
	DecodedInstruction(Item& item, Spec::EncodingId iEncodingId);

	virtual void print(std::ostream& os, const SymbolResolver* pSymbolResover = nullptr);
	
	bool checkMemoryReference()const;
	
	void updateOpcodeReference(size_t iDataSegmentShift)const;

	void setOperand(Spec::OperandId iOperand, uint32_t iValue)const;

	template<Spec::OperandId iOperand1, Spec::OperandId iOperand2>
	  inline void setOperands(uint32_t iValue1, uint32_t iValue2){
		  setOperand(iOperand1, iValue1);
		  setOperand(iOperand2, iValue2);
	  }

	template<Spec::OperandId iOperand1, Spec::OperandId iOperand2, Spec::OperandId iOperand3>
	  inline void setOperands(uint32_t iValue1, uint32_t iValue2, uint32_t iValue3){
		  setOperand(iOperand1, iValue1);
		  setOperand(iOperand2, iValue2);
		  setOperand(iOperand3, iValue3);
	  }

	template<Spec::OperandId iOperand1, Spec::OperandId iOperand2, Spec::OperandId iOperand3, Spec::OperandId iOperand4>
	  inline void setOperands(uint32_t iValue1, uint32_t iValue2, uint32_t iValue3, uint32_t iValue4 ){
		  setOperand(iOperand1, iValue1);
		  setOperand(iOperand2, iValue2);
		  setOperand(iOperand3, iValue3);
		  setOperand(iOperand4, iValue4);
	  }

protected:

	GenericDetail *pGenericDetail;
	const Spec::Encoding  *pEncoding;
};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_DecodedInstruction_H_ */
