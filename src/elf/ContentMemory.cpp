/*
 * File: ContentMemory.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "ContentMemory.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Identification.h"
#include "utils/Converter.h"

#include <elf/template/Header.h>
#include <elf/template/Segment.h>
#include <elf/template/Section.h>
#include <elf/template/Symbol.h>
#include <elf/template/SymbolTable.h>


namespace ELF {

/*************************************************************************/
ContentMemory::ContentMemory(const uint8_t* pSource, size_t iSize):
   pMemory((uint8_t*)std::aligned_alloc(16, 2*iSize)),
   iSize(iSize),
   iAvailableMemory(2*iSize){
	
   if(!pMemory){
      throw Tools::Exception()<<"Cannot allocate memory, size: "<<iSize;
   }

   std::cout<<"Making a memory copy, size: "<<iSize<<" bytes."<<std::endl;

   memcpy(pMemory, pSource, iSize);

   std::unique_ptr<Identification>   ptrIdentification(new Identification(this));

   setup(std::move(ptrIdentification));   
}
/*************************************************************************/
ContentMemory::~ContentMemory() throw(){
}
/*************************************************************************/
 uint8_t* ContentMemory::getData(size_t iOffset){
   
   if(iOffset >= iSize){
      throw Tools::Exception()<<"Bad offset: "<<iOffset<<", size is: "<<iSize;
   }

   return pMemory + iOffset;
}
/*************************************************************************/
 uint8_t* ContentMemory::getData(size_t iOffset, size_t iDataLen){
   
   if(iOffset >= iSize || iOffset + iDataLen > iSize){
      throw Tools::Exception()<<"Bad offset: "<<iOffset
         <<", or data length: "<<iDataLen<<", size is: "<<iSize;
   }

   return pMemory + iOffset;
}
/*************************************************************************/
size_t ContentMemory::getSize()const{
   return iSize;
}
/*************************************************************************/
}
