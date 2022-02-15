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

#include "../Field.h"
#include "../FieldBook.h"

#include "../Encoding.h"
#include "../EncodingBook.h"

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
	DefaultOperand(const Field* tabFields, OperandId iOperandId, uint8_t iShift, bool bIsMemoryReference = false);

	virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const;
    virtual int32_t getValue(uint32_t iOpCode) const;

    virtual void disassemble(uint32_t iOpCode, std::ostream& os) const;

protected:

	const Field* pField;
	uint8_t      iShift;
	const char*  sName;

};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_DefaultOperand_H_ */
