/*
 * File: Encoding.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Encoding_H_
#define _ASM_ARM_ARM64_Spec_Encoding_H_

#include <tools/common.h>

#include "enums.h"
#include "Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The Encoding class.
 *
 */
struct Encoding {

		static const int CMaxFields = 10;

		EncodingId 		    iEncodingId;
		InstructionId       iInstructionId;
		ClassId 	        iClass;
		InstructionId       iAliasInstructionId;
		uint32_t      		opCode;
		uint32_t      		opCodeMask;
		Field               fields[CMaxFields];
		OperandId           operands[CMaxFields];
		//InstructionFlags    flags; // ?
	};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Encoding_H_ */
