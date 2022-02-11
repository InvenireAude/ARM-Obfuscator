/*
 * File: GotInfo.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_GotInfo_H_
#define _ELF_Template_GotInfo_H_

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


/*************************************************************************/
/** The GotInfo class.
 *
 */
template<class S>
class GotInfoBase : public ELF::Impl::Component {
public:

	typedef typename S::Addr EntryType;


   ~GotInfoBase() throw(){
   }
	GotInfoBase(Header<S> *pHeader, const char* sName):
 		ELF::Impl::Component(pHeader->getContent()),
 			pHeader(pHeader){

 		pSection = pHeader->lookup(sName);
 
 		size_t iOffset = pSection->get_offset();
 		size_t iSize   = pSection->get_size();

 		std::cerr<<"Got info ["<<sName<<"] table offset: "<<(void*)(long)iOffset<<", size: "<<iSize<<", sizeof()"
 			<<sizeof(EntryType)<<std::endl;
 
 		 iNumEntries = iSize / sizeof(EntryType);
 
		if(iNumEntries < 2){
			throw Tools::Exception()<<".got tables should have at least 2 enteries, name: "<<sName;
		}

 		tabGotInfo = pSection->template getData< EntryType >();

	}
	
	EntryType getValue(size_t iIndex)const{
		if(iIndex + 2 >= iNumEntries){
			throw Tools::Exception()<<"Got index out of bounds, got: "<<iIndex<<", sz: "<<iNumEntries - 2;
		}

		return pConverter->convert(tabGotInfo[iIndex + 2]);
	}

	typename S::Addr getAddress(size_t iIndex)const{
		if(iIndex + 2 >= iNumEntries){
			throw Tools::Exception()<<"Got index out of bounds, got: "<<iIndex<<", sz: "<<iNumEntries - 2;
		}

		return pSection->get_addr() + (iIndex + 2) * sizeof(EntryType);
	}

	size_t getSize()const{
		return iNumEntries - 2;
	}

	inline Section<S> *getSection(){
		return pSection;
	};

	inline const Section<S> *getSection()const{
		return pSection;
	};

protected:

	Header<S> *pHeader;
	Section<S> *pSection;

	EntryType* tabGotInfo;
	size_t    iNumEntries;

};
/*************************************************************************/
template<class S>
class GotInfo : public GotInfoBase<S> {
	public:
	 GotInfo(Header<S>* pHeader):
	  GotInfoBase<S>(pHeader, ".got"){};

	typename GotInfoBase<S>::EntryType getDynamicSection()const{
		return GotInfoBase<S>::pConverter->convert(GotInfoBase<S>::tabGotInfo[0]);
	}
	
};
/*************************************************************************/
template<class S>
class GotPltInfo : public GotInfoBase<S> {
	public:
	 GotPltInfo(Header<S>* pHeader):
	  GotInfoBase<S>(pHeader, ".got.plt"){};

};
/*************************************************************************/
}
}

#endif /* _ELF_Template_GotInfo_H_ */
