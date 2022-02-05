/*
 * File: Decoder.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Decoder.h"

#include <asm/GenericInstruction.h>
#include <elf/utils/Helper.h>

#include "spec/EncodingBook.h"
#include "spec/FieldBook.h"

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

		const Encoding *pInstructionDef = EncodingBook::TheInstance.match(opCode);
		
		os<<std::left<<std::setw(24)<<EncodingBook::TheInstance.getName(pInstructionDef);
		os<<std::left<<std::setw(8)<<EncodingBook::TheInstance.getMnemonic(pInstructionDef);

		os<<std::right;
		for(int i=0; i<Encoding::CMaxFields; i++){
			const Field *pFieldBits = pInstructionDef->fields + i;

			if(pFieldBits->iFieldId != F_None){
				os<<(i == 0 ? "\t" : ",\t");			
				
				os<<FieldBook::TheInstance.getName(pFieldBits->iFieldId);
				os<<":";
				os<<pFieldBits->getValue(opCode);
				//TODO generate operands
				if(pFieldBits->iFieldId == F_imm19 ||
				 pFieldBits->iFieldId == F_imm26){
					os<<" @";
					_printHex(os,pGenericInstruction->getCurrentAddresses().iOpCode+4*(long)pFieldBits->getValueSigned(opCode));
					os<<",offset:"<<pFieldBits->getValueSigned(opCode);
				} 		
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
