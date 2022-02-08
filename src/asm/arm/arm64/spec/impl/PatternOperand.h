/*
 * File: PatternOperand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Impl_PatternOperand_H_
#define _ASM_ARM_ARM64_Spec_Impl_PatternOperand_H_

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
/** The PatternOperand class.
 *
 */
class PatternOperand : public Spec::Operand {
public:

	virtual ~PatternOperand() throw();
	PatternOperand(const Field* tabFields, OperandId iOperand, uint8_t iShift, const std::string& strSpec, bool bIsMemoryReference = false);

	virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const;
    virtual int32_t getValue(uint32_t iOpCode) const;

    virtual void disassemble(uint32_t iOpCode, std::ostream& os) const;

protected:
	static const int CMaxFields = 10;
	
	const Field*  tabUsedFields[CMaxFields];

	uint8_t      iShift;
	std::string strName;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Impl_PatternOperand_H_ */
