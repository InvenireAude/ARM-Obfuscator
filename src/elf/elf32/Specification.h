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

typedef uint32_t Addr;
typedef uint16_t Half;
typedef uint32_t Off;
typedef int32_t  Sword;
typedef uint32_t Word;

enum Type {
    ET_NONE = 0,
    ET_REL = 1,
    ET_EXEC = 2,
    ET_DYN = 3,
    ET_CORE = 4,
    ET_LOPROC = 0xff00,
    ET_HIPROC = 0xffff,
};

enum Machine {
    EM_NONE = 0,
    EM_M32 = 1,
    EM_SPARC = 2,
    EM_386 = 3,
    EM_68K = 4,
    EM_88K = 5,
    EM_860 = 7,
    EM_MIPS = 8,
    EM_MIPS_RS4_BE = 10,
    EM_RESERVED11 = 11,
    EM_RESERVED12 = 12,
    EM_RESERVED13 = 13,
    EM_RESERVED14 = 14,
    EM_RESERVED15 = 15,
    EM_RESERVED16 = 16,
};

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
