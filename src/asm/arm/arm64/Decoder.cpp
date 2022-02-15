/*
 * File: Decoder.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Decoder.h"

#include <asm/GenericInstruction.h>
#include <elf/utils/Helper.h>

#include "spec/Encoding.h"
#include "spec/EncodingBook.h"
#include "spec/FieldBook.h"
#include "spec/Operand.h"
#include "spec/OperandBook.h"

#include <iomanip>
#include <bitset>

namespace ASM {
namespace ARM {
namespace ARM64 {

using namespace Spec;

/*************************************************************************/
Decoder::Decoder(const GenericInstruction* pGenericInstruction):
 pGenericInstruction(pGenericInstruction){

 uint32_t opCode = pGenericInstruction->getOpcodeW();
 pEncoding = EncodingBook::TheInstance.match(opCode);
		
}
/*************************************************************************/
Decoder::Decoder(const GenericInstruction* pGenericInstruction, Spec::EncodingId iEncodingId):
 pGenericInstruction(pGenericInstruction){

 pEncoding = EncodingBook::TheInstance.get(iEncodingId);		
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
void Decoder::print(std::ostream& os, const SymbolResolver* pSymbolResover){

	uint64_t iOpCodeAddress = pGenericInstruction->getCurrentAddresses().iOpCode;

	_printHex(os, iOpCodeAddress);
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

 		uint32_t opCode = pGenericInstruction->getOpcodeW();
		_printHex(os, opCode);
		os<<"\t";

		os<<std::left<<std::setw(24)<<EncodingBook::TheInstance.getName(pEncoding);
		os<<std::left<<std::setw(8)<<EncodingBook::TheInstance.getMnemonic(pEncoding);

		os<<std::right;
		
		const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));

		bool bFirst = true;
		for(const auto& o: lstOperands){
	 		os<<( bFirst ? "\t" : ", ");
			bFirst = false;

			o->disassemble(opCode, os);
			if(o->isMemoryReference()){
				os<<" @";
				uint64_t iAddress = o->applyMemoryReference(iOpCodeAddress, opCode);
				_printHex(os, iAddress);
				if(pSymbolResover){
					pSymbolResover->print(os, iAddress );
				}
			}
		}

		
	}catch(Tools::Exception& e){
		std::cerr<<e<<std::endl;
		os<< "??? ?? ??";
	}
}
/*************************************************************************/
bool Decoder::checkMemoryReference()const{

 	uint32_t opCode = pGenericInstruction->getOpcodeW();

	//TODO move to another class ??
	ASM::GenericInstruction::Addresses& refAddresses(
		const_cast<ASM::GenericInstruction*>(pGenericInstruction)->getCurrentAddresses());

	const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));

	for(const auto& o: lstOperands){
		if(o->isMemoryReference()){
			refAddresses.iReference = o->applyMemoryReference(refAddresses.iOpCode, opCode);
			return true;
		}else{
			refAddresses.iReference = 0L;
		}
	}

	return false;
}

//
// TODO !!!!!!!!!!!!!!!!!!11
// redesign class - create a new one for modifications and get rid of these const_casts.

/*************************************************************************/
void Decoder::setOperand(Spec::OperandId iOperand, uint32_t iValue)const{

	const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));
 	uint32_t& opCode(const_cast<ASM::GenericInstruction*>(pGenericInstruction)->getOpcodeW());

	for(const auto&o : lstOperands){
		if(o->getOperandId())
			std::cout<<OperandBook::TheInstance.getSpec(o->getOperandId())<<std::endl;

		std::cout<<(int)o->getOperandId()<<std::endl;
		if(o->getOperandId() == iOperand){
			o->setValue(opCode, iValue);
		}
	}

	std::cout<<"updated [1]: "<<(void*)(long)opCode<<" "<<lstOperands.size()<<std::endl;
}
/*************************************************************************/
void Decoder::updateOpcodeReference(size_t iDataSegmentShift)const{

 	uint32_t& opCode(const_cast<ASM::GenericInstruction*>(pGenericInstruction)->getOpcodeW());

	//TODO move to another class ??
	ASM::GenericInstruction::Addresses& refAddresses(
		const_cast<ASM::GenericInstruction*>(pGenericInstruction)->getCurrentAddresses());

	const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));

	for(const auto& o: lstOperands){
		if(o->isMemoryReference()){
			ASM::GenericInstruction *pOther = pGenericInstruction->getReference();
			if(pOther != nullptr){
				std::cout<<"updateOpcodeReference: "<<(void*)refAddresses.iOpCode<<(void*)(long)opCode<<std::endl;
				o->setMemoryReference(opCode, refAddresses.iOpCode,pGenericInstruction->getReference()->getCurrentAddresses().iOpCode); 
				std::cout<<"updated: "<<(void*)(long)opCode<<std::endl;
			}else{
				//if(pEncoding->iClass == Spec::C_pcreladdr){
				
				if(refAddresses.iReference){

					std::cout<<"iReference:"<<(void*)(long)refAddresses.iOpCode<<"\t"<<(void*)(long)refAddresses.iReference<<std::endl;
					o->setMemoryReference(opCode, refAddresses.iOpCode, refAddresses.iReference + iDataSegmentShift); 

				}
			}
		}else{
			//throw Tools::Exception()<<"Instruction has no memory reference.";
		}
	}

}	
/*************************************************************************/
}
}
}


// for(int i=0; i<Encoding::CMaxFields; i++){
// 			const Field *pFieldBits = pInstructionDef->fields + i;

// 			if(pFieldBits->iFieldId != F_None){
// 				os<<(i == 0 ? "\t" : ",\t");			
				
// 				os<<FieldBook::TheInstance.getName(pFieldBits->iFieldId);
// 				os<<":";
// 				os<<pFieldBits->getValue(opCode);
// 				//TODO generate operands
// 				if(pFieldBits->iFieldId == F_imm19 ||
// 				 pFieldBits->iFieldId == F_imm26){
// 					os<<" @";
// 					_printHex(os,pGenericInstruction->getCurrentAddresses().iOpCode+4*(long)pFieldBits->getSignedValue(opCode));
// 					os<<",offset:"<<pFieldBits->getSignedValue(opCode);
// 				} 		
// 				//_printHex(os, pFieldBits->getValue(opCode)); //TODO is signed/hex ?
// 			}
// 		}