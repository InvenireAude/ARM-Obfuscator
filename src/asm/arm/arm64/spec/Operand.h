/*
 * File: Operand.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_Operand_H_
#define _ASM_ARM_ARM64_Spec_Operand_H_

#include "enums.h"

#include <unordered_map>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The Operand class.
 *
 */
class Operand {
public:

	virtual ~Operand() throw();
	Operand();

    const char* getSpec(OperandId iOperandId)const;

    static Operand TheInstance;

protected:

	typedef std::unordered_map< OperandId , const char*>   SpecByIdMap;
	static const SpecByIdMap                               TheSpecById;

};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_Operand_H_ */
