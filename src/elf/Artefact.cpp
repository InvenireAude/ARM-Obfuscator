/*
 * File: Artefact.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Artefact.h"

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
}
