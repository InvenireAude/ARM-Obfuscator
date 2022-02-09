/*
 * File: Operand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Operand_H_
#define _ASM_ARM_ARM64_Spec_Operand_H_

#include <tools/common.h>

#include "enums.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {
/*************************************************************************/
/** The Operand class.
 *
 */
class Operand {
public:

    virtual ~Operand() throw();

    virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const = 0;
    virtual int32_t getValue(uint32_t iOpCode) const = 0;
    virtual int32_t applyMemoryReference(uint64_t iAddress, uint32_t iOpCode) const;

    virtual void    disassemble(uint32_t iOpCode, std::ostream& os) const = 0;

    inline bool isMemoryReference()const{
        return bIsMemoryReference;
    }

    inline OperandId getOperandId()const{
        return iOperandId;
    }

    protected:
        Operand(OperandId iOperandId, bool bIsMemoryReference = false);
        bool bIsMemoryReference;

        OperandId iOperandId;

        void printHex(int32_t iValue, std::ostream& os) const;
};
/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Operand_H_ */
