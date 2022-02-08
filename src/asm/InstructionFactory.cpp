/*
 * File: InstructionFactory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "InstructionFactory.h"
#include "GenericInstruction.h"

namespace ASM {

/*************************************************************************/
InstructionFactory::InstructionFactory(size_t iSize):
	iSize(iSize),
	iFirstFree(0),
	pPool(nullptr){

	pPool = reinterpret_cast<GenericInstruction*>(aligned_alloc(sizeof(GenericInstruction), iSize*sizeof(GenericInstruction)));

}
/*************************************************************************/
InstructionFactory::~InstructionFactory() throw(){
	if(pPool){
		free(pPool);
	}
}
/*************************************************************************/
GenericInstruction* InstructionFactory::allocate(){

	if(iFirstFree == iSize){
		throw Tools::Exception()<<"Out of memory in InstructionFactory";
	}

	return pPool + iFirstFree++;
}
/*************************************************************************/
}
