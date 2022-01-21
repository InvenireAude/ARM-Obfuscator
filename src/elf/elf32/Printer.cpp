/*
 * File: Printer.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Printer.h"

#include "Header.h"
#include "Section.h"
#include "Segment.h"
#include "Symbol.h"
#include "SymbolTable.h"

#include <elf/utils/Helper.h>
#include <elf/Image.h>

#include <iomanip>

namespace ELF {
namespace Elf32 {
using namespace Utils;

/*************************************************************************/
Printer::Printer(std::ostream& os, const Header* pHeader):
	ELF::Printer(os),
	pHeader(pHeader){
	
	pStringsSection = pHeader->getStringsSection();
}
/*************************************************************************/
Printer::~Printer() throw(){
	
}
/*************************************************************************/
void Printer::printHeader(){

	os<<"Header "<<std::endl;

	printIdentification(pHeader	->getImage()->getIdentification());

	os<<"\t type:     \t"<<pHeader->get_type()<<std::endl;
	os<<"\t machine:  \t"<<pHeader->get_machine()<<std::endl;
	os<<"\t version:  \t"<<pHeader->get_version()<<std::endl;
	os<<"\t entry:    \t0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pHeader->get_entry()<<std::dec<<std::endl;
	os<<"\t phoff:    \t0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pHeader->get_phoff()<<std::dec<<std::endl;
	os<<"\t shoff:    \t0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pHeader->get_shoff()<<std::dec<<std::endl;
	os<<"\t flags:    \t0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pHeader->get_flags()<<std::dec<<std::endl;
	os<<"\t ehsize:   \t"<<pHeader->get_ehsize()<<std::endl;
	os<<"\t phentsize:\t"<<pHeader->get_phentsize()<<std::endl;
	os<<"\t phnum:    \t"<<pHeader->get_phnum()<<std::endl;
	os<<"\t shentsize:\t"<<pHeader->get_shentsize()<<std::endl;
	os<<"\t shnum:    \t"<<pHeader->get_shnum()<<std::endl;
	os<<"\t shstrndx: \t"<<pHeader->get_shstrndx()<<std::endl;

	os<<Helper::BinarytoHex(pHeader->getRaw(), sizeof(Header_))<<std::endl;

	const Header::SectionList& lstSections(pHeader->getSections());

	int iIdx = 0;
	for(const auto& s: lstSections){
		os<<std::setw(3)<<iIdx++;
		printSection(s.get());
	}

	const Header::SegmentList& lstSegments(pHeader->getSegments());

	for(const auto& s: lstSegments){
		printSegment(s.get());
	}

	if(!pHeader->hasSymbolTable()){
		os<<"No symbol table found";
	}else{
		printSymbolTable(pHeader->getSymbolTable());
	}
}
/*************************************************************************/
void Printer::printSection(const Section* pSection){

	//os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_name()<<std::dec;

	os<<std::setfill(' ')<<std::setw(32)<<pSection->getName();

	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_type()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_flags()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_addr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_offset()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_size()<<std::dec;

	os<<" "<<std::setw(8)<<pSection->get_link();
	os<<" "<<std::setw(8)<<pSection->get_info();
	os<<" "<<std::setw(8)<<pSection->get_addralign();
	os<<" "<<std::setw(8)<<pSection->get_entsize();

	os<<std::endl;
}
/*************************************************************************/
void Printer::printSegment(const Segment* pSegment){

	os<<" "<<std::setw(8)<<pSegment->get_type();

	os<<" "<<std::setw(8)<<pSegment->get_type();

	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_offset()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_vaddr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_paddr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_filesz()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_memsz()<<std::dec;
	os<<" "<<std::setw(8)<<pSegment->get_flags();
	os<<" "<<std::setw(8)<<pSegment->get_align();

	os<<std::endl;
}
/*************************************************************************/
void Printer::printSymbol(const Symbol* pSymbol){

	os<<std::setfill(' ')<<std::setw(32)<<pSymbol->getName();
	os<<" 0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pSymbol->get_value()<<std::dec;
	os<<" 0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pSymbol->get_size()<<std::dec;
	os<<" "<<(int)pSymbol->get_info();
	os<<" "<<(int)pSymbol->get_other();
	os<<" "<<std::setw(3)<<pSymbol->get_shndx();

	os<<std::endl;
}
/*************************************************************************/
void Printer::printSymbolTable(const SymbolTable* pSymbolTable){

	const SymbolTable::SymbolList& lstSymbols(pSymbolTable->getSymbols());

	for(const auto& s : lstSymbols){
		printSymbol(s.get());
	}

	// const Symbol* pMain = pSymbolTable->lookup("main");
	// printSymbol(pMain);
	// os<<Utils::Helper::BinarytoHex(pMain->getData<uint8_t>(), pMain->get_size());
	// os<<std::endl;
}
/*************************************************************************/
}
}
