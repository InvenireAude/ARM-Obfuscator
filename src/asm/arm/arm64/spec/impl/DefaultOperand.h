/*
 * File: DefaultOperand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Impl_DefaultOperand_H_
#define _ASM_ARM_ARM64_Spec_Impl_DefaultOperand_H_

#include <tools/common.h>

#include "../Operand.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
class Field;
namespace Impl {

/*************************************************************************/
/** The DefaultOperand class.
 *
 */
class DefaultOperand : public Spec::Operand {
public:

	virtual ~DefaultOperand() throw();
	DefaultOperand();

	virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const;
    virtual int32_t getValue(uint32_t iOpCode) const;

protected:

	const Field* pField;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_DefaultOperand_H_ */
