/*
 * File: Symbol.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Symbol.h"


namespace ARMOB {

/*************************************************************************/
Symbol::Symbol(Type iType, uint64_t iAddress, uint64_t iSize, const std::string& strName):
 iType(iType),
 iAddress(iAddress),
 iSize(iSize),
 strName(strName){
}
/*************************************************************************/
}
