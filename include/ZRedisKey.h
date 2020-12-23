#pragma once
#include "ZRedisConnection.h"
#include "ZRedisBase.h"

class ZRedisKey : public ZRedisBase
{
public:
    ZRedisKey() = default;
    ~ZRedisKey() = default;

    RedisStatus KeyExists(const std::string key,int &exists);

    RedisStatus DelKey(const std::string key);

    RedisStatus ExpireKey(const std::string key,int time);

    RedisStatus PttlKey(const std::string key);

    RedisStatus Keys(const std::string pattern_key,std::vector<std::string> result);

private:
};


