/*
 * File: SectionBook.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "SectionBook.h"


namespace ELF {

SectionBook SectionBook::TheInstance;

SectionBook::PLTInfoMap SectionBook::ThePltInfo({
	{ { ELFCLASS64, EM_AARCH64 }, { 32, 16 }}
});
/*************************************************************************/
SectionBook::SectionBook(){
}
/*************************************************************************/
bool SectionBook::getPLTInfo(const Elf64::Header* pHeader, PLTInfo* pPLTInfo)const{
	PLTInfoMap::key_type key(ELFCLASS64, static_cast<Machine>(pHeader->get_machine()));

	PLTInfoMap::const_iterator it = ThePltInfo.find(key);

	if(it == ThePltInfo.end()){
		return false;
	}

	*pPLTInfo = it->second;
	return true;
}
/*************************************************************************/
bool SectionBook::getPLTInfo(const Elf32::Header* pHeader, PLTInfo* pPLTInfo)const{
	PLTInfoMap::key_type key(ELFCLASS32, static_cast<Machine>(pHeader->get_machine()));

	PLTInfoMap::const_iterator it = ThePltInfo.find(key);

	if(it == ThePltInfo.end()){
		return false;
	}

	*pPLTInfo = it->second;
	return true;
}
/*************************************************************************/
}
