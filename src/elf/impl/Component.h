/*
 * File: Component.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ELF_Impl_Component_H_
#define _ELF_Impl_Component_H_

#include <tools/common.h>

namespace ELF {

namespace Utils {
	class Converter;
};

class Content;

namespace Impl {

/*************************************************************************/
/** The Component class.
 *
 */
class Component {
public:

	virtual ~Component() throw();
	Component(ELF::Content       *pContent);

	inline const ELF::Content* getContent()const{
		return pContent;
	}

	inline ELF::Content* getContent(){
		return pContent;
	}

	inline const Utils::Converter* getConverter()const{
		return pConverter;
	}

protected:

	ELF::Content           *pContent;
	const Utils::Converter *pConverter;

};

/*************************************************************************/
}
}

#endif /* _ELF_Impl_Component_H_ */
