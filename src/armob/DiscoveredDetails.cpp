/*
 * File: DiscoveredDetails.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "DiscoveredDetails.h"
#include "WorkContext.h"

namespace ARMOB {

/*************************************************************************/
DiscoveredDetails::DiscoveredDetails(WorkContext* pWorkContext):
	pWorkContext(pWorkContext){
}

/*************************************************************************/
DiscoveredDetails::~DiscoveredDetails() throw(){
}
/*************************************************************************/
ASM::ItemList::iterator DiscoveredDetails::appendNewInstruction(const uint8_t *pOpCode, uint8_t  iLength, uint64_t iOpCodeAddress){
	return lstInstructions.append(pWorkContext->getGenericDetailFactory()->create(pOpCode, iLength, iOpCodeAddress));
}
/*************************************************************************/
}
