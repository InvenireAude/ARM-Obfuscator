/*
 * File: Symbol.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Symbol_H_
#define _ARMOB_Symbol_H_

#include <tools/common.h>
#include <list>

#include <asm/GenericInstruction.h>

namespace ARMOB {

/*************************************************************************/
/** The Symbol class.
 *
 */
typedef std::list<ASM::GenericInstruction> InstructionList;

class Symbol {
public:


	enum Type : uint8_t {
		ST_Other = 0,
		ST_Code  = 1,
		ST_Data  = 2,
		ST_NumTypes = 3
	};

	static const std::string CNoName;

	Symbol(Type iType, uint64_t iAddress, uint64_t iSize = 0L, const std::string& = CNoName);

	inline Type getType()const{
		return iType;
	}

	inline uint64_t getAddress()const{
		return iAddress;
	}

	inline uint64_t getSize()const{
		return iSize;
	}

	inline void setSize(uint64_t iSize){
	   this->iSize = iSize;
	}

	inline const std::string& getName()const{
		return strName;
	}

	inline void setName(const std::string& strName){
	   this->strName = strName;
	}

	InstructionList::iterator getStart(){
		return itStart;
	}

	InstructionList::const_iterator getStart()const{
		return itStart;
	}

	InstructionList::iterator getEnd(){
		return itEnd;
	}

	InstructionList::const_iterator getEnd()const{
		return itEnd;
	}

	void setStart(const InstructionList::iterator& it){
		itStart = it;
	}

	void setEnd(const InstructionList::iterator& it){
		itEnd = it;
	}

protected:
	uint64_t     iAddress;
	uint64_t     iSize;
	std::string  strName;
	Type         iType;

	InstructionList::iterator itStart;
	InstructionList::iterator itEnd;
};

/*************************************************************************/
}

#endif /* _ARMOB_Symbol_H_ */
