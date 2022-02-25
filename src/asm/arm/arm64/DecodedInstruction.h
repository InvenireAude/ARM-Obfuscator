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

	const DecodedInstruction& setOperand(Spec::OperandId iOperand, uint32_t iValue)const;

	inline const DecodedInstruction& setOperands(Spec::OperandId iOperand1, uint32_t iValue1, 
							Spec::OperandId iOperand2, uint32_t iValue2){
		  setOperand(iOperand1, iValue1);
		  return setOperand(iOperand2, iValue2);
	  }

	inline const DecodedInstruction& setOperands(Spec::OperandId iOperand1, uint32_t iValue1, 
							Spec::OperandId iOperand2, uint32_t iValue2,
							Spec::OperandId iOperand3, uint32_t iValue3){
		  setOperand(iOperand1, iValue1);
		  setOperand(iOperand2, iValue2);
		  return setOperand(iOperand3, iValue3);
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
