/*
 * File: Operand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Operand_H_
#define _ASM_ARM_ARM64_Spec_Operand_H_

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

    ~Operand() throw();

    virtual void    setValue(uint32_t& iOpCode, int32_t iValue) const = 0;
    virtual int32_t getValue(uint32_t iOpCode) const = 0;

    inline bool isMemoryReference()const{
        return bIsMemoryReference;
    }

    protected:
        Operand();
        bool bIsMemoryReference;
};
/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Operand_H_ */
