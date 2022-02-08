/*
 * File: Decoder.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Decoder_H_
#define _ASM_ARM_ARM64_Decoder_H_

#include <tools/common.h>

namespace ASM {
class GenericInstruction;
namespace ARM {
namespace ARM64 {

namespace Spec{
	class Encoding;
}
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

	virtual void print(std::ostream& os, const SymbolResolver* pSymbolResover = nullptr);
	bool checkMemoryReference()const;

protected:
	const GenericInstruction *pGenericInstruction;
	const Spec::Encoding     *pEncoding;
};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_Decoder_H_ */
