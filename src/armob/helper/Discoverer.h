/*
 * File: Discoverer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_Discoverer_H_
#define _ARMOB_Helper_Discoverer_H_

#include <tools/common.h>

#include <elf/elf.h>


namespace ELF {
	class Artefact;
}

namespace ASM{
	class GenericInstruction;
}

namespace ARMOB {
class WorkContext;
class DiscoveredSymbols;

namespace Helper {

/*************************************************************************/
}
}
namespace ARMOB {
namespace Helper {

/*************************************************************************/
/** The Discoverer class.
 *
 */
class Discoverer {
public:

	virtual ~Discoverer() throw();

	Discoverer(WorkContext* pWorkContext);

	void discover();
	
protected:

	WorkContext               *pWorkContext;
	DiscoveredSymbols         *pDiscoveredSymbols;
	const ELF::Elf64::Header  *pHeader;
	
	void build(const std::string& strSectionName);
	void resolve(const std::string& strSectionName);

	void discoverSymbols();
	void discoverPLTSymbols();
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_Discoverer_H_ */
