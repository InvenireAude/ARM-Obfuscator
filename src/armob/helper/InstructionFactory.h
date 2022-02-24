/*
 * File: InstructionFactory.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_InstructionFactory_H_
#define _ARMOB_Helper_InstructionFactory_H_

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
class DiscoveredDetails;
class WorkContext;

namespace Helper {

/*************************************************************************/
/** The InstructionFactory class.
 *
 */
class InstructionFactory {
public:

	virtual ~InstructionFactory() throw();

	InstructionFactory(DiscoveredDetails*   pDiscoveredDetails);

	
	 ASM::ItemList::iterator create(ASM::ItemList::iterator it, 
	 												ASM::ARM::ARM64::Spec::EncodingId iEncodingId);

 	 ASM::ItemList::iterator createJump(ASM::ItemList::iterator it, 
	 								    ASM::ARM::ARM64::Spec::EncodingId iEncodingId,
										ASM::ItemList::iterator itReference);

protected:
	DiscoveredDetails*   pDiscoveredDetails;
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_InstructionFactory_H_ */
