/*
 * File: DynamicInfo.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_DynamicInfo_H_
#define _ELF_Template_DynamicInfo_H_

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
class Dynamic;

/*************************************************************************/
/** The DynamicInfo class.
 *
 */
template<class S>
class DynamicInfo : public ELF::Impl::Component {
public:

	typedef std::vector< std::unique_ptr< Dynamic<S> > > DynamicTable;

	DynamicTable& getDynamicTable(){
		return tabDynamicInfo;
	}

	const DynamicTable& getDynamicTable()const{
		return tabDynamicInfo;
	}

DynamicInfo(Header<S> *pHeader, const char* sName):
 	ELF::Impl::Component(pHeader->getContent()),
 	pHeader(pHeader){

 	pSection = pHeader->lookup(sName);
 
 	size_t iOffset = pSection->get_offset();
 	size_t iSize   = pSection->get_size();

 	std::cerr<<"Dynamic table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
 		<<sizeof(typename S::Symbol_)<<std::endl;
 
 	size_t iNumEntries = iSize / sizeof(typename S::Dynamic_);
 
 	typename S::Dynamic_ *pDynamicData = pSection->template getData< typename S::Dynamic_ >();

 	while(iNumEntries > 0 && pDynamicData->d_tag != DT_NULL
	 ){
		tabDynamicInfo.emplace_back(new Dynamic<S>(this, pDynamicData));
		pDynamicData++;
		iNumEntries--;
	}

}

 void write(){
	
	size_t iOffset = pSection->get_offset();
 	size_t iSize   = pSection->get_size();

 	std::cerr<<"Dynamic table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
 		<<sizeof(typename S::Symbol_)<<std::endl;
 
 	size_t iNumEntries = iSize / sizeof(typename S::Dynamic_);
 
 	typename S::Dynamic_ *pDynamicData = pSection->template getData< typename S::Dynamic_ >();

	for(auto& d : tabDynamicInfo){
		d->write(pDynamicData++);
	}
	
 }

/*************************************************************************/
~DynamicInfo() throw(){
}

protected:

	Header<S> *pHeader;

	Section<S> *pSection;

	DynamicTable tabDynamicInfo;

};

/*************************************************************************/
}
}

#endif /* _ELF_Template_DynamicInfo_H_ */
