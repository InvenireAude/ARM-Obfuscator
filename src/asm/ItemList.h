/*
 * File: ItemList.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _ASM_ItemList_H_
#define _ASM_ItemList_H_

#include <tools/common.h>
#include "Item.h"

namespace ASM {

/*************************************************************************/
/** The ItemList class.
 *
 */
class ItemList {
public:

	ItemList():
		pHead(nullptr){};

	inline Item* getHead(){
		if(!pHead){
			Tools::Exception()<<"Item is empty !!!";
		}
		return pHead;
	}

	inline const Item* getHead()const{
		return pHead;
	}

	inline Item* getTail(){
		return pTail;
	}

	inline const Item* getTail()const{
		return pTail;
	}

	class iterator {
		public:

		inline Item* operator->(){
			 if(!pCursor){
				 throw Tools::Exception()<<"Referenced a null operator";
			 }
			 return pCursor;
		 }

		inline Item& operator*(){
			 if(!pCursor){
				 throw Tools::Exception()<<"Referenced a null operator";
			 }
			 return *pCursor;
		 }

		 inline bool operator!()const{
			 return !pCursor;
		 }

		inline operator bool()const{
			 return pCursor != nullptr;
		 }

		 inline bool operator==(const iterator& other)const{
			 return pCursor == other.pCursor;
		 }

		 inline bool operator!=(const iterator& other)const{
			 return pCursor != other.pCursor;
		 }

		inline iterator& operator++(){
			 if(pCursor != nullptr){
				 pCursor = pCursor->pNext;
			 }
			 return *this;
		 }

		inline iterator operator++(int){
			iterator itOld(pCursor);
			 if(pCursor != nullptr){
				 pCursor = pCursor->pNext;
			 }
			 return itOld;
		 }

		inline iterator& operator--(){
			 if(pCursor != nullptr && pCursor->pPrev != nullptr){
				 pCursor = pCursor->pPrev;
			 }
			return *this;
		 }

		inline iterator& operator=(const iterator& o){
			this->pCursor = o.pCursor;
			return *this;
		}

		inline iterator next()const{
			 if(pCursor != nullptr){
				return pCursor->pNext;
			 }
			 throw Tools::Exception()<<"Referenced a null operator";
		}

		inline iterator(const iterator& o){
			this->pCursor = o.pCursor;
		}

		//TODO temporary quick fix for ARMOB::Symbol constructor.
			iterator(Item* pCursor = nullptr):pCursor(pCursor){};

		protected:

			Item* pCursor;

		friend class ItemList;
	};


	inline iterator begin(){
		return iterator(pHead);
	}

	inline iterator end(){
		return iterator(nullptr);
	}


	inline iterator insertAfter(iterator& it, Item* pNew){
		
		if(!it){
			throw Tools::Exception()<<"insertAfter cannot use an invalid interator";
		}

		if(it.pCursor == pTail){
			pTail = pNew;
			pNew->pNext = nullptr;
		}else{
			it.pCursor->pNext->pPrev = pNew;
			pNew->pNext = it.pCursor->pNext;
		}

		pNew->pPrev = it.pCursor;
		it.pCursor->pNext = pNew;

		return iterator(pNew);
	}

	inline iterator insertAfter(iterator& it, iterator& itStart, iterator& itEnd){
		
		if(!it || (itStart.pCursor == pHead && itEnd.pCursor == pTail)){
			throw Tools::Exception()<<"insertAfter invalid parameters.";
		}

		if(itEnd.pCursor == pTail){
			pTail = itStart->pPrev;
		}else{
			itEnd.pCursor->pNext->pPrev = itStart.pCursor->pPrev;
		}
		
		if(itStart.pCursor == pHead){
			pHead = itEnd->pNext;
		}else{
			itStart.pCursor->pPrev->pNext = itEnd.pCursor->pNext;
		}

		if(it.pCursor == pTail){
			itEnd.pCursor->pNext = nullptr;
			pTail = itEnd.pCursor;
		}else{
			it.pCursor->pNext->pPrev = itEnd.pCursor;
			itEnd.pCursor->pNext = it.pCursor->pNext;
		}

		it.pCursor->pNext = itStart.pCursor;
		itStart.pCursor->pPrev = it.pCursor;
		
		return iterator(itEnd);
	}

	inline iterator append(Item* pNew){

		if(!pHead){
			pHead = pNew;
			pTail = pNew;
		}else{
			pTail->pNext = pNew;
			pNew->pPrev = pTail;
			pNew->pNext = nullptr;
			pTail = pNew;
		}

		return iterator(pNew);
	}

protected:
	Item* pHead;
	Item* pTail;
};
/*************************************************************************/
}

#endif /* _ASM_ItemList_H_ */
