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
void ContentMemory::makeSpace(size_t iOffset, size_t iSpaceSize){
  

  std::cout<<"Make new space at: "<<(void*)iOffset<<", sz: "<<iSpaceSize<<std::endl;

  if(iOffset > iSize){
     throw Tools::Exception()<<"Offset to large, given: "<<iOffset<<", sz: "<<iSpaceSize;
  }

  if(iSize + iSpaceSize > iAvailableMemory){

     size_t iNewAvailableMemory = iAvailableMemory * 1.5;
     
     uint8_t* pNew = reinterpret_cast<uint8_t*>(std::aligned_alloc(16, iNewAvailableMemory));
     
     if(!pNew){
         throw Tools::Exception()<<"Cannot allocate memory, size: "<<iSpaceSize;
     }
     
     memcpy(pNew, pMemory, iSize);
     
     std::free(pMemory);
     
     pMemory = pNew;
     iAvailableMemory = iNewAvailableMemory;
  }

   std::cout<<"Copy :"<<(void*)(pMemory + iOffset + iSpaceSize)<<", from: "<<(void*)(pMemory + iOffset)<<
      ", sz: "<<(iSize - iOffset)<<std::endl;

  memcpy(pMemory + iOffset + iSpaceSize, pMemory + iOffset, iSize - iOffset);
  
  iSize += iSpaceSize;
}
/*************************************************************************/
void ContentMemory::copyData(size_t iDstOffset, size_t iSrcOffset, size_t iSize){
   memcpy(pMemory + iDstOffset, pMemory + iSrcOffset, iSize);
}
/*************************************************************************/
}
