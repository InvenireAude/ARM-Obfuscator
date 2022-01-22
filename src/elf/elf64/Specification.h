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

enum SegmentType {
   PT_NULL = 0,            // Unused segment.
   PT_LOAD = 1,            // Loadable segment.
   PT_DYNAMIC = 2,         // Dynamic linking information.
   PT_INTERP = 3,          // Interpreter pathname.
   PT_NOTE = 4,            // Auxiliary information.
   PT_SHLIB = 5,           // Reserved.
   PT_PHDR = 6,            // The program header table itself.
   PT_TLS = 7,             // The thread-local storage template.
   PT_LOOS = 0x60000000,   // Lowest operating system-specific pt entry type.
   PT_HIOS = 0x6fffffff,   // Highest operating system-specific pt entry type.
   PT_LOPROC = 0x70000000, // Lowest processor-specific program hdr entry type.
   PT_HIPROC = 0x7fffffff, // Highest processor-specific program hdr entry type.
  
   // x86-64 program header types.
   // These all contain stack unwind tables.
   PT_GNU_EH_FRAME = 0x6474e550,
   PT_SUNW_EH_FRAME = 0x6474e550,
   PT_SUNW_UNWIND = 0x6464e550,
  
   PT_GNU_STACK = 0x6474e551,    // Indicates stack executability.
   PT_GNU_RELRO = 0x6474e552,    // Read-only after relocation.
   PT_GNU_PROPERTY = 0x6474e553, // .note.gnu.property notes sections.
  
   PT_OPENBSD_RANDOMIZE = 0x65a3dbe6, // Fill with random data.
   PT_OPENBSD_WXNEEDED = 0x65a3dbe7,  // Program does W^X violations.
   PT_OPENBSD_BOOTDATA = 0x65a41be6,  // Section for boot arguments.
  
   // ARM program header types.
   PT_ARM_ARCHEXT = 0x70000000, // Platform architecture compatibility info
   // These all contain stack unwind tables.
   PT_ARM_EXIDX = 0x70000001,
   PT_ARM_UNWIND = 0x70000001,
  
   // MIPS program header types.
   PT_MIPS_REGINFO = 0x70000000,  // Register usage information.
   PT_MIPS_RTPROC = 0x70000001,   // Runtime procedure table.
   PT_MIPS_OPTIONS = 0x70000002,  // Options segment.
   PT_MIPS_ABIFLAGS = 0x70000003, // Abiflags segment.
};

enum SectionType {
   SHT_PROGBITS = 1,       // Program-defined contents.
   SHT_SYMTAB = 2,         // Symbol table.
   SHT_STRTAB = 3,         // String table.
   SHT_RELA = 4,           // Relocation entries; explicit addends.
   SHT_HASH = 5,           // Symbol hash table.
   SHT_DYNAMIC = 6,        // Information for dynamic linking.
   SHT_NOTE = 7,           // Information about the file.
   SHT_NOBITS = 8,         // Data occupies no space in the file.
   SHT_REL = 9,            // Relocation entries; no explicit addends.
   SHT_SHLIB = 10,         // Reserved.
   SHT_DYNSYM = 11,        // Symbol table.
   SHT_INIT_ARRAY = 14,    // Pointers to initialization functions.
   SHT_FINI_ARRAY = 15,    // Pointers to termination functions.
   SHT_PREINIT_ARRAY = 16, // Pointers to pre-init functions.
   SHT_GROUP = 17,         // Section group.
   SHT_SYMTAB_SHNDX = 18,  // Indices for SHN_XINDEX entries.
   // Experimental support for SHT_RELR sections. For details, see proposal
   // at https://groups.google.com/forum/#!topic/generic-abi/bX460iggiKg
   SHT_RELR = 19,         // Relocation entries; only offsets.
   SHT_LOOS = 0x60000000, // Lowest operating system-specific type.
   // Android packed relocation section types.
   // https://android.googlesource.com/platform/bionic/+/6f12bfece5dcc01325e0abba56a46b1bcf991c69/tools/relocation_packer/src/elf_file.cc#37
   SHT_ANDROID_REL = 0x60000001,
   SHT_ANDROID_RELA = 0x60000002,
   SHT_LLVM_ODRTAB = 0x6fff4c00,         // LLVM ODR table.
   SHT_LLVM_LINKER_OPTIONS = 0x6fff4c01, // LLVM Linker Options.
   SHT_LLVM_ADDRSIG = 0x6fff4c03,        // List of address-significant symbols
                                         // for safe ICF.
   SHT_LLVM_DEPENDENT_LIBRARIES =
       0x6fff4c04,                    // LLVM Dependent Library Specifiers.
   SHT_LLVM_SYMPART = 0x6fff4c05,     // Symbol partition specification.
   SHT_LLVM_PART_EHDR = 0x6fff4c06,   // ELF header for loadable partition.
   SHT_LLVM_PART_PHDR = 0x6fff4c07,   // Phdrs for loadable partition.
   SHT_LLVM_BB_ADDR_MAP = 0x6fff4c08, // LLVM Basic Block Address Map.
   SHT_LLVM_CALL_GRAPH_PROFILE = 0x6fff4c09, // LLVM Call Graph Profile.
   // Android's experimental support for SHT_RELR sections.
   // https://android.googlesource.com/platform/bionic/+/b7feec74547f84559a1467aca02708ff61346d2a/libc/include/elf.h#512
   SHT_ANDROID_RELR = 0x6fffff00,   // Relocation entries; only offsets.
   SHT_GNU_ATTRIBUTES = 0x6ffffff5, // Object attributes.
   SHT_GNU_HASH = 0x6ffffff6,       // GNU-style hash table.
   SHT_GNU_verdef = 0x6ffffffd,     // GNU version definitions.
   SHT_GNU_verneed = 0x6ffffffe,    // GNU version references.
   SHT_GNU_versym = 0x6fffffff,     // GNU symbol versions table.
   SHT_HIOS = 0x6fffffff,           // Highest operating system-specific type.
   SHT_LOPROC = 0x70000000,         // Lowest processor arch-specific type.
   // Fixme: All this is duplicated in MCSectionELF. Why??
   // Exception Index table
   SHT_ARM_EXIDX = 0x70000001U,
   // BPABI DLL dynamic linking pre-emption map
   SHT_ARM_PREEMPTMAP = 0x70000002U,
   //  Object file compatibility attributes
   SHT_ARM_ATTRIBUTES = 0x70000003U,
   SHT_ARM_DEBUGOVERLAY = 0x70000004U,
   SHT_ARM_OVERLAYSECTION = 0x70000005U,
   SHT_HEX_ORDERED = 0x70000000,   // Link editor is to sort the entries in
                                   // this section based on their sizes
   SHT_X86_64_UNWIND = 0x70000001, // Unwind information
  
   SHT_MIPS_REGINFO = 0x70000006,  // Register usage information
   SHT_MIPS_OPTIONS = 0x7000000d,  // General options
   SHT_MIPS_DWARF = 0x7000001e,    // DWARF debugging section.
   SHT_MIPS_ABIFLAGS = 0x7000002a, // ABI information.
  
   SHT_MSP430_ATTRIBUTES = 0x70000003U,
  
   SHT_RISCV_ATTRIBUTES = 0x70000003U,
  
   SHT_HIPROC = 0x7fffffff, // Highest processor arch-specific type.
   SHT_LOUSER = 0x80000000, // Lowest type reserved for applications.
   SHT_HIUSER = 0xffffffff  // Highest type reserved for applications.

};

enum SymbolBind {
   STB_LOCAL = 0,
   STB_GLOBAL = 1,
   STB_WEAK = 2,
   STB_GNU_UNIQUE = 10,
   STB_LOOS = 10,
   STB_HIOS = 12,
   STB_LOPROC = 13,
   STB_HIPROC = 15  
};

enum SymbolType {
   STT_NOTYPE = 0,
   STT_OBJECT = 1,
   STT_FUNC = 2,
   STT_SECTION = 3,
   STT_FILE = 4,
   STT_COMMON = 5,
   STT_TLS = 6,
   STT_GNU_IFUNC = 10,
   STT_LOOS = 10,
   STT_HIOS = 12,
   STT_LOPROC = 13,
   STT_HIPROC = 15
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
