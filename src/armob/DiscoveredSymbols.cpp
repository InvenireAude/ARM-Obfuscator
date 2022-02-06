/*
 * File: DiscoveredSymbols.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DiscoveredSymbols.h"


namespace ARMOB {

/*************************************************************************/
DiscoveredSymbols::DiscoveredSymbols(){
	
}

/*************************************************************************/
DiscoveredSymbols::~DiscoveredSymbols() throw(){
	
}
/*************************************************************************/
void DiscoveredSymbols::add(Symbol::Type iType, uint64_t iAddress, uint64_t iSize, const std::string& strName){

    //TODO check for overlaps
    
    SymbolMap::iterator it = mapSymbols.find(iAddress);

    if(it == mapSymbols.end()){
        mapSymbols[iAddress].reset(new Symbol(iType, iAddress, iSize, strName));
        tabSymbolSets[iType].insert(iAddress);
    }else{
        if(iSize){
            it->second->setSize(iSize);
        }

        if(strName.compare(Symbol::CNoName) != 0){
            it->second->setName(strName);
        }
    }

}
/*************************************************************************/
}
