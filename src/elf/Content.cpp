/*
 * File: Content.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Content.h"

#include "Identification.h"
#include "utils/Converter.h"

namespace ELF {

/*************************************************************************/
Content::Content(){
}
/*************************************************************************/
Content::~Content() throw(){
}
/*************************************************************************/
void Content::setup(std::unique_ptr<Identification>&&   ptrIdentification){
	
	this->ptrIdentification = std::move(ptrIdentification);
   ptrConverter.reset(Utils::Converter::Create(this->ptrIdentification->getDataEncoding()));
   
}
/*************************************************************************/
}
