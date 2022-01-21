/*
 * File: Exception.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _Tools_Exception_H_
#define _Tools_Exception_H_

#include <iostream>
#include <sstream>
#include <string>

namespace Tools {

/*************************************************************************/
/** The Exception class.
 *
 */
class Exception {
public:

	virtual ~Exception() throw();
	Exception();

	inline Exception(const Exception& e):
		ssInfo(e.ssInfo.str()){};

	Exception& operator<<(const char* s){
		ssInfo<<s;
		return *this;
	}

	Exception& operator<<(const std::string& s){
		ssInfo<<s;
		return *this;
	}

	Exception& operator<<(int i){
		ssInfo<<i;
		return *this;
	}

	Exception& operator<<(void* p){
		ssInfo<<p;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Exception& e){
		os<<e.ssInfo.str();
		return os;
	}

protected:

	std::stringstream ssInfo;
};

/*************************************************************************/
}

#endif /* _Tools_Exception_H_ */
