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
	pHeader(pHeader){
	std::cerr<<(void*)this<<"Offset :"<<(void*)iOffset<<", sizeof: "<<sizeof(section)<<std::endl;
	memcpy(&section, pContent->getData(iOffset, sizeof(section)), sizeof(section));
}
/*************************************************************************/
~Section() throw(){
}
/*************************************************************************/
void write(size_t iOffset){
	memcpy(pContent->getData(iOffset, sizeof(section)), &section, sizeof(section));
}
/*************************************************************************/
const char* getName()const{
	return pHeader->getStringsSection()->getString(get_name());
}
/*************************************************************************/
const char* getString(size_t iOffset)const{
	
	std::cerr<<(void*)this<<" Offset :"<<(void*)iOffset<<", in section: "<<(void*)(long)get_offset()<<std::endl;


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

void set_name(typename S::Word sh_name){
	section.sh_name = pConverter->convert(sh_name);
}
void set_type(typename S::Word sh_type){
	section.sh_type = pConverter->convert(sh_type);
}
void set_flags(typename S::Word sh_flags){
	section.sh_flags = pConverter->convert(sh_flags);
}
void set_addr(typename S::Addr sh_addr){
	section.sh_addr = pConverter->convert(sh_addr);
}
void set_offset(typename S::Off sh_offset){
	section.sh_offset = pConverter->convert(sh_offset);
}
void set_size(typename S::Word sh_size){
	section.sh_size = pConverter->convert(sh_size);
}
void set_link(typename S::Word sh_link){
	section.sh_link = pConverter->convert(sh_link);
}
void set_info(typename S::Word sh_info){
	section.sh_info = pConverter->convert(sh_info);
}
void set_addralign(typename S::Word sh_addralign){
	section.sh_addralign = pConverter->convert(sh_addralign);
}
void set_entsize(typename S::Word sh_entsize){
	section.sh_entsize = pConverter->convert(sh_entsize);
}

protected:
	
	const Header<S> *pHeader;

	typename S::Section_ section;
	
};

/*************************************************************************/
}
}

#endif /* _ELF_Template_Section_H_ */
