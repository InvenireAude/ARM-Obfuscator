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
 strName(strName){
     std::cerr<<"New symbol: "<<strName<<", at: "<<(void*)iAddress<<", sz: "<<(void*)iSize<<std::endl;
}
/*************************************************************************/
void Symbol::updateSize(){

    size_t iSize = 0;

    forAll([&iSize](auto& it){
        iSize += it->getGenericDetail()->getOpCodeLength();
    });
    
    this->iSize = iSize;

    std::cout<<"New size: "<<(void*)(long)iSize<<std::endl;
}
/*************************************************************************/
}
