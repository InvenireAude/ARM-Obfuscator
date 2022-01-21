/*
 * File: Specification.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Specification.h"

namespace ELF {
namespace Map {
/*************************************************************************/

::Tools::ValueMap Class("Class", {
 { ELFCLASSNONE,	"ELFCLASSNONE" },
 { ELFCLASS32,		"ELFCLASS32" },
 { ELFCLASS64,		"ELFCLASS64" },
});

::Tools::ValueMap Data("Data", {
    { ELFDATANONE, "ELFDATANONE" },  
    { ELFDATA2LSB, "ELFDATA2LSB" },  
    { ELFDATA2MSB, "ELFDATA2MSB" },  
});

::Tools::ValueMap Version("Version", {
    { EV_NONE,     "EV_NONE" },
    { EV_CURRENT, "EV_CURRENT" },
});

/*************************************************************************/
}
}