/*
 * File: Component.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Component.h"

#include <elf/Content.h>
#include <elf/utils/Converter.h>

namespace ELF {
namespace Impl {

/*************************************************************************/
Component::Component(ELF::Content *pContent):
	pContent(pContent),
	pConverter(pContent->getConverter()){
}

/*************************************************************************/
Component::~Component() throw(){
}
/*************************************************************************/
}
}
