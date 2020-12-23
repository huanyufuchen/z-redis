#pragma once
#include "ZRedisConnection.h"
#include <sstream>
#include <initializer_list>



class ZRedisBase
{
public:
    ZRedisBase();
    ~ZRedisBase();

    virtual std::string GetErr();

    static void SetError(std::string error);

private:
    static std::string err_msg_;
};
