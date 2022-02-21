/*
 * File: WorkContext.cpp
 *
 * Copyright (C) 2021, Albert Krzymowski
 *
 */

#include "WorkContext.h"

#include "DiscoveredDetails.h"
#include "DiscoveredSymbols.h"

namespace ARMOB {

const std::string& WorkContext::CTextSection(".text");
const std::string& WorkContext::CPltSection(".plt");

/*************************************************************************/
WorkContext::WorkContext(const ELF::Artefact* pArtefact):
	ptrGenericDetailFactory(new ASM::GenericDetailFactory()),
	ptrDiscoveredSymbols(new DiscoveredSymbols()),
	ptrArtefactCopy(new ELF::ArtefactCopy(pArtefact)){
}
/*************************************************************************/
WorkContext::~WorkContext() throw(){
}
/*************************************************************************/
DiscoveredDetails* WorkContext::getDetails(const std::string& strSectionName){

	DetailsMap::iterator it = hmDetails.find(strSectionName);

	if(it == hmDetails.end()){
		std::unique_ptr<DiscoveredDetails>& ptrResult(hmDetails[strSectionName]);
		ptrResult.reset(new DiscoveredDetails(this));
		return ptrResult.get();
	}

	return it->second.get();
}
/*************************************************************************/
DiscoveredSymbols* WorkContext::getSymbols()const{
	return ptrDiscoveredSymbols.get();
}	
/*************************************************************************/
void WorkContext::save(const std::string& strFileName)const{

	ptrArtefactCopy->save(strFileName);    
}
/*************************************************************************/
}
