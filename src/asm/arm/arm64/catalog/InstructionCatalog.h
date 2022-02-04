/*
 * File: InstructionCatalog.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_InstructionCatalog_H_
#define _ASM_ARM_ARM64_InstructionCatalog_H_


namespace ASM {
namespace ARM {
namespace ARM64 {

/*************************************************************************/
/** The InstructionCatalog class.
 *
 */
class InstructionCatalog {
public:

	virtual ~InstructionCatalog() throw();
	InstructionCatalog();

	enum OpCode {
		INSN_ADD,
    	INSN_ADDS,
    	INSN_SUB,
    	INSN_SUBS,
    	INSN_B   	
	};

protected:

};

/*************************************************************************/
}
}
}

#endif /* _ASM_ARM_ARM64_InstructionCatalog_H_ */
