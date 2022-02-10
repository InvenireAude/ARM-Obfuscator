/*
 * File: ArtefactCopy.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_ArtefactCopy_H_
#define _ELF_ArtefactCopy_H_

#include <tools/common.h>

#include "Artefact.h"

namespace ELF {

/*************************************************************************/
/** The ArtefactCopy class.
 *
 */

class ContentMemory;

class ArtefactCopy : public Artefact {
public:

	virtual ~ArtefactCopy() throw();
	ArtefactCopy(const Artefact* pArtefact);


protected:
	
	virtual Content* getContent()const;

	std::unique_ptr<ContentMemory>   ptrContentMemory;
};

/*************************************************************************/
}

#endif /* _ELF_ArtefactCopy_H_ */
