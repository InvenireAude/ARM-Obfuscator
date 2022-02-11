/*
 * File: Specification.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf64_Specification_H_
#define _ELF_Elf64_Specification_H_

#include <inttypes.h>

#include "../Specification.h"

namespace ELF::Elf64 {


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
    EM_M64 = 1,
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

enum SectionIndice {
   SHN_UNDEF = 0,          
   SHN_LORESERVE = 0xff00, 
   SHN_LOPROC = 0xff00,    
   SHN_HIPROC = 0xff1f,    
   SHN_LOOS = 0xff20,      
   SHN_HIOS = 0xff3f,      
   SHN_ABS = 0xfff1,       
   SHN_COMMON = 0xfff2,    
   SHN_XINDEX = 0xffff,    
   SHN_HIRESERVE = 0xffff  
};


enum SectionFlag : uint32_t {
   // Section data should be writable during execution.
   SHF_WRITE = 0x1,
  
   // Section occupies memory during program execution.
   SHF_ALLOC = 0x2,
  
   // Section contains executable machine instructions.
   SHF_EXECINSTR = 0x4,
  
   // The data in this section may be merged.
   SHF_MERGE = 0x10,
  
   // The data in this section is null-terminated strings.
   SHF_STRINGS = 0x20,
  
   // A field in this section holds a section header table index.
   SHF_INFO_LINK = 0x40U,
  
   // Adds special ordering requirements for link editors.
   SHF_LINK_ORDER = 0x80U,
  
   // This section requires special OS-specific processing to avoid incorrect
   // behavior.
   SHF_OS_NONCONFORMING = 0x100U,
  
   // This section is a member of a section group.
   SHF_GROUP = 0x200U,
  
   // This section holds Thread-Local Storage.
   SHF_TLS = 0x400U,
  
   // Identifies a section containing compressed data.
   SHF_COMPRESSED = 0x800U,
  
   // This section should not be garbage collected by the linker.
   SHF_GNU_RETAIN = 0x200000,
  
   // This section is excluded from the final executable or shared library.
   SHF_EXCLUDE = 0x80000000U,
  
   // Start of target-specific flags.
  
   SHF_MASKOS = 0x0ff00000,
  
   // Bits indicating processor-specific flags.
   SHF_MASKPROC = 0xf0000000,
  
   /// All sections with the "d" flag are grouped together by the linker to form
   /// the data section and the dp register is set to the start of the section by
   /// the boot code.
   XCORE_SHF_DP_SECTION = 0x10000000,
  
   /// All sections with the "c" flag are grouped together by the linker to form
   /// the constant pool and the cp register is set to the start of the constant
   /// pool by the boot code.
   XCORE_SHF_CP_SECTION = 0x20000000,
  
   // If an object file section does not have this flag set, then it may not hold
   // more than 2GB and can be freely referred to in objects using smaller code
   // models. Otherwise, only objects using larger code models can refer to them.
   // For example, a medium code model object can refer to data in a section that
   // sets this flag besides being able to refer to data in a section that does
   // not set it; likewise, a small code model object can refer only to code in a
   // section that does not set this flag.
   SHF_X86_64_LARGE = 0x10000000,
  
   // All sections with the GPREL flag are grouped into a global data area
   // for faster accesses
   SHF_HEX_GPREL = 0x10000000,
  
   // Section contains text/data which may be replicated in other sections.
   // Linker must retain only one copy.
   SHF_MIPS_NODUPES = 0x01000000,
  
   // Linker must generate implicit hidden weak names.
   SHF_MIPS_NAMES = 0x02000000,
  
   // Section data local to process.
   SHF_MIPS_LOCAL = 0x04000000,
  
   // Do not strip this section.
   SHF_MIPS_NOSTRIP = 0x08000000,
  
   // Section must be part of global data area.
   SHF_MIPS_GPREL = 0x10000000,
  
   // This section should be merged.
   SHF_MIPS_MERGE = 0x20000000,
  
   // Address size to be inferred from section entry size.
   SHF_MIPS_ADDR = 0x40000000,
  
   // Section data is string data by default.
   SHF_MIPS_STRING = 0x80000000,
  
   // Make code section unreadable when in execute-only mode
   SHF_ARM_PURECODE = 0x20000000
 };

/*************************************************************************/

}

#endif /* _ELF_Elf64_Specification_H_ */
