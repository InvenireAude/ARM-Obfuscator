/*
 * File: OperandFactory.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_OperandFactory_H_
#define _ASM_ARM_ARM64_Spec_OperandFactory_H_

#include <tools/common.h>

#include "enums.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

class Operand;
class Encoding;

/*************************************************************************/
/** The OperandFactory class.
 *
 */
class OperandFactory {
public:

	static Operand* CreateOperand(const Encoding* pEncoding, OperandId iOperandId);

protected:

};
/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_OperandFactory_H_ */
