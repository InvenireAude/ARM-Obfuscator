/*
 * File: RelocationInfo.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_RelocationInfo_H_
#define _ELF_Template_RelocationInfo_H_

#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>

#include <vector>

namespace ELF {
namespace Template {

template<class S>
class Header;

template<class S>
class Section;

template<class S>
class Relocation;

/*************************************************************************/
/** The RelocationInfo class.
 *
 */
template<class S>
class RelocationInfo : public ELF::Impl::Component {
public:

	typedef std::vector< std::unique_ptr< Relocation<S> > > RelocationTable;


~RelocationInfo() throw(){
}
RelocationInfo(Header<S> *pHeader, const char* sName):
 	ELF::Impl::Component(pHeader->getContent()),
 	pHeader(pHeader){

 	pSection = pHeader->lookup(sName);
 
 	size_t iOffset = pSection->get_offset();
 	size_t iSize   = pSection->get_size();

 	std::cerr<<"Relocation table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
 		<<sizeof(typename S::Symbol_)<<std::endl;
 
 	size_t iNumEntries = iSize / sizeof(typename S::Relocation_);
 
 	typename S::Relocation_ *pRelocationData = pSection->template getData< typename S::Relocation_ >();

 	while(iNumEntries > 0){
		tabRelocationInfo.emplace_back(new Relocation<S>(this, pRelocationData));
		pRelocationData++;
		iNumEntries--;
	}

}

	void write(){

		size_t iOffset = pSection->get_offset();
		size_t iSize   = pSection->get_size();

		std::cerr<<"Relocation table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
			<<sizeof(typename S::Symbol_)<<std::endl;
	
		size_t iNumEntries = iSize / sizeof(typename S::Relocation_);
	
		typename S::Relocation_ *pRelocationData = pSection->template getData< typename S::Relocation_ >();

		for(auto& r : tabRelocationInfo){
			r->write(pRelocationData++);
		}

	}

/*************************************************************************/

	inline Section<S> *getSection(){
		return pSection;
	};

	inline const Section<S> *getSection()const{
		return pSection;
	};

	RelocationTable& getRelocationTable(){
		return tabRelocationInfo;
	}

	const RelocationTable& getRelocationTable()const{
		return tabRelocationInfo;
	}

protected:

	Header<S> *pHeader;

	Section<S> *pSection;

	RelocationTable tabRelocationInfo;

};

/*************************************************************************/
}
}

#endif /* _ELF_Template_RelocationInfo_H_ */
