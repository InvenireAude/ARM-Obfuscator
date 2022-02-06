/*
 * File: RegisterOperand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Impl_RegisterOperand_H_
#define _ASM_ARM_ARM64_Spec_Impl_RegisterOperand_H_

#include <tools/common.h>

#include "DefaultOperand.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
class Field;
namespace Impl {

/*************************************************************************/
/** The RegisterOperand class.
 *
 */
class RegisterOperand : public DefaultOperand {
public:

	virtual ~RegisterOperand() throw();
	RegisterOperand(const Field* tabFields, OperandId iOperand, uint8_t iSize);

   virtual void disassemble(uint32_t iOpCode, std::ostream& os) const;

protected:

  const std::string& strRegisterName;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_RegisterOperand_H_ */
