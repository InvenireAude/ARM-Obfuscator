/*
 * File: Builder.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_Builder_H_
#define _ARMOB_Helper_Builder_H_

#include <tools/common.h>

#include <elf/elf.h>


namespace ELF {
	class Artefact;
	class Expander;
}

namespace ASM{
	class GenericInstruction;
}

namespace ARMOB {
class WorkContext;
class DiscoveredSymbols;
class Symbol;

namespace Helper {

/*************************************************************************/
}
}
namespace ARMOB {
namespace Helper {

/*************************************************************************/
/** The Builder class.
 *
 */
class Builder {
public:

	virtual ~Builder() throw();

	Builder(WorkContext* pWorkContext);

	void syncSize(Symbol* pSymbol);

	void build();

protected:

	WorkContext         *pWorkContext;
	DiscoveredSymbols   *pDiscoveredSymbols;
	ELF::Elf64::Header  *pHeader;
	std::unique_ptr<ELF::Expander> ptrExpander;

	size_t recomputeAddresses(const std::string& strSectionName);
	void   updateReferences(const std::string& strSectionName);

	void   write(const std::string& strSectionName);

	void syncAddresses();
	void syncAddresses(ELF::Elf64::SymbolTable *pSymbolTable);
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_Builder_H_ */
