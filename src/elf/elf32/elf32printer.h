

#ifndef _ELF_Elf32Printer_Header_H_
#define _ELF_Elf32Printer_Header_H_

#include "Structures.h"

#include <elf/template/Printer.h>

namespace ELF {
namespace Elf32 {

    typedef Template::Printer<Elf32::S>  Printer;

}
}

#endif