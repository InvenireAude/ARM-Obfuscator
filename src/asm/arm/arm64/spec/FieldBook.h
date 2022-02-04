/*
 * File: FieldBook.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ARM_ARM64_Spec_FieldBook_H_
#define _ASM_ARM_ARM64_Spec_FieldBook_H_

#include "enums.h"

#include <list>
#include <vector>
#include <unordered_map>
#include <string>

#include "Field.h"

namespace ASM {
namespace ARM {
namespace ARM64 {
namespace Spec {

/*************************************************************************/
/** The FieldBook class.
 *
 */
class FieldBook {
public:

	virtual ~FieldBook() throw();
	FieldBook();

	const char* getName(FieldId iFieldId)const;
	const FieldId getId(const std::string& strName)const;

	static const FieldBook TheInstance;

protected:

	typedef std::unordered_map< FieldId , const char*>   NameByIdMap;
	static const NameByIdMap                             TheNameById;

	typedef std::unordered_map< std::string, FieldId >   IdByNameMap;
	IdByNameMap                                          hmIdByName;
};

/*************************************************************************/
}
}
}
}

#endif /* _ASM_ARM_ARM64_Spec_FieldBook_H_ */
