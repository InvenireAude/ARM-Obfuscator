/*
 * File: OperandFactory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "OperandFactory.h"

#include "impl/DefaultOperand.h"
#include "impl/DefaultSignedOperand.h"
#include "impl/RegisterOperand.h"
#include "impl/MemoryReferenceOperand.h"

#include "EncodingBook.h"
#include "FieldBook.h"
#include "OperandBook.h"

#include <set>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

static std::set< std::string > _TheRegisterOperands({
    "Rd", "Rn", "Rm", "Rt", "Rt2"
});
/*************************************************************************/
Operand* OperandFactory::CreateOperand(const Encoding* pEncoding, OperandId iOperandId){

    const std::string& strSpec(OperandBook::TheInstance.getSpec(iOperandId));

    if(pEncoding->iClass == C_loadlit && strSpec.compare("imm19") == 0){
        return new Impl::MemoryReferenceOperand(pEncoding->fields, iOperandId, 2);
    }

    if(pEncoding->iClass == C_branch_imm && strSpec.compare("imm26") == 0){
        return new Impl::MemoryReferenceOperand(pEncoding->fields, iOperandId, 2);
    }

    if(_TheRegisterOperands.count(strSpec)){
        return new Impl::RegisterOperand(pEncoding->fields, iOperandId, 64);
    }

    return new Impl::DefaultOperand(pEncoding->fields, iOperandId, 0);
}
/*************************************************************************/
}
}
}
}
