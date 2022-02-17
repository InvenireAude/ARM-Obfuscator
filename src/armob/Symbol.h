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

#include <asm/GenericDetail.h>
#include <asm/Item.h>
#include <asm/ItemList.h>

namespace ARMOB {

/*************************************************************************/
/** The Symbol class.
 *
 */

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


	ASM::ItemList::iterator getStart()const{
		if(!itStart){
			throw Tools::Exception()<<"Instruction start not set for symbol: "<<strName;
		}
		return itStart;
	}

	ASM::ItemList::iterator getEnd()const{
		if(!itEnd){
			throw Tools::Exception()<<"Instruction end not set for symbol: "<<strName;
		}
		return itEnd;
	}

	void setStart(ASM::ItemList::iterator itStart){
		this->itStart = itStart;
		this->itEnd = itStart;
	}

	void setEnd(ASM::ItemList::iterator itEnd){
		this->itEnd = itEnd;
	}

	inline bool hasInstructions()const{
		return ! !itStart;
	}

	void updateSize();
	
	template<typename F>
	void forAll(F &&f) { 
		
		 if(!hasInstructions()){
			 return;
		 }

		ASM::ItemList::iterator itCursor = getStart();

		while(true){

			f(itCursor);

			if( itCursor->isTail() ||
				itCursor == getEnd())
					break; //strange ...

			++itCursor;
			}
		}

	template<typename F>
	void forAllSkipNew(F &&f) { 
		
		 if(!hasInstructions()){
			 return;
		 }

		ASM::ItemList::iterator itCursor = getStart();
		while(true){
			ASM::ItemList::iterator itNext = itCursor.next();
			f(itCursor);
			if( itCursor->isTail() ||
				itCursor == getEnd())
					break; //strange ...

			itCursor = itNext;
			}
		}

	
	template<typename F>
	void withFirst(F &&f) { 
		
		 if(!hasInstructions()){
			 return;
		 }

		ASM::ItemList::iterator itCursor = getStart();
		f(itCursor);
	}

protected:
	uint64_t     iAddress;
	uint64_t     iSize;
	std::string  strName;
	Type         iType;

	ASM::ItemList::iterator itStart;
	ASM::ItemList::iterator itEnd;
};

/*************************************************************************/
}

#endif /* _ARMOB_Symbol_H_ */
