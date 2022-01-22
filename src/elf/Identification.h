/*
 * File: Identification.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Identification_H_
#define _ELF_Identification_H_

#include <tools/common.h>
#include "Specification.h"

namespace ELF {

class Content;

/*************************************************************************/
/** The Identification class.
 *
 */
class Identification {
public:

	virtual ~Identification() throw();
	Identification(const Content* pContent);

	Class   getClass()const;
	Data    getDataEncoding()const;
	Version getVersion()const;
	OSABI   getOSABI()const;
	

protected:

	uint8_t _d[EI_NIDENT];
};
/*************************************************************************/
}

#endif /* _ELF_Identification_H_ */
