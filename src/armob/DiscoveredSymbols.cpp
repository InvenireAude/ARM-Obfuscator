/*
 * File: DiscoveredSymbols.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DiscoveredSymbols.h"


namespace ARMOB {

/*************************************************************************/
DiscoveredSymbols::DiscoveredSymbols():
  ptrGenericDetailFactory(new ASM::GenericDetailFactory()){
}
/*************************************************************************/
DiscoveredSymbols::~DiscoveredSymbols() throw(){
	
}
/*************************************************************************/
Symbol* DiscoveredSymbols::add(Symbol::Type iType, uint64_t iAddress, uint64_t iSize, const std::string& strName){

    //TODO check for overlaps
    Symbol* pResult = nullptr;

    // SymbolMap::iterator it = mapSymbols.find(iAddress);
    SymbolMap::iterator it = mapSymbols.find(strName);

    if(it == mapSymbols.end()){
        mapSymbols[strName].reset(pResult = new Symbol(iType, iAddress, iSize, strName));
        tabSymbolSets[iType][iAddress] = pResult;
    }else{
        pResult = it->second.get();
        if(iSize){
            pResult->setSize(iSize);
        }

        if(strName.compare(Symbol::CNoName) != 0){
            pResult->setName(strName);
        }
    }

    return pResult;
}
/*************************************************************************/
}
