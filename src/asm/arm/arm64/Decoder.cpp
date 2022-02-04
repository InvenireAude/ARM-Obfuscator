/*
 * File: Decoder.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Decoder.h"

#include <asm/GenericInstruction.h>
#include <elf/utils/Helper.h>

#include "spec/Instruction.h"

#include <iomanip>
#include <bitset>

namespace ASM {
namespace ARM {
namespace ARM64 {

using namespace Spec;

/*************************************************************************/
Decoder::Decoder(const GenericInstruction* pGenericInstruction):
 pGenericInstruction(pGenericInstruction){
}
/*************************************************************************/
Decoder::~Decoder() throw(){
}
/*************************************************************************/
static inline void _printHex(std::ostream& os, uint8_t v){
	os<<std::hex<<std::setw(2)<<std::setfill('0')<<(int)v;
	os<<std::dec<<std::setfill(' ');
}
/*************************************************************************/
static inline void _printHex(std::ostream& os, uint32_t v){
	os<<std::hex<<std::setw(8)<<std::setfill('0')<<v;
	os<<std::dec<<std::setfill(' ');
}
/*************************************************************************/
static inline void _printHex(std::ostream& os, uint64_t v){
	os<<std::hex<<std::setw(16)<<std::setfill('0')<<v;
	os<<std::dec<<std::setfill(' ');
}
/*************************************************************************/
static inline void _printHex(std::ostream& os, long v){
	os<<std::hex<<v;
	os<<std::dec;
}
/*************************************************************************/
void Decoder::print(std::ostream& os){

	_printHex(os, pGenericInstruction->getCurrentAddresses().iOpCode);
	const uint8_t* pOpCode = pGenericInstruction->getOpcode();
	os<<" ";
	
	for(int i = 0; i < pGenericInstruction->getOpCodeLength(); i++){
		_printHex(os, pOpCode[i]);
		os<<" ";
	}
	
	// std::bitset<32> op(*(uint32_t*)pOpCode);
	// std::cout << op;
	// os<<std::dec;

	os<<" ";
	try{
		const uint8_t* tOpCode = pGenericInstruction->getOpcode();
		uint32_t opCode = *(uint32_t*)tOpCode;

		_printHex(os,opCode);
		os<<"\t";

		const Instruction::Encoding *pInstructionDef = Instruction::TheInstance.match(opCode);
		
		os<<std::left<<std::setw(24)<<Instruction::TheInstance.getName(pInstructionDef);
		os<<std::left<<std::setw(8)<<Instruction::TheInstance.getMnemonic(pInstructionDef);

		os<<std::right;
		for(int i=0; i<Instruction::CMaxFields; i++){
			const Field::Bits *pFieldBits = pInstructionDef->fields + i;

			if(pFieldBits->iField != F_None){
				os<<(i == 0 ? "\t" : ",\t");			
				
				os<<Field::TheInstance.getName(pFieldBits->iField);
				os<<":";
				os<<pFieldBits->getValue(opCode);
				//_printHex(os, pFieldBits->getValue(opCode)); //TODO is signed/hex ?
			}
		}



	}catch(Tools::Exception& e){
		std::cerr<<e<<std::endl;
		os<< "??? ?? ??";
	}
}
/*************************************************************************/
}
}
}
