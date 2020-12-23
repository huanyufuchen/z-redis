//
// Created by Administrator on 2020/4/10.
//
#pragma once

#include <map>
#include "ZRedisConnection.h"
#include "ZRedisBase.h"

class ZRedisSortedSet : public ZRedisBase
{
public:
    ZRedisSortedSet() = default;
    ~ZRedisSortedSet() = default;

    RedisStatus Zadd(std::string key,std::map<int64_t,std::string> members);
    RedisStatus Zadd(std::string key,int64_t score,std::string val);

    RedisStatus Zrange(std::string key, int64_t start, int64_t stop, std::vector<std::string> &values);

    RedisStatus ZrevRange(std::string key, int64_t start, int64_t stop, std::vector<std::string> &values);

    RedisStatus Zcard(std::string key,int& val);

    RedisStatus ZremRangekByRank(std::string key, int64_t start, int64_t stop, int &len);

    RedisStatus Zrem(std::string key,std::string member);
private:
    /* data */
};

