

#ifndef _ELF_Elf32_Header_H_
#define _ELF_Elf32_Header_H_

#include "Structures.h"

#include <elf/template/Header.h>
#include <elf/template/Segment.h>
#include <elf/template/Section.h>
#include <elf/template/Symbol.h>
#include <elf/template/SymbolTable.h>

namespace ELF {
namespace Elf32 {

    typedef Template::Header<Elf32::S>  Header;
    typedef Template::Segment<Elf32::S> Segment;
    typedef Template::Section<Elf32::S> Section;
    typedef Template::Symbol<Elf32::S>  Symbol;
    typedef Template::SymbolTable<Elf32::S> SymbolTable;
}
}

#endif