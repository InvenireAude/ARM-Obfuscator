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
		adrCurrent({  iOpCodeAddress, iReferenceAddress }){

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
protected:

	uint8_t tOpCode[CMaxBytes];
	uint8_t iLength;

	Addresses  adrOriginal;
	Addresses  adrCurrent;

	struct List{
		GenericInstruction* pPrev;
		GenericInstruction* pNext;
	};

};

/*************************************************************************/
}

#endif /* _ASM_GenericInstruction_H_ */
