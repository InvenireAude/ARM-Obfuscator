/*
 * File: Section.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Template_Section_H_
#define _ELF_Template_Section_H_

#include <tools/common.h>
#include <elf/utils/Converter.h>
#include <elf/impl/Component.h>
#include <elf/Content.h>

namespace ELF {
namespace Template {

template<class S>
class Header;

/*************************************************************************/
/** The Section class.
 *
 */
template<class S>
class Section : public Impl::Component {
public:

	const typename S::Section_*  getRaw()const{
		return &section;
	}

	template<class T>
	 T* getData(){
		std::cerr<<"Get data for offset: "<<get_offset();
		return reinterpret_cast<T*>(pContent->getData(get_offset()));
	}

	template<class T>
	const T* getData()const{
		std::cerr<<"Get data for offset: "<<get_offset();
		return reinterpret_cast<const T*>(pContent->getData(get_offset()));
	}

/*************************************************************************/
Section(Header<S> *pHeader, size_t iOffset):
	Impl::Component(pHeader->getContent()),
	pHeader(pHeader),
	section(*reinterpret_cast<typename S::Section_*>(pContent->getData(iOffset, sizeof(typename S::Section_)))){
	std::cerr<<"Offset :"<<iOffset<<", sizeof: "<<sizeof(section)<<std::endl;
}
/*************************************************************************/
~Section() throw(){
}
/*************************************************************************/
const char* getName()const{
	return pHeader->getStringsSection()->getString(get_name());
}
/*************************************************************************/
const char* getString(size_t iOffset)const{
	
	if(iOffset > get_size())
		throw Tools::Exception()<<"String offset is out of bounds, section size: "<<get_size();

	return reinterpret_cast<const char*>(pContent->getData(get_offset()) + iOffset);
}
/*************************************************************************/
typename S::Word get_name()const{
	return pConverter->convert(section.sh_name);
}
typename S::Word get_type()const{
	return pConverter->convert(section.sh_type);
}
typename S::Word get_flags()const{
	return pConverter->convert(section.sh_flags);
}
typename S::Addr get_addr()const{
	return pConverter->convert(section.sh_addr);
}
typename S::Off  get_offset()const{
	return pConverter->convert(section.sh_offset);
}
typename S::Word get_size()const{
	return pConverter->convert(section.sh_size);
}
typename S::Word get_link()const{
	return pConverter->convert(section.sh_link);
}
typename S::Word get_info()const{
	return pConverter->convert(section.sh_info);
}
typename S::Word get_addralign()const{
	return pConverter->convert(section.sh_addralign);
}
typename S::Word get_entsize()const{
	return pConverter->convert(section.sh_entsize);
}

protected:
	
	const Header<S> *pHeader;

	typename S::Section_& section;
	
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Section_H_ */
