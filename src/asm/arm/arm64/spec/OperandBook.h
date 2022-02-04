/*
 * File: OperandBook.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_OperandBook_H_
#define _ASM_ARM_ARM64_Spec_OperandBook_H_

#include "enums.h"

#include <unordered_map>

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The OperandBook class.
 *
 */
class OperandBook {
public:

	virtual ~OperandBook() throw();
	OperandBook();

    const char* getSpec(OperandId iOperandId)const;

    static OperandBook TheInstance;

protected:

	typedef std::unordered_map< OperandId , const char*>   SpecByIdMap;
	static const SpecByIdMap                               TheSpecById;

};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_OperandBook_H_ */
