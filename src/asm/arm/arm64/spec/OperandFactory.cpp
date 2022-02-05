/*
 * File: OperandFactory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "OperandFactory.h"

#include "impl/DefaultOperand.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
Operand* createOperand(const Encoding* pEncoding, OperandId iOperandId){
    return new Impl::DefaultOperand();
}
/*************************************************************************/
// OperandFactory::OperandFactory(){

// }

// /*************************************************************************/
// OperandFactory::~OperandFactory() throw(){

// }
/*************************************************************************/
}
}
}
}
