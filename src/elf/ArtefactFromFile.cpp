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
   Class iClass = ptrContentFile->getIdentification()->getClass();

   switch(iClass){

      case ELFCLASS32:
         ptrHeader32.reset(
            new Elf32::Header(ptrContentFile.get())
         );         
      break;

   case ELFCLASS64:
         ptrHeader64.reset(
            new Elf64::Header(ptrContentFile.get())
         );         
      break;

   default:
      throw Tools::Exception()<<"Unknown/unsupported ELF class : "<<iClass;
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
