/*
 * File: Specification.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Specification_H_
#define _ELF_Elf32_Specification_H_

#include <inttypes.h>

#include "../Specification.h"

namespace ELF::Elf32 {


enum SectionIndex {
    SHN_UNDEF     = 0,
    SHN_LORESERVE = 0xff00,
    SHN_LOPROC    = 0xff00,
    SHN_HIPROC    = 0xff1f,
    SHN_ABS       = 0xfff1,
    SHN_COMMON    = 0xfff2,
    SHN_HIRESERVE = 0xffff,
};

enum SymbolBind {
    STB_LOCAL = 0,
    STB_GLOBAL = 1,
    STB_WEAK = 2,
    STB_LOPROC = 13,
    STB_HIPROC = 15,
};

enum SymbolType {
    STT_NOTYPE = 0,
    STT_OBJECT = 1,
    STT_FUNC = 2,
    STT_SECTION = 3,
    STT_FILE = 4,
    STT_LOPROC = 13,
    STT_HIPROC = 15,
};

/*************************************************************************/

}

#endif /* _ELF_Elf32_Specification_H_ */
