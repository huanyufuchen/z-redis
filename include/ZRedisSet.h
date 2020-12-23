#pragma once
#include <map>
#include <vector>
#include "ZRedisBase.h"

class ZRedisSet :public ZRedisBase
{
public:
    ZRedisSet() = default;
    ~ZRedisSet() = default;

    RedisStatus Sadd(std::string key,std::vector<std::string> members);

    RedisStatus Sadd(std::string key,std::string member);

    RedisStatus SisMember(std::string key,std::string value,int &exists);

    RedisStatus Spop(std::string key,std::vector<std::string> &valus, int count=0);

    RedisStatus Spop(std::string key, char* value);

    RedisStatus Srandmember(std::string key, char* value);

    RedisStatus Srem(std::string key,std::string value);

    RedisStatus Smembers(std::string key, std::vector<std::string> &result);

private:
    /* data */
};