/*
 * File: Item.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_Item_H_
#define _ASM_Item_H_

#include <tools/common.h>
#include <string.h>

namespace ASM {

class GenericDetail;

/*************************************************************************/
/** The Item class.
 *
 */
class Item {
public:

	Item(GenericDetail *pGenericDetail):
		pGenericDetail(pGenericDetail){}

	inline Item* getNext()const{
		return pNext;
	}

	inline Item* getPrev()const{
		return pPrev;
	}

	inline bool isHead()const{
		return !pPrev;
	}

	inline bool isTail()const{
		return !pNext;
	}
	
	enum EncodedType : uint8_t {
		ET_None  = 0,
		ET_ARMv8 = 0x01
	};

	typedef uint8_t  EncodedTagType;

	template<EncodedTagType iTagId, typename T>
		void setEncoded(T iEncodedValue){
			this->iTagId = iTagId;
			this->iEncodedValue = reinterpret_cast<EncodedType>(iEncodedValue);			
		}

	template<EncodedTagType iTagId, typename T>
		T getEncoded()const{
			if(this->iTagId != iTagId){
				throw Tools::Exception()<<"Inconsisted tags: this: "<<(int)this->iTagId<<", got:"<<(int)iTagId;
			}
			return reinterpret_cast<T>(iEncodedValue);			
		}

protected:

	GenericDetail *pGenericDetail;

	Item* pNext;
	Item* pPrev;

    EncodedTagType  iTagId;
	EncodedType     iEncodedValue;

	friend class ItemList;
};


/*************************************************************************/
}

#endif /* _ASM_Item_H_ */
