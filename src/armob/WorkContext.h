/*
 * File: WorkContext.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_WorkContext_H_
#define _ARMOB_WorkContext_H_

#include <tools/common.h>

#include "Symbol.h"
#include <asm/GenericDetailFactory.h>
#include <elf/elf.h>

namespace ARMOB {

class DiscoveredSymbols;
class DiscoveredDetails;
class Symbol;

/*************************************************************************/
/** The WorkContext class.
 *
 */
class WorkContext {
public:

	virtual ~WorkContext() throw();
	WorkContext(const ELF::Artefact* pArtefact);
	
	inline ASM::GenericDetailFactory* getGenericDetailFactory()const{
		return ptrGenericDetailFactory.get();
	}

	static const std::string& CTextSection;
	static const std::string& CPltSection;

	DiscoveredDetails* getDetails(const std::string& strSectionName);
	DiscoveredSymbols* getSymbols()const;

	inline ELF::Elf64::Header* getHeader64()const{
		return ptrArtefactCopy->getHeader64();
	}

	inline ELF::Elf32::Header* getHeader32()const{
		return ptrArtefactCopy->getHeader32();
	}

	void save(const std::string& strFileName)const;

protected:

	typedef std::unordered_map< std::string, std::unique_ptr<DiscoveredDetails> > DetailsMap;

	DetailsMap 								   hmDetails;

	std::unique_ptr<DiscoveredSymbols>         ptrDiscoveredSymbols;
	std::unique_ptr<ASM::GenericDetailFactory> ptrGenericDetailFactory;

	std::unique_ptr<ELF::Artefact> ptrArtefactCopy;

};

/*************************************************************************/
}

#endif /* _ARMOB_WorkContext_H_ */
