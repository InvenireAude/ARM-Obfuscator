/*
 * File: Disassembler.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_Helper_Disassembler_H_
#define _ARMOB_Helper_Disassembler_H_

#include <tools/common.h>


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
/** The Disassembler class.
 *
 */
class Disassembler {
public:

	virtual ~Disassembler() throw();

	Disassembler(DiscoveredSymbols*   pDiscoveredSymbols);

	void print(const std::string& strName, std::ostream& os);

protected:

	DiscoveredSymbols*   pDiscoveredSymbols;
};

/*************************************************************************/
}
}

#endif /* _ARMOB_Helper_Disassembler_H_ */
