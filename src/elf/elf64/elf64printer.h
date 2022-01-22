

#ifndef _ELF_Elf64Printer_Header_H_
#define _ELF_Elf64Printer_Header_H_

#include "Structures.h"

#include <elf/template/Printer.h>

namespace ELF {
namespace Elf64 {

    typedef Template::Printer<Elf64::S>  Printer;

}
}

#endif