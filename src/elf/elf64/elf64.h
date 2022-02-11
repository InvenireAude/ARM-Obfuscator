

#ifndef _ELF_Elf64_Header_H_
#define _ELF_Elf64_Header_H_

#include "Structures.h"

#include <elf/template/Header.h>
#include <elf/template/Segment.h>
#include <elf/template/Section.h>
#include <elf/template/Symbol.h>
#include <elf/template/SymbolTable.h>
#include <elf/template/Dynamic.h>
#include <elf/template/DynamicInfo.h>
#include <elf/template/GotInfo.h>

namespace ELF {
namespace Elf64 {

    typedef Template::Header<Elf64::S>      Header;
    typedef Template::Segment<Elf64::S>     Segment;
    typedef Template::Section<Elf64::S>     Section;
    typedef Template::Symbol<Elf64::S>      Symbol;
    typedef Template::SymbolTable<Elf64::S> SymbolTable;
    typedef Template::Dynamic<Elf64::S>     Dynamic;
    typedef Template::DynamicInfo<Elf64::S> DynamicInfo;
    typedef Template::GotInfo<Elf64::S>     GotInfo;
    typedef Template::GotPltInfo<Elf64::S>  GotPltInfo;
    
}
}

#endif