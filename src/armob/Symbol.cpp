/*
 * File: Symbol.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Symbol.h"


namespace ARMOB {
 const std::string Symbol::CNoName("__no_name__");
/*************************************************************************/
Symbol::Symbol(Type iType, uint64_t iAddress, uint64_t iSize, const std::string& strName):
 iType(iType),
 iAddress(iAddress),
 iSize(iSize),
 strName(strName),
 pStart(nullptr),
 pEnd(nullptr){
     std::cerr<<"New symbol: "<<strName<<", at: "<<(void*)iAddress<<", sz: "<<(void*)iSize<<std::endl;
}
/*************************************************************************/
}
