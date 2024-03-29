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
#include <functional>

namespace ASM {

class GenericDetail;

/*************************************************************************/
/** The Item class.
 *
 */
class Item {
public:
	
	enum EncodedTagType : uint8_t {
		ET_None  = 0,
		ET_ARMv8 = 0x01
	};

	Item(GenericDetail *pGenericDetail):
		pGenericDetail(pGenericDetail),
		iTagId(ET_None),
		onUpdateReference(nullptr){}

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


	typedef uint64_t EncodedType;

	template<EncodedTagType iTagId, typename T>
		void setEncoded(T iEncodedValue){
			this->iTagId = iTagId;
			this->iEncodedValue = reinterpret_cast<EncodedType>(iEncodedValue);			
		}

	template<EncodedTagType iTagId, typename T>
		T getEncoded()const{
			if(this->iTagId != iTagId){
				throw Tools::Exception()<<"Inconsisted tags: this->iTagId: "<<(int)this->iTagId<<", got:"<<(int)iTagId<<", this: "<<(void*)this;
			}
			return reinterpret_cast<T>(iEncodedValue);			
		}

	inline bool hasEncoded()const{
		return iTagId != ET_None;
	}

	inline GenericDetail* getGenericDetail(){
		return pGenericDetail;
	}

	inline const GenericDetail* getGenericDetail()const{
		return pGenericDetail;
	}

	void setUpdateReference(std::function<void(Item*)> onUpdateReference){
		this->onUpdateReference = onUpdateReference;
	}

	void callUpdateReference(){
		if(onUpdateReference != nullptr){
			onUpdateReference(this);
		}
	}

protected:

	GenericDetail *pGenericDetail;

	Item* pNext;
	Item* pPrev;

    EncodedTagType  iTagId;
	EncodedType     iEncodedValue;

	std::function<void(Item*)> onUpdateReference;

	friend class ItemList;
};


/*************************************************************************/
}

#endif /* _ASM_Item_H_ */
