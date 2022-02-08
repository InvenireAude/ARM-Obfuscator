/*
 * File: InstructionFactory.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_InstructionFactory_H_
#define _ASM_InstructionFactory_H_

#include <tools/common.h>

namespace ASM {
class GenericInstruction;
/*************************************************************************/
/** The InstructionFactory class.
 *
 */
class InstructionFactory {
public:

	virtual ~InstructionFactory() throw();
	InstructionFactory(size_t iSize = 100000);

	GenericInstruction* allocate();

protected:

	GenericInstruction* pPool;
	size_t iSize;
	size_t iFirstFree;
};

/*************************************************************************/
}

#endif /* _ASM_InstructionFactory_H_ */
