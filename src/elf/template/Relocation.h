/*
 * File: Relocation.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Relocation_H_
#define _ELF_Template_Relocation_H_


#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>
#include <elf/Specification.h>

namespace ELF {
namespace Template {
	

/*************************************************************************/
/** The Relocation class.
 *T
 */
template<class S>
class RelocationInfo;

template<class S>
class Relocation {
public:


	inline static size_t CElfSize = sizeof(typename S::Relocation_);


/*************************************************************************/
Relocation(RelocationInfo<S>* pRelocationInfo, typename S::Relocation_* pRelocationData):
	pRelocationInfo(pRelocationInfo),
	relocation(*pRelocationData){
}
/*************************************************************************/
~Relocation() throw(){	
}
/*************************************************************************/

  typename S::Addr   get_offset()const{
	  return pRelocationInfo->getConverter()->convert(relocation.r_offset);
  }
  
  void set_offset(typename S::Addr iOffset){
	  relocation.r_offset = pRelocationInfo->getConverter()->convert(iOffset);
  }
  
  typename S::Relocation_::InfoType  get_info()const{
	  return pRelocationInfo->getConverter()->convert(relocation.r_info);
  }
  typename S::Relocation_::AddEndType get_addend()const{
	  return pRelocationInfo->getConverter()->convert(relocation.r_addend);
  }

  inline typename S::Off getSymbolOffset()const{
	  return S::Relocation_::ToSymbolOffset(get_info());
  }

  inline uint32_t getType()const{
	  return S::Relocation_::ToType(get_info());
  }


/*************************************************************************/
	
	void write(typename S::Relocation_* pRelocationData){
		*pRelocationData = relocation;
	}

protected:
	RelocationInfo<S>* pRelocationInfo;

	typename S::Relocation_ relocation;
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Relocation_H_ */
