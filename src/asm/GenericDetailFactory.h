/*
 * File: GenericDetailFactory.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */

#ifndef _ASM_GenericDetailFactory_H_
#define _ASM_GenericDetailFactory_H_

#include <tools/common.h>
#include "GenericDetail.h"
#include "Item.h"

namespace ASM
{

	/*************************************************************************/
	/** The GenericDetailFactory class.
	 *
	 */
	class GenericDetailFactory
	{
	public:
		virtual ~GenericDetailFactory() throw();
		GenericDetailFactory(size_t iSize = 100000);

		GenericDetail *allocateGenericDetail();
		Item *allocateItem();

		template<class... Args>
			Item* create(Args... args){
				return new(allocateItem())Item(new (allocateGenericDetail())GenericDetail(args...));
			}

	protected:
		
		std::unique_ptr<GenericDetail> ptrPool;
		size_t iSize;
		size_t iFirstFree;

		std::unique_ptr<Item> ptrItemPool;
		size_t iItemFirstFree;
	};

	/*************************************************************************/
} // namespace ASM

#endif /* _ASM_GenericDetailFactory_H_ */
