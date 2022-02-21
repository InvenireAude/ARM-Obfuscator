/*
 * File: SymbolDiscoverer.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_SymbolDiscoverer_H_
#define _ARMOB_Helper_SymbolDiscoverer_H_

#include <tools/common.h>

#include <elf/elf.h>


namespace ELF {
	class Artefact;
}

namespace ASM{
	class GenericInstruction;
}

namespace ARMOB {
class DiscoveredSymbols;

namespace Helper {

/*************************************************************************/
}
}
namespace ARMOB {
namespace Helper {

/*************************************************************************/
/** The SymbolDiscoverer class.
 *
 */
class SymbolDiscoverer {
public:

	virtual ~SymbolDiscoverer() throw();

	SymbolDiscoverer(const ELF::Artefact* pArtefact, 
					 DiscoveredSymbols*   pDiscoveredSymbols);

	void discover();
	void build();
	void resolve();
	
protected:
	const ELF::Artefact* pArtefact;
	DiscoveredSymbols*   pDiscoveredSymbols;
	
	const ELF::Elf64::Header* pHeader;

	void discoverPLTSymbols();
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_SymbolDiscoverer_H_ */
