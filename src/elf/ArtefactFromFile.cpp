/*
 * File: ArtefactFromFile.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "ArtefactFromFile.h"

#include "ContentFile.h"
#include "Identification.h"

namespace ELF {

/*************************************************************************/
ArtefactFromFile::ArtefactFromFile(const std::string& strName){
	
	ptrContentFile.reset(new ContentFile(strName));

   if(ptrContentFile->getIdentification()->getClass() == ELFCLASS32){
      ptrHeader32.reset(
         new Elf32::Header(ptrContentFile.get())
      );         
   }
}
/*************************************************************************/
ArtefactFromFile::~ArtefactFromFile() throw(){
}
/*************************************************************************/
Content* ArtefactFromFile::getContent()const{
   return ptrContentFile.get();
}
/*************************************************************************/
}
