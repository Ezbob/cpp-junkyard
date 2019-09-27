
#ifndef _HEADER_FILE_Resource_20190927215326_
#define _HEADER_FILE_Resource_20190927215326_

#include "DataSignals.hpp"

struct Resource : public DataSignals<Resource> {

    int stuff;
    float blah;

    virtual void get() = 0;
};

#endif