/*
 * File: Structures.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Structures_H_
#define _ELF_Elf32_Structures_H_

#include "Specification.h"

namespace ELF {
namespace Elf32 {

struct Header_ {

	UChar 			e_ident[EI_NIDENT];

	Elf32::Half 	e_type;
	Elf32::Half 	e_machine;
	Elf32::Word 	e_version;
	Elf32::Addr 	e_entry;
	Elf32::Off 		e_phoff;
	Elf32::Off 		e_shoff;
	Elf32::Word 	e_flags;
	Elf32::Half 	e_ehsize;
	Elf32::Half 	e_phentsize;
	Elf32::Half 	e_phnum;
	Elf32::Half 	e_shentsize;
	Elf32::Half 	e_shnum;
	Elf32::Half 	e_shstrndx;

};

struct Section_ {
	Elf32::Word sh_name;
	Elf32::Word sh_type;
	Elf32::Word sh_flags;
	Elf32::Addr sh_addr;
	Elf32::Off  sh_offset;
	Elf32::Word sh_size;
	Elf32::Word sh_link;
	Elf32::Word sh_info;
	Elf32::Word sh_addralign;
	Elf32::Word sh_entsize;
};

struct Segment_ {
	Elf32::Word p_type;
	Elf32::Off  p_offset;
	Elf32::Addr p_vaddr;
	Elf32::Addr p_paddr;
	Elf32::Word p_filesz;
	Elf32::Word p_memsz;
	Elf32::Word p_flags;
	Elf32::Word p_align;
};

struct Symbol_ {
	Elf32::Word st_name;
	Elf32::Addr st_value;
	Elf32::Word st_size;
	uint8_t     st_info;
	uint8_t     st_other;
	Elf32::Half st_shndx;
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Structures_H_ */
