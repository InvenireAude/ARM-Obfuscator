/*
 * File: Instruction.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Instruction_H_
#define _ASM_ARM_ARM64_Spec_Instruction_H_

#include <inttypes.h>

#include "enums.h"
#include "Field.h"

#include <list>
#include <vector>
#include <unordered_map>

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The Instruction class.
 *
 */
class Instruction {
public:

	virtual ~Instruction() throw();
	Instruction();

	static const int CMaxFields = 10;

	struct Encoding {
		EncodingId 		    iEncodingId;
		InstructionId       iInstructionId;
		ClassId 	        iClass;
		InstructionId       iAliasInstructionId;
		uint32_t      		opCode;
		uint32_t      		opCodeMask;
		Field::Bits         fields[CMaxFields];
		OperandId           operands[CMaxFields];
		//InstructionFlags    flags; // ?
	};

	const Encoding* match(uint32_t opCode)const;

	const char* getName(EncodingId iEncodingId)const;
	const char* getMnemonic(EncodingId iEncodingId)const;

	inline const char* getName(const Instruction::Encoding* pd)const{
		return getName(pd->iEncodingId);
	}

	inline const char* getMnemonic(const Instruction::Encoding* pd)const{
		return getMnemonic(pd->iEncodingId);
	}

	static const Instruction TheInstance;

protected:

	typedef std::vector < Encoding > DefinitionTable;
	static const DefinitionTable	 TheDefinitions;

	typedef std::unordered_map< EncodingId , const Encoding*> EncodingByIdMap;
	typedef std::unordered_map< EncodingId , const char*>     NameByIdMap;
	typedef std::unordered_map< EncodingId , const char*>     MnemonicByIdMap;
	typedef std::unordered_map< EncodingId , std::list< const Encoding*> >  AliasByIdMap;


	EncodingByIdMap                hmEncodingById;
	AliasByIdMap                   hmAliasById;

	static const NameByIdMap       TheNameById;
	static const MnemonicByIdMap   TheMnemonicById;

};
/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Instruction_H_ */
