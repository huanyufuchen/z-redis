#pragma once
#include <map>
#include <vector>
#include "ZRedisBase.h"

class ZRedisHash :public ZRedisBase
{
public:
    ZRedisHash() = default;
    ~ZRedisHash() = default;

    RedisStatus Hmset(std::string key,std::map<std::string,std::string> value);

    RedisStatus Hset(std::string key,std::string field,std::string value);

    RedisStatus Hmget(std::string key,std::vector<std::string> fields,std::map<std::string,std::string> &result);

    RedisStatus Hmget(std::string key,std::map<std::string,std::string> &result);

    RedisStatus Hget(std::string key,std::string field,std::string &value);

    RedisStatus Hexist(std::string key,std::string field,int &status);

    RedisStatus Hdel(std::string key,std::string field,int &status);


private:
    /* data */
};