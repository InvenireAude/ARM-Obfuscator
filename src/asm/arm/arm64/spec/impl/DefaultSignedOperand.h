/*
 * File: DefaultSignedOperand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Impl_DefaultSignedOperand_H_
#define _ASM_ARM_ARM64_Spec_Impl_DefaultSignedOperand_H_

#include <tools/common.h>

#include "DefaultOperand.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
class Field;
namespace Impl {

/*************************************************************************/
/** The DefaultSignedOperand class.
 *
 */
class DefaultSignedOperand : public DefaultOperand {
public:

	virtual ~DefaultSignedOperand() throw();
	DefaultSignedOperand(const Field* tabFields, OperandId iOperand, uint8_t iShift);

	virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const;
    virtual int32_t getValue(uint32_t iOpCode) const;

};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_DefaultSignedOperand_H_ */
