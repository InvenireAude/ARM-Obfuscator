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
	
	Symbol* add(Symbol::Type iType, uint64_t iAddress, uint64_t iSize, const std::string& strName);

	inline Symbol* addCode(uint64_t iAddress, uint64_t iSize, const std::string& strName ){
		return add(Symbol::ST_Code, iAddress, iSize, strName);
	}

	inline Symbol* addData(uint64_t iAddress, uint64_t iSize, const std::string& strName ){
		return add(Symbol::ST_Data, iAddress, iSize, strName);
	}

	typedef std::map<uint64_t, Symbol*> SymbolSet;
	typedef std::unordered_map<std::string, std::unique_ptr<Symbol> >  SymbolMap; 

	inline const SymbolSet& getSymbols(Symbol::Type iType)const{

		if(iType >= Symbol::ST_NumTypes)
			throw Tools::Exception()<<"Symbol id out of range: "<<iType;

		return tabSymbolSets[iType];
	}

	// inline bool checkType(Symbol::Type iType, uint64_t iAddress){
	// 	SymbolMap::iterator it = mapSymbols.lower_bound(iAddress);
	// 	if(it == mapSymbols.begin())
	// 		return false;
	// 	it--;
	// 	return  (iAddress >= it->second->getAddress()) &&
	// 			(iAddress <= it->second->getAddress() + it->second->getSize());
	// }

	InstructionList& getInstructions(){
		return lstInstructions;
	}

	Symbol* getSymbol(const std::string& strName){
		SymbolMap::iterator it = mapSymbols.find(strName);

		if(it == mapSymbols.end()){
			throw Tools::Exception()<<"Symbol not found: "<<strName;
		}

		return it->second.get();
	}

protected:

	SymbolMap mapSymbols;
	SymbolSet tabSymbolSets[Symbol::ST_NumTypes];

	InstructionList lstInstructions;
};
/*************************************************************************/
}

#endif /* _ARMOB_DiscoveredSymbols_H_ */
