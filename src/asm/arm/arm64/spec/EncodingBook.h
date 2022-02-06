/*
 * File: Instruction.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Instruction_H_
#define _ASM_ARM_ARM64_Spec_Instruction_H_

#include <tools/common.h>

#include "enums.h"

#include "Encoding.h"

#include <list>
#include <vector>
#include <unordered_map>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

class Field;
class Operand;
/*************************************************************************/
/** The Instruction class.
 *
 */
class EncodingBook {
public:

	virtual ~EncodingBook() throw();
	EncodingBook();

	typedef std::list< std::unique_ptr<Operand> > OperandList;

	const Encoding* match(uint32_t opCode)const;

	const char* getName(EncodingId iEncodingId)const;
	const char* getMnemonic(EncodingId iEncodingId)const;
	const OperandList& getEncodingOperands(EncodingId iEncodingId)const;

	inline const char* getName(const Encoding* pd)const{
		return getName(pd->iEncodingId);
	}

	inline const char* getMnemonic(const Encoding* pd)const{
		return getMnemonic(pd->iEncodingId);
	}

	inline const OperandList& getEncodingOperands(const Encoding* pd)const{
		return getEncodingOperands(pd->iEncodingId);
	}

	static const EncodingBook TheInstance;

protected:

	typedef std::vector < Encoding > DefinitionTable;

	typedef std::unordered_map< EncodingId , const Encoding*> EncodingByIdMap;
	typedef std::unordered_map< EncodingId , const char*>     NameByIdMap;
	typedef std::unordered_map< EncodingId , const char*>     MnemonicByIdMap;
	typedef std::unordered_map< EncodingId , std::list< const Encoding*> >  AliasByIdMap;


	typedef std::unordered_map< EncodingId , OperandList>     OperandListByIdMap;

	OperandListByIdMap hmOperandListByIdMap;


	EncodingByIdMap                hmEncodingById;
	AliasByIdMap                   hmAliasById;

	static const DefinitionTable	 TheDefinitions;
	static const NameByIdMap       TheNameById;
	static const MnemonicByIdMap   TheMnemonicById;

};
/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Instruction_H_ */
