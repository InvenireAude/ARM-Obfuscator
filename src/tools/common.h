/*
 * File: common.h
 *
 * Copyright (C) 2021, Albert Krzymowski
 *

 */


#ifndef _tools_common_H_
#define _tools_common_H_

#include <inttypes.h>

#include <string>
#include <iostream>
#include <memory>

#include "Exception.h"
#include "ValueMap.h"

namespace Tools {

template<class C, typename T>
inline typename C::const_iterator LowerBound(const C& c, T v){
    typename C::const_iterator it = c.upper_bound(v);

    if(v != it->first){
        --it;
    }

    return it;
}

}

#endif /* _tools_common_H_ */
