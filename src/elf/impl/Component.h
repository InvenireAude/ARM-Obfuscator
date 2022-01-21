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

class Image;

namespace Impl {

/*************************************************************************/
/** The Component class.
 *
 */
class Component {
public:

	virtual ~Component() throw();
	Component(const ELF::Image       *pImage);

	const ELF::Image* getImage()const{
		return pImage;
	}

	const Utils::Converter* getConverter()const{
		return pConverter;
	}

protected:

	const ELF::Image       *pImage;
	const Utils::Converter *pConverter;

};

/*************************************************************************/
}
}

#endif /* _ELF_Impl_Component_H_ */
