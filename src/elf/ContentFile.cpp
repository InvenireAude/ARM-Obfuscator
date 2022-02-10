/*
 * File: ContentFile.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "ContentFile.h"

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
ContentFile::ContentFile(const std::string& strName){
	
	struct stat sb;

   std::cerr<<"Opening file: ["<<strName<<"]"<<std::endl;

   fd = open(strName.c_str(), O_RDONLY);
   
   if(fd < 0){
	   throw Tools::Exception()<<"open :"<<strName;
   }

   fstat(fd, &sb);
   std::cerr<<"Size: "<<(uint64_t)sb.st_size<<" bytes."<<std::endl;
   
   iSize = sb.st_size;

   pMemory = reinterpret_cast<uint8_t*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
   
   if (pMemory == MAP_FAILED){
		throw Tools::Exception()<<"MMap failed: ["<<strName<<"]";
   }

   std::unique_ptr<Identification>   ptrIdentification(new Identification(this));

   setup(std::move(ptrIdentification));   
}
/*************************************************************************/
ContentFile::~ContentFile() throw(){
}
/*************************************************************************/
 uint8_t* ContentFile::getData(size_t iOffset){
   
   if(iOffset >= iSize){
      throw Tools::Exception()<<"Bad offset: "<<iOffset<<", size is: "<<iSize;
   }

   return pMemory + iOffset;
}
/*************************************************************************/
 uint8_t* ContentFile::getData(size_t iOffset, size_t iDataLen){
   
   if(iOffset >= iSize || iOffset + iDataLen > iSize){
      throw Tools::Exception()<<"Bad offset: "<<iOffset
         <<", or data length: "<<iDataLen<<", size is: "<<iSize;
   }

   return pMemory + iOffset;
}
/*************************************************************************/
}
