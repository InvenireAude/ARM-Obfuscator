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

	printHeaderHex();

	const typename Header<S>::SectionList& lstSections(pHeader->getSections());

	printSectionsHeader();
	int iIdx = 0;
	for(const auto& s: lstSections){
		os<<std::setfill('0')<<std::setw(3)<<iIdx++;
		printSection(s.get());
	}

	const typename Header<S>::SegmentList& lstSegments(pHeader->getSegments());

	printSegmentsHeader();
	iIdx = 0;
	for(const auto& s: lstSegments){
		os<<std::setfill('0')<<std::setw(3)<<iIdx++;
		printSegment(s.get());
	}

	iIdx = 0;
	for(const auto& s: lstSegments){
		os<<std::setfill('0')<<std::setw(3)<<iIdx++;
		printSegmentSections(s.get());
	}

	os<<"Symbols:"<<std::endl;

	if(!pHeader->hasSymbolTable()){
		os<<"No symbol table found."<<std::endl;
	}else{
		printSymbolTable(pHeader->getSymbolTable());
	}

	os<<"Dynamic symbols:"<<std::endl;


	if(!pHeader->hasDynSymbolTable()){
		os<<"No symbol table found."<<std::endl;
	}else{
		printSymbolTable(pHeader->getDynSymbolTable());
	}

	if(!pHeader->hasDynamicInfo()){
		os<<"No dynamic section found."<<std::endl;
	}else{
		printDynamicInfo(pHeader->getDynamicInfo());
	}

	if(!pHeader->hasGotInfo()){
		os<<"No got section found."<<std::endl;
	}else{
		printGot(pHeader->getGotInfo());
	}

	if(!pHeader->hasGotPltInfo()){
		os<<"No gotplt section found."<<std::endl;
	}else{
		printGot(pHeader->getGotPltInfo());
	}

	if(!pHeader->hasRelocationInfo()){
		os<<"No Relocation section found."<<std::endl;
	}else{
		printRelocationInfo(pHeader->getRelocationInfo());
	}

	if(!pHeader->hasRelocationPltInfo()){
		os<<"No Relocationplt section found."<<std::endl;
	}else{
		printRelocationInfo(pHeader->getRelocationPltInfo());
	}

}
/*************************************************************************/
void printHeaderHex(){
	
	std::string strHex(Utils::Helper::BinarytoHex(pHeader->getRaw(), sizeof(typename S::Header_)));

	for(int i=0; i<strHex.length(); i += 2){
		if(i % 32 == 0){
			os<<std::endl<<"\t Hex: ["<<std::hex<<std::setw(2)<<i<<std::dec<<"]\t";
		}
		os<<strHex.substr(i, 2)<<" ";
	}

	os<<std::endl;
}
/*************************************************************************/
void printSectionsHeader(){
	
	os<<std::endl<<"Sections:"<<std::endl;

	os<<"Idx";
	os<<std::setfill(' ')<<std::setw(16)<<" Name :";

	os<<" "<<std::setfill(' ')<<std::setw(18)<<"Type:";
	os<<" "<<std::setfill(' ')<<std::setw(8)<<"Flags:";
	os<<" "<<std::setfill(' ')<<std::setw(16)<<"Address:";
	os<<" "<<std::setfill(' ')<<std::setw(8)<<"Offset:";
	os<<" "<<std::setfill(' ')<<std::setw(8)<<"Size:";

	os<<" "<<std::setw(8)<<"Link:";
	os<<" "<<std::setw(8)<<"Info:";
	os<<" "<<std::setw(4)<<"Algn:";
	os<<" "<<std::setw(8)<<"EntSize:";
	os<<std::endl;;
}
/************************************************************************/
void printSection(const Section<S>* pSection){

	//os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_name()<<std::dec;

	os<<std::setfill(' ')<<std::setw(16)<<pSection->getName();

	try{
		std::string strName(Map::SectionType.getString(pSection->get_type()));
		os<<std::setfill(' ')<<std::setw(16)<<strName;
	}catch(Tools::Exception& e){
		os<<"      0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_type()<<std::dec;
	}

	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_flags()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSection->get_addr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_offset()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSection->get_size()<<std::dec;

	os<<" "<<std::setw(8)<<pSection->get_link();
	os<<" "<<std::setw(8)<<pSection->get_info();
	os<<" "<<std::setw(4)<<pSection->get_addralign();
	os<<" "<<std::setw(8)<<pSection->get_entsize();

	os<<std::endl;
}
/************************************************************************/
void printSegmentsHeader(){

	os<<std::endl<<"Segments:"<<std::endl;

	os<<std::setw(3)<<"Idx";

	os<<std::setfill(' ');

	os<<std::setw(18)<<"type";

	os<<" "<<std::setw(16)<<"offset";
	os<<" "<<std::setw(16)<<"vaddr";
	os<<" "<<std::setw(16)<<"paddr";
	os<<" "<<std::setw(16)<<"filesz";
	os<<" "<<std::setw(16)<<"memsz";
	os<<" "<<std::setw(8)<<"flags";
	os<<" "<<std::setw(4)<<"align";

	os<<std::endl;
}
/************************************************************************/
void printSegment(const Segment<S>* pSegment){

	try{
		os<<std::setfill(' ')<<std::setw(18)<<Map::SegmentType.getString(pSegment->get_type());
	}catch(Tools::Exception& e){
		os<<"        0x"<<std::hex<<std::setfill('0')<<std::setw(8)<<std::setw(8)<<pSegment->get_type()<<std::dec;
	}

	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSegment->get_offset()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSegment->get_vaddr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSegment->get_paddr()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSegment->get_filesz()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(16)<<pSegment->get_memsz()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(8)<<pSegment->get_flags()<<std::dec;
	os<<" "<<std::hex<<std::setfill('0')<<std::setw(4)<<pSegment->get_align()<<std::dec;

	os<<std::endl;
}
/************************************************************************/
void printSegmentSections(const Segment<S>* pSegment){

	const typename Header<S>::SectionList& lstSections(pHeader->getSections());


	for(const auto& s: lstSections){

		if( !(s->get_offset() + s->get_size() < pSegment->get_offset() ||
		      s->get_offset() >= pSegment->get_offset() + pSegment->get_filesz())){
				  os<<" "<<s->getName();
			  }
	}

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

	try{
		os<<std::setfill(' ')<<std::setw(8)<<Map::SymbolBind.getString(pSymbol->getBinding());
	}catch(Tools::Exception& e){
		os<<"  0x"<<std::hex<<std::setfill('0')<<std::setw(4)<<pSymbol->getBinding()<<std::dec;
	}

	try{
		os<<std::setfill(' ')<<std::setw(8)<<Map::SymbolType.getString(pSymbol->getType());
	}catch(Tools::Exception& e){
		os<<"  0x"<<std::hex<<std::setfill('0')<<std::setw(4)<<pSymbol->getType()<<std::dec;
	}

	if(pSymbol->get_shndx() < pHeader->getSections().size()){
		os<<" "<<std::setw(3)<<pSymbol->get_shndx();
	}else{
		os<<" ...";
	}

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
/************************************************************************/
void printRelocationInfo(const RelocationInfo<S>* pRelocationInfo){

	os<<"Section: "<<pRelocationInfo->getSection()->getName()<<std::endl;

	const typename RelocationInfo<S>::RelocationTable& tabRelocation(pRelocationInfo->getRelocationTable());

	for(const auto& d : tabRelocation){
		os<<" 0x"<<std::setfill('0')<<std::hex<<std::setw(sizeof(typename S::Addr)*2);
		os<<d->get_offset()<<std::dec;
		os<<"\t";
		os<<" 0x"<<std::setfill('0')<<std::hex<<std::setw(8);
		os<<d->getType()<<std::dec;
		os<<"\t";
		os<<"["<<d->getSymbolOffset()<<"]";
		os<<"\t"<<pHeader->getDynSymbolTable()->get(d->getSymbolOffset())->getName();
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
