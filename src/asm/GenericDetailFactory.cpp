/*
 * File: GenericDetailFactory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "GenericDetailFactory.h"
#include "GenericDetail.h"
#include "Item.h"

namespace ASM {

/*************************************************************************/
GenericDetailFactory::GenericDetailFactory(size_t iSize):
	iSize(iSize),
	iFirstFree(0),
	iItemFirstFree(0){

// TODO use LRU pool allocator template for this.

	ptrPool.reset(reinterpret_cast<GenericDetail*>(aligned_alloc(sizeof(GenericDetail), iSize*sizeof(GenericDetail))));
	ptrItemPool.reset(reinterpret_cast<Item*>(aligned_alloc(sizeof(Item), iSize*sizeof(Item))));

	if(!ptrItemPool || !ptrPool){
		throw Tools::Exception()<<"Cannot allocate memory for pools";
	}
}
/*************************************************************************/
GenericDetailFactory::~GenericDetailFactory() throw(){

}
/*************************************************************************/
GenericDetail* GenericDetailFactory::allocateGenericDetail(){

	if(iFirstFree == iSize){
		throw Tools::Exception()<<"Out of memory in GenericDetailFactory";
	}

	return ptrPool.get() + iFirstFree++;
}
/*************************************************************************/
Item* GenericDetailFactory::allocateItem(){

	if(iItemFirstFree == iSize){
		throw Tools::Exception()<<"Out of memory in GenericDetailFactory";
	}

	return ptrItemPool.get() + iItemFirstFree++;
}
/*************************************************************************/
}
