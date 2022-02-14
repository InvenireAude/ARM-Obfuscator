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


void setUIntValue(uint64_t iValue){
	switch(get_tag()){
		case DT_NULL : break;
				
		case DT_NEEDED : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_PLTRELSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_PLTGOT : 
			std::cout<<"test"<<std::endl;
		dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue));
		 break;
		
		case DT_HASH : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_STRTAB : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SYMTAB : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_RELA : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_RELASZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_RELAENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_STRSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SYMENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_INIT : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_FINI : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SONAME : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_RPATH : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_REL : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_RELSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_RELENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_PLTREL : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_DEBUG : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_JMPREL : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_INIT_ARRAY : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_FINI_ARRAY : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_INIT_ARRAYSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_FINI_ARRAYSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_RUNPATH : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_FLAGS : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_PREINIT_ARRAY : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_PREINIT_ARRAYSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_AUXILIARY : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_RTLDINF : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_CAP : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_SYMTAB : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_SYMSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_SORTENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_SYMSORT : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_SYMSORTSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_TLSSORT : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_TLSSORTSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_CAPINFO : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_STRPAD : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_CAPCHAIN : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SUNW_LDMACH : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_CAPCHAINENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SUNW_CAPCHAINSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_CHECKSUM : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_PLTPADSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_MOVEENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_MOVESZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_POSFLAG_1 : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SYMINSZ : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SYMINENT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_CONFIG : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_DEPAUDIT : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_AUDIT : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_PLTPAD : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_MOVETAB : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_SYMINFO : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_RELACOUNT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_RELCOUNT : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_FLAGS_1 : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_VERDEF : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_VERDEFNUM : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_VERNEED : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;
		case DT_VERNEEDNUM : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_SPARC_REGISTER : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_AUXILIARY : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_USED : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;
		case DT_FILTER : dynamic.d_un.d_val = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::ValType>(iValue)); break;

		case DT_GNUHASH : dynamic.d_un.d_ptr = pDynamicInfo->getConverter()->convert(reinterpret_cast<typename S::Dynamic_::AddrType>(iValue)); break;

	}

}


void write(typename S::Dynamic_* pDynamicData){
	*pDynamicData = dynamic;
}

protected:
	DynamicInfo<S>* pDynamicInfo;

	typename S::Dynamic_ dynamic;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Dynamic_H_ */
