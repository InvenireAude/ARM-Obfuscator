/*
 * File: enums.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_enums_H_
#define _ASM_ARM_ARM64_Spec_enums_H_

#include <inttypes.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/

enum InstructionId : uint16_t {
#include "auto_instruction_enums.h.in"
};

enum ClassId : uint16_t {
#include "auto_class_enums.h.in"
};

enum OperandId : uint16_t {
#include "auto_operand_enums.h.in"
};

enum EncodingId : uint16_t {
#include "auto_encoding_enums.h.in"
};

enum FieldId : uint8_t {
#include "auto_field_enums.h.in"
};


/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_enums_H_ */
