/*
 * File: DecodedInstruction.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DecodedInstruction.h"

#include <asm/GenericDetail.h>
#include <asm/Item.h>

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
DecodedInstruction::DecodedInstruction(GenericDetail* pGenericDetail):
 pGenericDetail(pGenericDetail){

 uint32_t opCode = pGenericDetail->getOpcodeW();
 pEncoding = EncodingBook::TheInstance.match(opCode);
		
}
/*************************************************************************/
DecodedInstruction::DecodedInstruction(GenericDetail* pGenericDetail, Spec::EncodingId iEncodingId):
 pGenericDetail(pGenericDetail){

 pEncoding = EncodingBook::TheInstance.get(iEncodingId);		
}
/*************************************************************************/
 DecodedInstruction::DecodedInstruction(Item& item):
 pGenericDetail(item.getGenericDetail()){
	if(item.hasEncoded()){
		pEncoding = item.getEncoded<Item::ET_ARMv8, Spec::Encoding*>();
	}else{
		uint32_t opCode = pGenericDetail->getOpcodeW();
 		pEncoding = EncodingBook::TheInstance.match(opCode);
		item.setEncoded<Item::ET_ARMv8>(pEncoding);
		std::cout<<"decoded: "<<EncodingBook::TheInstance.getName(pEncoding)<<(void*)&item<<std::endl;
	}
}
/*************************************************************************/
 DecodedInstruction::DecodedInstruction(Item& item, Spec::EncodingId iEncodingId):
 pGenericDetail(item.getGenericDetail()){
	
 	pEncoding = EncodingBook::TheInstance.get(iEncodingId);
	item.setEncoded<Item::ET_ARMv8>(pEncoding);
}
/*************************************************************************/
DecodedInstruction::~DecodedInstruction() throw(){
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
void DecodedInstruction::print(std::ostream& os, const SymbolResolver* pSymbolResover){

	uint64_t iOpCodeAddress = pGenericDetail->getCurrentAddresses().iOpCode;

	_printHex(os, iOpCodeAddress);
	const uint8_t* pOpCode = pGenericDetail->getOpcode();
	os<<" ";
	
	for(int i = 0; i < pGenericDetail->getOpCodeLength(); i++){
		_printHex(os, pOpCode[i]);
		os<<" ";
	}
	
	// std::bitset<32> op(*(uint32_t*)pOpCode);
	// std::cout << op;
	// os<<std::dec;

	os<<" ";
	try{

 		uint32_t opCode = pGenericDetail->getOpcodeW();
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
bool DecodedInstruction::checkMemoryReference()const{

 	uint32_t opCode = pGenericDetail->getOpcodeW();

	//TODO move to another class ??
	ASM::GenericDetail::Addresses& refAddresses(
		pGenericDetail->getCurrentAddresses());

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
void DecodedInstruction::setOperand(Spec::OperandId iOperand, uint32_t iValue)const{

	const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));
 	uint32_t& opCode(pGenericDetail->getOpcodeW());

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
void DecodedInstruction::updateOpcodeReference(size_t iDataSegmentShift)const{

 	uint32_t& opCode(pGenericDetail->getOpcodeW());

	//TODO move to another class ??
	ASM::GenericDetail::Addresses& refAddresses(
		pGenericDetail->getCurrentAddresses());

	const EncodingBook::OperandList& lstOperands(EncodingBook::TheInstance.getEncodingOperands(pEncoding));

	for(const auto& o: lstOperands){
		if(o->isMemoryReference()){
			ASM::GenericDetail *pOther = pGenericDetail->getReference();
			if(pOther != nullptr){
				std::cout<<"updateOpcodeReference: "<<(void*)refAddresses.iOpCode<<" "<<(void*)(long)opCode<<std::endl;
				o->setMemoryReference(opCode, refAddresses.iOpCode,pGenericDetail->getReference()->getCurrentAddresses().iOpCode); 
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
