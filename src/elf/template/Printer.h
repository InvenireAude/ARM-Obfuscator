/*
 * File: Printer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Printer_H_
#define _ELF_Template_Printer_H_


#include <elf/Printer.h>

#include <elf/utils/Helper.h>
#include <iomanip>

namespace ELF {
namespace Template {

template<class S>
class Header;

template<class S>
class Section;

template<class S>
class Segment;

template<class S>
class Symbol;

template<class S>
class SymbolTable;

template<class S>
class Dynamic;

template<class S>
class DynamicInfo;


/*************************************************************************/
/** The Printer class.
 *
 */
template<class S>
class Printer : public ELF::Printer {
public:

/*************************************************************************/
Printer(std::ostream& os, const Header<S>* pHeader):
	ELF::Printer(os),
	pHeader(pHeader){
	
	pStringsSection = pHeader->getStringsSection();
}
/*************************************************************************/
~Printer() throw(){
	
}
/************************************************************************/
void printHeader(){

	os<<"Header "<<std::endl;

	printIdentification(pHeader	->getContent()->getIdentification());

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

	os<<Utils::Helper::BinarytoHex(pHeader->getRaw(), sizeof(typename S::Header_))<<std::endl;

	const typename Header<S>::SectionList& lstSections(pHeader->getSections());

	os<<"Sections:"<<std::endl;

	int iIdx = 0;
	for(const auto& s: lstSections){
		os<<std::setw(3)<<iIdx++;
		printSection(s.get());
	}

	const typename Header<S>::SegmentList& lstSegments(pHeader->getSegments());

	os<<"Segments:"<<std::endl;

	for(const auto& s: lstSegments){
		printSegment(s.get());
	}

	os<<"Symbols:"<<std::endl;

	if(!pHeader->hasSymbolTable()){
		os<<"No symbol table found";
	}else{
		printSymbolTable(pHeader->getSymbolTable());
	}

	os<<"Dynamic symbols:"<<std::endl;


	if(!pHeader->hasDynSymbolTable()){
		os<<"No symbol table found";
	}else{
		printSymbolTable(pHeader->getDynSymbolTable());
	}

	if(!pHeader->hasDynamicInfo()){
		os<<"No dynamic section found";
	}else{
		printDynamicInfo(pHeader->getDynamicInfo());
	}

	if(!pHeader->hasGotInfo()){
		os<<"No got section found";
	}else{
		printGot(pHeader->getGotInfo());
	}

	if(!pHeader->hasGotPltInfo()){
		os<<"No gotplt section found";
	}else{
		printGot(pHeader->getGotPltInfo());
	}

}
/************************************************************************/
void printSection(const Section<S>* pSection){

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
/************************************************************************/
void printSegment(const Segment<S>* pSegment){

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
/************************************************************************/
void printSymbol(size_t iIdx, const Symbol<S>* pSymbol){

	std::string strName(pSymbol->getName());

	if(strName.length() > 20){
		strName = strName.substr(0,18) + "[...]";
	}

	os<<std::setw(6)<<iIdx;
	os<<" 0x"<<std::hex<<std::setfill('0')<<std::setw(2*sizeof(typename S::Addr))<<pSymbol->get_value()<<std::dec;
	os<<" 0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pSymbol->get_size()<<std::dec;
	os<<" "<<(int)pSymbol->get_info();
	os<<" "<<(int)pSymbol->get_other();
	os<<" "<<std::setw(3)<<pSymbol->get_shndx();
	os<<" "<<strName;

	os<<std::endl;
}
/************************************************************************/
void printSymbolTable(const SymbolTable<S>* pSymbolTable){

	const typename SymbolTable<S>::SymbolList& lstSymbols(pSymbolTable->getSymbols());

	int iIdx = 0;
	for(const auto& s : lstSymbols){
		printSymbol(iIdx++, s.get());
	}

}
/************************************************************************/
void printDynamic(const Dynamic<S>* pDynamic){

	std::string strTag;
	try{
		strTag = "("+Map::DynamicTag.getString(pDynamic->get_tag())+")";
	}catch(Tools::Exception& e){
		std::stringstream ss;
		ss<<(void*)(long)(pDynamic->get_tag());
		strTag = ss.str();
	}

	os<<" 0x"<<std::setfill('0')<<std::hex<<std::setw(sizeof(typename S::Dynamic_::TagType)*2)<<pDynamic->get_tag()<<std::dec;
	os<<"\t"<<std::setfill(' ')<<std::setw(20)<<strTag;
	os<<"\t"<<(void*)pDynamic->getUIntValue()<<std::endl;

}
/************************************************************************/
void printDynamicInfo(const DynamicInfo<S>* pDynamicInfo){

	const typename DynamicInfo<S>::DynamicTable& tabDynamic(pDynamicInfo->getDynamicTable());

	for(const auto& d : tabDynamic){
		printDynamic(d.get());
	}

}
/************************************************************************/
void printGot(const GotInfoBase<S>* pGotBase){

	os<<"Section: "<<pGotBase->getSection()->getName()<<std::endl;

	for(size_t i=0; i<pGotBase->getSize(); i++){
		os<<" 0x"<<std::setfill('0')<<std::hex<<std::setw(sizeof(typename S::Dynamic_::TagType)*2);
		os<<pGotBase->getAddress(i)<<std::dec;
		os<<"\t";
		os<<" 0x"<<std::setfill('0')<<std::hex<<std::setw(sizeof(typename S::Dynamic_::TagType)*2);
		os<<pGotBase->getValue(i)<<std::dec;
		os<<std::endl;
	}
}
/*************************************************************************/
	const  Header<S>* pHeader;
	const  Section<S>* pStringsSection;
};




/*************************************************************************/
}
}

#endif /* _ELF_Template_Printer_H_ */
