/*
 * File: ArtefactFromFile.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_ArtefactFromFile_H_
#define _ELF_ArtefactFromFile_H_

#include <tools/common.h>

#include "Artefact.h"

namespace ELF {

/*************************************************************************/
/** The ArtefactFromFile class.
 *
 */

class ContentFile;

class ArtefactFromFile : public Artefact {
public:

	virtual ~ArtefactFromFile() throw();
	ArtefactFromFile(const std::string& strName);

protected:
	
	virtual Content* getContent()const;

	std::unique_ptr<ContentFile>   ptrContentFile;
};

/*************************************************************************/
}

#endif /* _ELF_ArtefactFromFile_H_ */
