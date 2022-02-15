/*
 * File: Decoder.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Decoder_H_
#define _ASM_ARM_ARM64_Decoder_H_

#include <tools/common.h>

#include <asm/arm/arm64/spec/enums.h>
#include <asm/arm/arm64/spec/Encoding.h>

namespace ASM {
class GenericInstruction;
namespace ARM {
namespace ARM64 {

/*************************************************************************/
/** The Decoder class.
 *
 */
class Decoder {
public:

	class SymbolResolver {
		public:
		virtual void print(std::ostream& os, uint64_t iAddress)const = 0;
	};

	virtual ~Decoder() throw();
	Decoder(const GenericInstruction* pGenericInstruction);
	Decoder(const GenericInstruction* pGenericInstruction, Spec::EncodingId iEncodingId);

	virtual void print(std::ostream& os, const SymbolResolver* pSymbolResover = nullptr);
	
	bool checkMemoryReference()const;
	
	void updateOpcodeReference(size_t iDataSegmentShift)const;

	void setOperand(Spec::OperandId iOperand, uint32_t iValue)const;

protected:
	const GenericInstruction *pGenericInstruction;
	const Spec::Encoding     *pEncoding;
};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_Decoder_H_ */
