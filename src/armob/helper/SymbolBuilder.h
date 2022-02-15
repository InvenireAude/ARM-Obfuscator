/*
 * File: SymbolBuilder.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_SymbolBuilder_H_
#define _ARMOB_Helper_SymbolBuilder_H_

#include <tools/common.h>

#include <asm/arm/arm64/spec/Encoding.h>
#include <asm/ItemList.h>

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
/** The SymbolBuilder class.
 *
 */
class SymbolBuilder {
public:

	virtual ~SymbolBuilder() throw();

	SymbolBuilder(const ELF::Artefact* pArtefact, 
					 DiscoveredSymbols*   pDiscoveredSymbols);

	
	 ASM::ItemList::iterator createBlankInstruction(ASM::ItemList::iterator it, ASM::ARM::ARM64::Spec::EncodingId iEncodingId);

protected:
	const ELF::Artefact* pArtefact;
	DiscoveredSymbols*   pDiscoveredSymbols;
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_SymbolBuilder_H_ */
