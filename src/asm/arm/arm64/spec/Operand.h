/*
 * File: Operand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Operand_H_
#define _ASM_ARM_ARM64_Spec_Operand_H_

#include <inttypes.h>

#include "enums.h"

#include <list>
#include <vector>
#include <unordered_map>

#include <tools/Exception.h>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The Operand class.
 *
 */
class Operand {
public:

// 	virtual ~Operand() throw();
// 	Operand();

	
// 	struct FieldBits {
// 		FieldId id;
// 		uint8_t start;
// 		uint8_t size;
// 	};

// 	struct Register {
// 	 RegisterClass registerClass;
// 	 FieldId       fieldNumber;
// 	 FieldId       fieldShift;
// 	};

// 	struct Definition {
// 		OperandId     id;
// 		OperandClass operandClass;
// 		union {
// 			Register dRegister;
// 		} detail;
// 	};

// 	static const Operand TheInstance;
	
// 	inline const char* getRegisterName(RegisterClass registerClass)const{

// 		NameByIdMap::const_iterator it = TheNameById.find(registerClass);

// 		if(it == TheNameById.end()){
// 			return "?";
// 		}

// 		return it->second;
// 	};

// 	inline const Definition* getOperand(OperandId id)const{

// 		DefinitionByIdMap::const_iterator it = hmDefinitionById.find(id);

// 		if(it == hmDefinitionById.end()){
// 			throw Tools::Exception()<<"Operand not found:"<<id;
// 		}

// 		return it->second;
// 	}


// 	 const FieldBits* getFieldBits(FieldId id, InstructionClass ic)const;

// 	 inline int32_t extractFieldValue(FieldId id, InstructionClass ic, uint32_t opcode)const{
	
// 		const FieldBits* fb = getFieldBits(id, ic);
// 		opcode = opcode >> (fb->start);
// 		uint32_t mask   = 0xffffffff >> (32 - fb->size);
// 		return opcode & mask; // signed / unsigned ??
// 	 };

// protected:

// 	typedef std::vector < Definition > DefinitionTable;
// 	typedef std::vector < FieldBits >  FieldBitsTable;
	
// 	static const DefinitionTable	   TheDefinitions;
// 	static const FieldBitsTable	   	   TheFieldBits;

// 	typedef std::unordered_map< OperandId , const Definition*> DefinitionByIdMap;
// 	typedef std::unordered_map< RegisterClass , const char*>   NameByIdMap;
// 	typedef std::unordered_map< FieldId ,   const FieldBits*>  FieldByIdMap;

// 	DefinitionByIdMap hmDefinitionById;
// 	FieldByIdMap      hmFieldById;

// 	static const NameByIdMap       TheNameById;

};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Operand_H_ */
