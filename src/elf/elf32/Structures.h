/*
 * File: Structures.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Structures_H_
#define _ELF_Structures_H_

#include <inttypes.h>

#include "Specification.h"

namespace ELF {
namespace Elf32 {

struct S {
	
	typedef uint32_t Addr;
	typedef uint16_t Half;
	typedef uint32_t Off;
	typedef int32_t  Sword;
	typedef uint32_t Word;

struct Header_ {

	uint8_t 			e_ident[EI_NIDENT];

	Half 	e_type;
	Half 	e_machine;
	Word 	e_version;
	Addr 	e_entry;
	Off 	e_phoff;
	Off 	e_shoff;
	Word 	e_flags;
	Half 	e_ehsize;
	Half 	e_phentsize;
	Half 	e_phnum;
	Half 	e_shentsize;
	Half 	e_shnum;
	Half 	e_shstrndx;

};

struct Section_ {
	Word sh_name;
	Word sh_type;
	Word sh_flags;
	Addr sh_addr;
	Off  sh_offset;
	Word sh_size;
	Word sh_link;
	Word sh_info;
	Word sh_addralign;
	Word sh_entsize;
};

struct Segment_ {
	Word p_type;
	Off  p_offset;
	Addr p_vaddr;
	Addr p_paddr;
	Word p_filesz;
	Word p_memsz;
	Word p_flags;
	Word p_align;
};

struct Symbol_ {
	Word st_name;
	Addr st_value;
	Word st_size;
	uint8_t st_info;
	uint8_t st_other;
	Half st_shndx;
};

struct Dynamic_ {
	typedef Word TagType;
	typedef Word ValType;
   	typedef Addr AddrType;
	
	TagType d_tag;
	union {
		ValType      d_val;
		AddrType      d_ptr;
	//	Off       d_off;
	} d_un;
};

struct Relocation_{
  typedef Word  InfoType;
  typedef Sword AddEndType;
  Addr         r_offset;
  InfoType     r_info;
  AddEndType   r_addend;

  static inline uint32_t ToType(InfoType r_info){
     return (r_info & 0xff);
  }

  static inline Off ToSymbolOffset(InfoType r_info){
     return (r_info >> 8);
  }

};


};
/*************************************************************************/
}
}

#endif /* _ELF_ElfXYZ_Structures_H_ */
