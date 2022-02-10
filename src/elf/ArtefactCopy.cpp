/*
 * File: ArtefactCopy.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "ArtefactCopy.h"

#include "ContentMemory.h"
#include "Identification.h"


namespace ELF {

/*************************************************************************/
ArtefactCopy::ArtefactCopy(const Artefact* pArtefact){
	
   const Content* pContent = pArtefact->getContent();

   ptrContentMemory.reset(new ContentMemory(pContent->getData(0), pContent->getSize()));

   ELF::Class iClass = pArtefact->getIdentification()->getClass();

   switch(iClass){

      case ELFCLASS32:
         ptrHeader32.reset(
            new Elf32::Header(ptrContentMemory.get())
         );         
      break;

   case ELFCLASS64:
         ptrHeader64.reset(
            new Elf64::Header(ptrContentMemory.get())
         );         
      break;

   default:
      throw Tools::Exception()<<"Unknown/unsupported ELF class : "<<iClass;
   }

}
/*************************************************************************/
ArtefactCopy::~ArtefactCopy() throw(){
}
/*************************************************************************/
Content* ArtefactCopy::getContent()const{
   return ptrContentMemory.get();
}
/*************************************************************************/
}
