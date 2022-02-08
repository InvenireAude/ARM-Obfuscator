/*
 * File: GenericInstruction.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_GenericInstruction_H_
#define _ASM_GenericInstruction_H_

#include <tools/common.h>
#include <string.h>

namespace ASM {

/*************************************************************************/
/** The GenericInstruction class.
 *
 */
class GenericInstruction {
public:

	static const int CMaxBytes = 8;

	struct Addresses {
		uint64_t iOpCode;
		uint64_t iReference;
	};

	GenericInstruction(const uint8_t *pOpCode, 
				uint8_t  iLength,
				uint64_t iOpCodeAddress,
				uint64_t iReferenceAddress = 0L):
		iLength(iLength),
		adrOriginal({ iOpCodeAddress, iReferenceAddress }),
		adrCurrent({  iOpCodeAddress, iReferenceAddress }),
		pPrev(nullptr),
		pNext(nullptr),
		pReference(nullptr){

			if(iLength > CMaxBytes){
				throw Tools::Exception()<<"Opcode to long: "<<iLength;
			}

			memcpy(tOpCode, pOpCode, iLength);
		}

	inline const Addresses& getOriginaAddresses()const{
			return adrOriginal;
		}

	inline Addresses& getCurrentAddresses(){
			return adrCurrent;
	}

	inline const Addresses& getCurrentAddresses()const{
			return adrCurrent;
	}	

	inline const uint8_t* getOpcode()const{
		return tOpCode;
	};

	inline uint8_t getOpCodeLength()const{
		return iLength;
	}

	inline uint32_t getOpcodeS()const{
		if(iLength != 2)
			throw Tools::Exception()<<"Opcode is not 16bit size: "<<iLength;

		return *reinterpret_cast<const uint32_t*>(tOpCode);
	};

	inline uint32_t getOpcodeW()const{
		if(iLength != 4)
			throw Tools::Exception()<<"Opcode is not 32bit size: "<<iLength;

		return *reinterpret_cast<const uint32_t*>(tOpCode);
	};

	inline uint64_t getOpcodeX()const{
		if(iLength != 8)
			throw Tools::Exception()<<"Opcode is not 64bit size: "<<iLength;

		return *reinterpret_cast<const uint32_t*>(tOpCode);
	};

	inline GenericInstruction* getNext()const{
		return pNext;
	}

	inline GenericInstruction* getPrev()const{
		return pPrev;
	}

	inline bool isHead()const{
		return !pPrev;
	}

	inline bool isTail()const{
		return !pNext;
	}
	
protected:
	//TODO larger opcodes and data content as a malloc on demand;

	uint8_t tOpCode[CMaxBytes];
	uint8_t iLength;

	Addresses  adrOriginal;
	Addresses  adrCurrent;

	GenericInstruction* pNext;
	GenericInstruction* pPrev;

	GenericInstruction* pReference;

	friend class GenericInstructionList;
};


class GenericInstructionList {
public:

	inline void append(GenericInstruction* pNew){

		if(!pHead){
			pHead = pNew;
			pTail = pNew;
		}else{
			pTail->pNext = pNew;
			pNew->pPrev = pTail;
			pNew->pNext = nullptr;
			pTail = pNew;
		}
	}

	GenericInstructionList():
		pHead(nullptr){};

	inline GenericInstruction* getHead(){
		return pHead;
	}

	inline const GenericInstruction* getHead()const{
		return pHead;
	}

	inline GenericInstruction* getTail(){
		return pTail;
	}

	inline const GenericInstruction* getTail()const{
		return pTail;
	}

protected:
	GenericInstruction* pHead;
	GenericInstruction* pTail;
};
/*************************************************************************/
}

#endif /* _ASM_GenericInstruction_H_ */
