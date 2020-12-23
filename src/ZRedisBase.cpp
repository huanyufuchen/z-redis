#include "ZRedisBase.h"

std::string ZRedisBase::err_msg_;
ZRedisBase::ZRedisBase()
{
}

ZRedisBase::~ZRedisBase()
{
}


std::string ZRedisBase::GetErr(){
    return err_msg_;
}

void ZRedisBase::SetError(std::string error) {
    err_msg_ = error;
}

