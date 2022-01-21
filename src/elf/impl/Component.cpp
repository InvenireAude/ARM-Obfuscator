/*
 * File: Component.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Component.h"

#include <elf/Image.h>
#include <elf/utils/Converter.h>

namespace ELF {
namespace Impl {

/*************************************************************************/
Component::Component(const ELF::Image *pImage):
	pImage(pImage),
	pConverter(pImage->getConverter()){
}

/*************************************************************************/
Component::~Component() throw(){
}
/*************************************************************************/
}
}
