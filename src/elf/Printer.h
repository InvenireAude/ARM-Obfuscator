/*
 * File: Printer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Printer_H_
#define _ELF_Printer_H_

#include <tools/common.h>

namespace ELF {

class Image;

namespace Elf32{
class Header;
}

class Identification;

/*************************************************************************/
/** The Printer class.
 *
 */
class Printer {
public:

	static void Print(std::ostream& os, Image* pImage);
	static void Print(std::ostream& os, Elf32::Header* pHeader);

	void printIdentification(Identification* pHeader);

	Printer(std::ostream& os);

protected:
	std::ostream& os;
};

/*************************************************************************/
}

#endif /* _ELF_Printer_H_ */
