/*
 * File: Structures.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf64_Structures_H_
#define _ELF_Elf64_Structures_H_

#include <inttypes.h>

#include "Specification.h"

namespace ELF {
namespace Elf64 {

struct S {
	
	typedef uint64_t  Addr;
	typedef uint64_t  Off;
	typedef uint16_t  Half;
	typedef uint32_t  Word;
	typedef int32_t   Sword;
	typedef uint64_t  Xword;
	typedef int64_t   Sxword;

struct Header_ {

	uint8_t 			e_ident[EI_NIDENT];

	Half e_type;
	Half e_machine;
	Word e_version;
	Addr e_entry;
	Off  e_phoff;
	Off  e_shoff;
	Word e_flags;
	Half e_ehsize;
	Half e_phentsize;
	Half e_phnum;
	Half e_shentsize;
	Half e_shnum;
	Half e_shstrndx;

};

struct Section_ {
   Word		sh_name;
   Word		sh_type;
   Xword	sh_flags;
   Addr		sh_addr;
   Off		sh_offset;
   Xword	sh_size;
   Word		sh_link;
   Word		sh_info;
   Xword	sh_addralign;
   Xword	sh_entsize;
};

struct Segment_ {
   Word p_type;
   Word p_flags;
   Off p_offset;
   Addr p_vaddr;
   Addr p_paddr;
   Xword p_filesz;
   Xword p_memsz;
   Xword p_align;
};

struct Symbol_ {
   Word st_name;    
   uint8_t st_info;  
   uint8_t st_other; 
   Half st_shndx;    
   Addr st_value;    
   Xword st_size;    
};

struct Dynamic_ {
   typedef Xword TagType;
   typedef Xword ValType;
   typedef Addr  AddrType;

	TagType d_tag;
	union {
		ValType      d_val;
		AddrType       d_ptr;
	} d_un;
};

struct Relocation_{
  typedef Xword  InfoType;
  typedef Sxword AddEndType;
  Addr         r_offset;
  InfoType     r_info;
  AddEndType   r_addend;

  static inline uint32_t ToType(InfoType r_info){
     return (r_info & 0xffffffff);
  }

  static inline Off ToSymbolOffset(InfoType r_info){
     return (r_info >> 32);
  }

};



};
/*************************************************************************/
}
}

#endif /* _ELF_ElfXYZ_Structures_H_ */
