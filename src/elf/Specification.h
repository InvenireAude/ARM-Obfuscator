/*
 * File: Specification.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Specification_H_
#define _ELF_Specification_H_

#include <inttypes.h>
#include <tools/common.h>

namespace ELF {
    
typedef uint8_t  UChar;

enum FileIdentificatorBytes {

	 EI_NIDENT = 16,

	 EI_MAG0 = 0,
	 EI_MAG1 = 1,
	 EI_MAG2 = 2,
	 EI_MAG3 = 3,
	
	 EI_CLASS = 4,
	 EI_DATA = 5,
	 EI_VERSION = 6,
	 EI_PAD = 7,

};

enum Class {
    ELFCLASSNONE = 0,
    ELFCLASS32 = 1,
    ELFCLASS64 = 2,
};

enum Data {
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2,
};

enum Version {
    EV_NONE = 0,
    EV_CURRENT = 1,
};


namespace Map {
	extern ::Tools::ValueMap Class;
	extern ::Tools::ValueMap Data;
	extern ::Tools::ValueMap Version;
}

}

#include "elf32/Specification.h"

#endif /* _ELF_Specification_H_ */
