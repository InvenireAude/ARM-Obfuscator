/*
 * File: DiscoveredSymbols.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_DiscoveredSymbols_H_
#define _ARMOB_DiscoveredSymbols_H_

#include <tools/common.h>
#include <map>
#include <set>

#include "Symbol.h"

namespace ARMOB {

/*************************************************************************/
/** The DiscoveredSymbols class.
 *
 */
class DiscoveredSymbols {
public:

	virtual ~DiscoveredSymbols() throw();
	DiscoveredSymbols();
	
	void add(Symbol::Type iType, uint64_t iAddress, uint64_t iSize, const std::string& = Symbol::CNoName);

	inline void addCode(uint64_t iAddress, uint64_t iSize, const std::string& strName = Symbol::CNoName){
		add(Symbol::ST_Code, iAddress, iSize, strName);
	}

	inline void addData(uint64_t iAddress, uint64_t iSize, const std::string& strName = Symbol::CNoName){
		add(Symbol::ST_Data, iAddress, iSize, strName);
	}

	typedef std::set<uint64_t> SymbolSet;
	typedef std::map<uint64_t, std::unique_ptr<Symbol> >  SymbolMap; 

	inline const SymbolSet& getSymbols(Symbol::Type iType)const{

		if(iType >= Symbol::ST_NumTypes)
			throw Tools::Exception()<<"Symbol id out of range: "<<iType;

		return tabSymbolSets[iType];
	}

	inline bool checkType(Symbol::Type iType, uint64_t iAddress){
		SymbolMap::iterator it = mapSymbols.lower_bound(iAddress);
		if(it == mapSymbols.begin())
			return false;
		it--;
		return  (iAddress >= it->second->getAddress()) &&
				(iAddress <= it->second->getAddress() + it->second->getSize());
	}
	
protected:

	
	SymbolMap mapSymbols;
	SymbolSet tabSymbolSets[Symbol::ST_NumTypes];
};
/*************************************************************************/
}

#endif /* _ARMOB_DiscoveredSymbols_H_ */
