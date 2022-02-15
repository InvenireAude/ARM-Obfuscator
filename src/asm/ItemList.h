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

		 inline bool operator!()const{
			 return !pCursor;
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

		inline iterator(const iterator& o){
			this->pCursor = o.pCursor;
		}

		protected:

			iterator(Item* pCursor):pCursor(pCursor){};
			Item* pCursor;

		friend class ItemList;
	};


	inline iterator begin(){
		return iterator(pHead);
	}

	inline iterator end(){
		return iterator(nullptr);
	}


	inline void insertAfter(iterator& it, Item* pNew){
		
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

	}

	inline void append(Item* pNew){

		if(!pHead){
			pHead = pNew;
			pTail = pNew;
		}else{
			pTail->pNext = pNew;
			pNew->pPrev = pTail;
			pNew->pNext = nullptr;
			pTail = pNew;
		}
	}

protected:
	Item* pHead;
	Item* pTail;
};
/*************************************************************************/
}

#endif /* _ASM_ItemList_H_ */
