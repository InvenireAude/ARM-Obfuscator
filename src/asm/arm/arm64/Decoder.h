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

/*************************************************************************/
/** The Decoder class.
 *
 */
class Decoder {
public:

	virtual ~Decoder() throw();
	Decoder(const GenericInstruction* pGenericInstruction);

	virtual void print(std::ostream& os);
	
protected:
	const GenericInstruction* pGenericInstruction;
};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_Decoder_H_ */
