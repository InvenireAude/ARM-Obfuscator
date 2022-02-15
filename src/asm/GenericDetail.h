/*
 * File: GenericDetail.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_GenericDetail_H_
#define _ASM_GenericDetail_H_

#include <tools/common.h>
#include <string.h>

namespace ASM {

/*************************************************************************/
/** The GenericDetail class.
 *
 */
class GenericDetail {
public:

	static const int CMaxBytes = 8;

	struct Addresses {
		uint64_t iOpCode;
		uint64_t iReference;
	};

	GenericDetail(const uint8_t *pOpCode, 
				uint8_t  iLength,
				uint64_t iOpCodeAddress,
				uint64_t iReferenceAddress = 0L):
		iLength(iLength),
		adrOriginal({ iOpCodeAddress, iReferenceAddress }),
		adrCurrent({  iOpCodeAddress, iReferenceAddress }),
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

	inline uint32_t& getOpcodeW(){
		if(iLength != 4)
			throw Tools::Exception()<<"Opcode is not 32bit size: "<<iLength;

		return *reinterpret_cast<uint32_t*>(tOpCode);
	};

	inline GenericDetail* getReference()const{
	   return pReference;
	}
	
	inline void setReference(GenericDetail* pReference){
	 this->pReference = pReference;
	}
	
	
protected:
	//TODO larger opcodes and data content as a malloc on demand;

	uint8_t tOpCode[CMaxBytes];
	uint8_t iLength;

	Addresses  adrOriginal;
	Addresses  adrCurrent;

	GenericDetail* pReference;

	friend class GenericDetailList;
};
/*************************************************************************/
}

#endif /* _ASM_GenericDetail_H_ */
