/*
 * File: Field.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Field_H_
#define _ASM_ARM_ARM64_Spec_Field_H_

#include "enums.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The Field class.
 *
 */
class Field {
public:

		FieldId  iFieldId;
		uint8_t  iHiBit;
		uint8_t  iWidth;

		int32_t getValue(uint32_t opCode)const{
			static const uint32_t CFullMask = ~(uint32_t)0x0;
			uint32_t iMask = ~(CFullMask << iWidth);
			opCode >>= iHiBit + 1 - iWidth;
			return opCode & iMask;
		}
		
		int32_t getSignedValue(uint32_t opCode)const{
			static const uint32_t CFullMask = ~(uint32_t)0x0;
			uint32_t iMask = ~(CFullMask << iWidth);
			opCode >>= iHiBit + 1 - iWidth;
			int32_t iResult = opCode & iMask;
			if(iResult >> (iWidth - 1)){
				iMask = CFullMask << iWidth;
				iResult |= iMask;
			}
			return iResult;
		}


		void setValue(uint32_t& opCode, int32_t iValue)const{
			static const uint32_t CFullMask = ~(uint32_t)0x0;
			uint32_t iMask = ~(CFullMask << iWidth);			
			iMask <<= iHiBit + 1 - iWidth;
			opCode &= ~iMask;
			iValue <<= iHiBit + 1 - iWidth;
			iValue &= iMask;
			opCode |= iValue;
		}

};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Field_H_ */
