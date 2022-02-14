/*
 * File: Expander.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "Expander.h"

namespace ELF {

/*************************************************************************/
Expander::Expander(Elf64::Header* pHeader):
 pHeader(pHeader){}
/*************************************************************************/
void Expander::expand(size_t iNeededSpace){

  const size_t iLoadSegmentAlignment = 0x10000;

    // size_t iNeededSpace = 130000;

    size_t iDataMovementAligned = (iNeededSpace / iLoadSegmentAlignment) * iLoadSegmentAlignment;
    // size_t iDataMovementAligned = iNeededSpace & ~(iLoadSegmentAlignment - 1);

    size_t iRemaing = iNeededSpace % iLoadSegmentAlignment;
  
    pTextSection    = pHeader->lookup(".text");
    pEhFrameSection = pHeader->lookup(".eh_frame");
    pDynamicSection = pHeader->lookup(".dynamic");

    iOrginalDataStart = pHeader->lookup(".data")->get_addr();

    size_t iSpaceAvailable = pDynamicSection->get_offset() - (pEhFrameSection->get_offset() + pEhFrameSection->get_size());

    std::cout<<"iSpaceAvailable ?  iRemaing"<<(void*)iSpaceAvailable<<" ?? "<<(void*)iRemaing<<std::endl;

    if(iRemaing > iSpaceAvailable){
      iDataMovementAligned += iLoadSegmentAlignment;
      iRemaing = 0;
    }

    std::cout<<"iSpaceAvailable ?  iRemaing"<<(void*)iSpaceAvailable<<" ?? "<<(void*)iRemaing<<std::endl;

    insertSpaceAfter(pTextSection->get_offset() + pTextSection->get_size() - 1, iDataMovementAligned);
    
    const Elf64::Header::SectionList& lstSections(pHeader->getSections());

    size_t iLastTextSegmentByte = pEhFrameSection->get_offset() + pEhFrameSection->get_size() - 1;
    for(auto& s : lstSections){
      if(s->get_offset() > pTextSection->get_offset() &&
         s->get_offset() < iLastTextSegmentByte){
          pHeader->getContent()->copyData(s->get_offset() + iRemaing, s->get_offset(), s->get_size());
          s->set_offset(s->get_offset() + iRemaing);     
          s->set_addr(s->get_addr() + iRemaing);
      }
    }

    pTextSection->set_size(pTextSection->get_size() + iRemaing);     

	iDataSegmentShift = iDataMovementAligned;
}
/*************************************************************************/
void Expander::insertSpaceAfter(Elf64::S::Off iOffset, size_t iSize){

    Content *pContent = pHeader->getContent();

		pContent->makeSpace(reinterpret_cast<size_t>(iOffset + 1), iSize);
		pHeader->set_shoff(pHeader->get_shoff()+iSize);

	    std::cout<<"offset :"<<(void*)iOffset<<std::endl;

		for(auto& s: pHeader->getSections())
		if(s->get_type()){

			std::cout<<"Checking section :"<<(void*)s->get_offset()<<std::endl;

			if( s->get_offset() <= iOffset && 
			    s->get_offset() + s->get_size() > iOffset){
					std::cout<<"Update section :"<<(void*)s->get_offset()<<std::endl;
					s->set_size(s->get_size() + iSize);
			}else if( s->get_offset() > iOffset ){
					std::cout<<"Moving section :"<<(void*)s->get_offset()<<std::endl;
				s->set_offset(s->get_offset() + iSize);
				s->set_addr(s->get_addr() + iSize);
			}
		}

		for(auto& s: pHeader->getSegments()){

		  std::cout<<"Checking segment :"<<(void*)s->get_offset()<<std::endl;

			if( s->get_offset() <= iOffset && 
			    s->get_offset() + s->get_filesz() > iOffset){
					std::cout<<"Update segment :"<<(void*)s->get_offset()<<std::endl;
					s->set_filesz(s->get_filesz() + iSize);
					s->set_memsz(s->get_memsz() + iSize);
			}else if( s->get_offset() > iOffset ){
				std::cout<<"Moving segment :"<<(void*)s->get_offset()<<std::endl;
				s->set_offset(s->get_offset() + iSize);
				s->set_paddr(s->get_paddr() + iSize);
				s->set_vaddr(s->get_vaddr() + iSize);
			}
		}
	
}

/*************************************************************************/
void Expander::updateDataSegmentSymbols(){


	if(pHeader->hasDynamicInfo()){

		Elf64::DynamicInfo::DynamicTable& tabDynamic(pHeader->getDynamicInfo()->getDynamicTable());

		ELF::Elf64::Section *pPltGotSection    = pHeader->lookup(".got.plt");

		for(auto& d: tabDynamic){
			if(d->get_tag() == DT_PLTGOT){
				std::cout<<"Setting DT_PLTGOT"<<(void*)pPltGotSection->get_addr()<<std::endl;
				d->setUIntValue(pPltGotSection->get_addr());
			}
		}
	}

	if(pHeader->hasRelocationInfo()){

		Elf64::RelocationInfo::RelocationTable& tabRelocation(pHeader->getRelocationInfo()->getRelocationTable());

		for(auto& r : tabRelocation){
			r->set_offset(r->get_offset() + iDataSegmentShift);
		}
	}

	if(pHeader->hasRelocationPltInfo()){

		Elf64::RelocationInfo::RelocationTable& tabRelocationPlt(pHeader->getRelocationPltInfo()->getRelocationTable());

		for(auto& r : tabRelocationPlt){
			std::cout<<"Setting tabRelocationPlt"<<(void*)r->get_offset()<<std::endl;
			r->set_offset(r->get_offset() + iDataSegmentShift);
		}
	}



	if(pHeader->hasSymbolTable()){

		Elf64::SymbolTable::SymbolList& lstSymbols(pHeader->getSymbolTable()->getSymbols());

		for(auto& s : lstSymbols){
			if(s->get_value() >= iOrginalDataStart){
				std::cout<<"Setting symbol"<<s->getName()<<std::endl;
				s->set_value(s->get_value() + iDataSegmentShift);
			}
		}
	}

	if(pHeader->hasDynSymbolTable()){

		Elf64::SymbolTable::SymbolList& lstDynSymbols(pHeader->getDynSymbolTable()->getSymbols());

		for(auto& s : lstDynSymbols){
			if(s->get_value() >= iOrginalDataStart){
				std::cout<<"Setting dynamic symbol"<<s->getName()<<std::endl;
				s->set_value(s->get_value() + iDataSegmentShift);
			}
		}
	}

}
/*************************************************************************/
}
