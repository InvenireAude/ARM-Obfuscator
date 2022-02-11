/*
 * File: Dynamic.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Dynamic_H_
#define _ELF_Template_Dynamic_H_


#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>
#include <elf/Specification.h>

namespace ELF {
namespace Template {
	

/*************************************************************************/
/** The Dynamic class.
 *T
 */
template<class S>
class DynamicInfo;

template<class S>
class Dynamic {
public:


	inline static size_t CElfSize = sizeof(typename S::Dynamic_);


/*************************************************************************/
Dynamic(DynamicInfo<S>* pDynamicInfo, typename S::Dynamic_* pDynamicData):
	pDynamicInfo(pDynamicInfo),
	dynamic(*pDynamicData){
}
/*************************************************************************/
~Dynamic() throw(){	
}

/*************************************************************************/
typename S::Dynamic_::TagType get_tag()const{
	return pDynamicInfo->getConverter()->convert(dynamic.d_tag);
}

uint64_t getUIntValue()const{
	switch(get_tag()){
		case DT_NULL : return 0;

		case DT_NEEDED : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_PLTRELSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_PLTGOT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_HASH : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_STRTAB : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SYMTAB : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_RELA : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_RELASZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_RELAENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_STRSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SYMENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_INIT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_FINI : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SONAME : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_RPATH : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_REL : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_RELSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_RELENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_PLTREL : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_DEBUG : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_JMPREL : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_INIT_ARRAY : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_FINI_ARRAY : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_INIT_ARRAYSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_FINI_ARRAYSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_RUNPATH : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_FLAGS : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_PREINIT_ARRAY : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_PREINIT_ARRAYSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_AUXILIARY : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_RTLDINF : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_CAP : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_SYMTAB : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_SYMSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_SORTENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_SYMSORT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_SYMSORTSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_TLSSORT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_TLSSORTSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_CAPINFO : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_STRPAD : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_CAPCHAIN : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SUNW_LDMACH : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_CAPCHAINENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SUNW_CAPCHAINSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_CHECKSUM : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_PLTPADSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_MOVEENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_MOVESZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_POSFLAG_1 : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SYMINSZ : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SYMINENT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_CONFIG : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_DEPAUDIT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_AUDIT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_PLTPAD : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_MOVETAB : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_SYMINFO : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_RELACOUNT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_RELCOUNT : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_FLAGS_1 : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_VERDEF : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_VERDEFNUM : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_VERNEED : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
		case DT_VERNEEDNUM : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_SPARC_REGISTER : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_AUXILIARY : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_USED : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);
		case DT_FILTER : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_val);

		case DT_GNUHASH : return pDynamicInfo->getConverter()->convert(dynamic.d_un.d_ptr);
	}

	return 0x0;
}

protected:
	DynamicInfo<S>* pDynamicInfo;

	typename S::Dynamic_& dynamic;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Dynamic_H_ */
