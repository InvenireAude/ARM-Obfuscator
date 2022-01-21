/*
 * File: Printer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Elf32_Printer_H_
#define _ELF_Elf32_Printer_H_

#include "../Printer.h"

namespace ELF {
namespace Elf32 {

class Header;
class Section;
class Segment;
class Symbol;
class SymbolTable;

/*************************************************************************/
/** The Printer class.
 *
 */
class Printer : public ELF::Printer {
public:

	virtual ~Printer() throw();
	Printer(std::ostream& os, const  Header* pHeader);

	void printHeader();
	void printSection(const Section* pSection);
	void printSegment(const Segment* pSegment);

	void printSymbol(const Symbol* pSymbol);
	void printSymbolTable(const SymbolTable* pSymbolTable);

	const  Header* pHeader;
	const  Section* pStringsSection;
};

/*************************************************************************/
}
}

#endif /* _ELF_Elf32_Printer_H_ */
