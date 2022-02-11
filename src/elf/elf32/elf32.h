

#ifndef _ELF_Elf32_Header_H_
#define _ELF_Elf32_Header_H_

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
namespace Elf32 {

    typedef Template::Header<Elf32::S>      Header;
    typedef Template::Segment<Elf32::S>     Segment;
    typedef Template::Section<Elf32::S>     Section;
    typedef Template::Symbol<Elf32::S>      Symbol;
    typedef Template::SymbolTable<Elf32::S> SymbolTable;
    typedef Template::Dynamic<Elf32::S>     Dynamic;
    typedef Template::DynamicInfo<Elf32::S> DynamicInfo;
    typedef Template::GotInfo<Elf32::S>     GotInfo;
    typedef Template::GotPltInfo<Elf32::S>  GotPltInfo;
    
}
}

#endif