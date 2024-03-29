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

#include <asm/GenericDetail.h>
#include <asm/Item.h>
#include <asm/ItemList.h>

#include "Symbol.h"
#include <asm/GenericDetailFactory.h>

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

};
/*************************************************************************/
}

#endif /* _ARMOB_DiscoveredSymbols_H_ */
