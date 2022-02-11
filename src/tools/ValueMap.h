/*
 * File: ValueMap.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _tools_ValueMap_H_
#define _tools_ValueMap_H_

#include <string>
#include <unordered_map>

#include "Exception.h"

namespace Tools {

/*************************************************************************/
/** The ValueMap class.
 *
 */
class ValueMap {
public:

	virtual ~ValueMap() throw();
	
	ValueMap(const std::string& strName, const std::initializer_list< std::pair<int, std::string> >& values);

	const std::string& getString(int iValue)const{
		ValuesHashMap::const_iterator it = hmValues.find(iValue);

		if(it == hmValues.end()){
			throw Tools::Exception()<<"Value not found ["<<strName<<"]: "<<iValue<<"["<<(void*)(long)iValue<<"]";
		}

		return it->second;
	}

protected:

	std::string strName;

	typedef std::unordered_map<int, std::string> ValuesHashMap;
	
	ValuesHashMap hmValues;

};

/*************************************************************************/
}

#endif /* _tools_ValueMap_H_ */
