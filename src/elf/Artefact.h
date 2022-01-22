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

	Identification* getIdentification()const;

	static Artefact* CreateFromFile(const std::string& strName);

protected:

	std::unique_ptr<Elf32::Header>   ptrHeader32;
	virtual Content*                 getContent()const = 0;

};

/*************************************************************************/
}

#endif /* _ELF_Artefact_H_ */
