/*
 * File: SectionBook.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_SectionBook_H_
#define _ELF_SectionBook_H_

#include <tools/common.h>

#include "Specification.h"

#include "elf32/elf32.h"
#include "elf64/elf64.h"

namespace ELF {

/*************************************************************************/
/** The SectionBook class.
 *
 */

class SectionBook {
public:

	struct PLTInfo {
		size_t iPLTPrologSize;
		size_t iPLTEntrySize;
	};


	bool getPLTInfo(const Elf64::Header* pHeader, PLTInfo* pPLTInfo)const;
	bool getPLTInfo(const Elf32::Header* pHeader, PLTInfo* pPLTInfo)const;

	static SectionBook TheInstance;

	SectionBook();

protected:

 	struct CMHash{
	typedef std::pair< Class, Machine> KeyType;
    std::size_t operator()(const KeyType& k) const{
      using std::size_t;
      using std::hash;
      return (hash<size_t>()(k.first) ^ hash<size_t>()(k.second));
    }
  };

	typedef std::unordered_map< std::pair< Class, Machine>, PLTInfo, CMHash> PLTInfoMap;

	static PLTInfoMap ThePltInfo;
	
};

/*************************************************************************/
}

#endif /* _ELF_SectionBook_H_ */
