/*
 * File: DiscoveredDetails.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ARMOB_DiscoveredDetails_H_
#define _ARMOB_DiscoveredDetails_H_

#include <tools/common.h>

#include "Symbol.h"
#include <asm/GenericDetailFactory.h>
#include <asm/GenericDetail.h>
#include <asm/Item.h>
#include <asm/ItemList.h>

namespace ARMOB {

class WorkContext;

/*************************************************************************/
/** The DiscoveredDetails class.
 *
 */
class DiscoveredDetails {
public:

	virtual ~DiscoveredDetails() throw();
	DiscoveredDetails(WorkContext* pWorkContext);

  	ASM::ItemList::iterator appendNewInstruction(const uint8_t *pOpCode, 
	  											 uint8_t  iLength, 
	  											 uint64_t iOpCodeAddress);

	ASM::ItemList& getInstructions(){
		return lstInstructions;
	}

	inline WorkContext* getWorkContext()const{
		return pWorkContext;
	}

protected:

	WorkContext   *pWorkContext;
	ASM::ItemList lstInstructions;
};

/*************************************************************************/
}

#endif /* _ARMOB_DiscoveredDetails_H_ */
