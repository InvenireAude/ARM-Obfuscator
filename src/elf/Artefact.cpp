/*
 * File: Artefact.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Artefact.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ArtefactFromFile.h"
#include "Content.h"

namespace ELF {

/*************************************************************************/
Artefact::Artefact(){
}
/*************************************************************************/
Artefact::~Artefact() throw(){
}	
/*************************************************************************/
Identification* Artefact::getIdentification()const{
   return getContent()->getIdentification();
}
/*************************************************************************/
void Artefact::save(const std::string& strFileName)const{

   const Content* pContent = getContent();

   const uint8_t* pData = pContent->getData();
   size_t iBytesToWrite = pContent->getSize();

   int fd = open(strFileName.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0750);
   
   if(fd == -1){
      throw Tools::Exception()<<"Cannot open file for writing: "<<strFileName<<", reason: "<<
         strerror(errno);
   }

   while(iBytesToWrite > 0){

      int rc = write(fd, pData, iBytesToWrite);

      if(rc == -1){
         throw Tools::Exception()<<"Cannot write to file: "<<strFileName<<", reason: "<<
            strerror(errno);
      }

      iBytesToWrite -= rc;
      pData         += rc;
   }
   
   close(fd);
}
/*************************************************************************/
}
