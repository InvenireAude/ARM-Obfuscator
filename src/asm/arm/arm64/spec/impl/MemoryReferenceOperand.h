/*
 * File: MemoryReferenceOperand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Impl_MemoryReferenceOperand_H_
#define _ASM_ARM_ARM64_Spec_Impl_MemoryReferenceOperand_H_

#include <tools/common.h>

#include "DefaultOperand.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
class Field;
namespace Impl {

/*************************************************************************/
/** The MemoryReferenceOperand class.
 *
 */
class MemoryReferenceOperand : public DefaultOperand {
public:

	virtual ~MemoryReferenceOperand() throw();
	MemoryReferenceOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift);

	virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const;
    virtual int32_t getValue(uint32_t iOpCode) const;

	virtual void disassemble(uint32_t iOpCode, std::ostream& os) const;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_MemoryReferenceOperand_H_ */
