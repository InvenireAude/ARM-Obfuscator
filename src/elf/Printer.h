/*
 * File: Printer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Printer_H_
#define _ELF_Printer_H_

#include <tools/common.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>

namespace ELF {

class Artefact;
class Identification;

/*************************************************************************/
/** The Printer class.
 *
 */
class Printer {
public:

	static void Print(std::ostream& os, Artefact*     pArtefact);
	static void Print(std::ostream& os, Elf32::Header* pHeader);
	static void Print(std::ostream& os, Elf64::Header* pHeader);

	void printIdentification(Identification* pHeader);


protected:
	Printer(std::ostream& os);
	std::ostream& os;
};

/*************************************************************************/
}

#endif /* _ELF_Printer_H_ */
