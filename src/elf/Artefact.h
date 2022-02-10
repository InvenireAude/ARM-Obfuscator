/*
 * File: Artefact.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Artefact_H_
#define _ELF_Artefact_H_

#include <tools/common.h>
#include <elf/elf32/elf32.h>
#include <elf/elf64/elf64.h>

namespace ELF {

/*************************************************************************/
/** The Artefact class.
 *
 */

class Artefact {
public:

	virtual ~Artefact() throw();
	Artefact();

	inline Elf32::Header* getHeader32()const{
		
		if(!ptrHeader32){
			throw Tools::Exception()<<"Header for 32bit not set, wrong ELF type ?";
		}

		return ptrHeader32.get();
	}

	inline Elf64::Header* getHeader64()const{
		
		if(!ptrHeader64){
			throw Tools::Exception()<<"Header for 32bit not set, wrong ELF type ?";
		}

		return ptrHeader64.get();
	}

	Identification* getIdentification()const;


protected:

	std::unique_ptr<Elf32::Header>   ptrHeader32;
	std::unique_ptr<Elf64::Header>   ptrHeader64;

	virtual Content*                 getContent()const = 0;
	friend class ArtefactCopy;
};

/*************************************************************************/
}

#endif /* _ELF_Artefact_H_ */
