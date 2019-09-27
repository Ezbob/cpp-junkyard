
#ifndef _HEADER_FILE_ResourceFetcher_20190927215629_
#define _HEADER_FILE_ResourceFetcher_20190927215629_

#include "Resource.hpp"

class ResourceFetcher : public Resource {

public:
    void get() override;
};

#endif