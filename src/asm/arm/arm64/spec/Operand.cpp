/*
 * File: Operand.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Operand.h"
#include "Instruction.h"


namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

// const Operand::DefinitionTable Operand::TheDefinitions = {
//     { Rd , OC_REGISTER, { dRegister : { RC_R , OF_Rd , OF_None } } },
//     { Rn , OC_REGISTER, { dRegister : { RC_R , OF_Rn , OF_None} } },
//     { Rm , OC_REGISTER, { dRegister : { RC_R , OF_Rm , OF_None} } },
//     { Rm_SFT , OC_REGISTER, { dRegister : { RC_R , OF_Rm, OF_Shift } } }
//  };

//  const Operand::FieldBitsTable Operand::TheFieldBits = {
//     { OF_Rd, 0, 5 },
//     { OF_Rn, 5, 5 },
//     { OF_Shift, 22, 2 },
//     { OF_Imm6,  10, 6 }
//  };

//  const Operand::NameByIdMap Operand::TheNameById = {
//     { RC_R, "R"},
//     { RC_X, "X"},
//  };

// const Operand Operand::TheInstance;
// /*************************************************************************/
// Operand::Operand(){

//     for(const auto& d:TheDefinitions){
//         hmDefinitionById[d.id] = &d;
//     }

//     for(const auto& f:TheFieldBits){
//         hmFieldById[f.id] = &f;
//     }

// }
// /*************************************************************************/
// Operand::~Operand() throw(){
// }
// /*************************************************************************/
// const Operand::FieldBits* Operand::getFieldBits(FieldId id, InstructionClass ic)const{
	
//     if(id < OF_Variable){
// 		FieldByIdMap::const_iterator it = hmFieldById.find(id);
// 		if(it == hmFieldById.end()){
// 			throw Tools::Exception()<<"Field not found[1]:"<<id;
// 		}
// 		return it->second;
// 	}

//     switch(id){
//         case OF_Rm:
//             static const FieldBits _fb_OF_Rm_1{ OF_Rm, 0,  5};
//             static const FieldBits _fb_OF_Rm_2{ OF_Rm, 16, 5};        

//             //if(d->instructionClass == Instruction::C_)
//             return & _fb_OF_Rm_2;            
//         break;
//         default:
//         throw Tools::Exception()<<"Field not found[2]:"<<id;
//     }
// };
/*************************************************************************/
}
}
}
}
