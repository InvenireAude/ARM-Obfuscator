/*
 * File: Image.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Image.h"

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
Image::Image(const std::string& strName){
	
	struct stat sb;

   std::cerr<<"Opening file: ["<<strName<<"]"<<std::endl;

   fd = open(strName.c_str(), O_RDONLY);
   
   if(fd < 0){
	   throw Tools::Exception()<<"open :"<<strName;
   }

   fstat(fd, &sb);
   std::cerr<<"Size: "<<(uint64_t)sb.st_size<<" bytes."<<std::endl;
   
   iSize = sb.st_size;

   pMemory = reinterpret_cast<const uint8_t*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
   
   if (pMemory == MAP_FAILED){
		throw Tools::Exception()<<"MMap failed: ["<<strName<<"]";
   }

   identify();
}
/*************************************************************************/
Image::~Image() throw(){
}
/*************************************************************************/
void Image::identify(){
	
	ptrIdentification.reset(new Identification(this));
   ptrConverter.reset(Utils::Converter::Create(ptrIdentification->getDataEncoding()));
   
   // if(ptrIdentification->getClass() == ELFCLASS32){
   //    //h.ptrHeader32.reset(
   //       new ::ELF::Template::Header<ElfXYZ::S>(this);
   //      //  );         
   // }

}
/*************************************************************************/
// Template::Header<ElfXYZ::S>* Image::getHeader32()const{
 
//    if(ptrIdentification->getClass() == ELFCLASS32){
//       return h.ptrHeader32.get();
//    }

//    throw Tools::Exception()<<"Requested 32bit header in image class :"<<
//       Map::Class.getString(ptrIdentification->getClass());

// }
/*************************************************************************/
}
