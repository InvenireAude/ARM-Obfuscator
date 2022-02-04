/*
 * File: DecodedInstruction.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_DecodedInstruction_H_
#define _ASM_ARM_ARM64_DecodedInstruction_H_


namespace ASM {
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
protected:

};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_DecodedInstruction_H_ */
