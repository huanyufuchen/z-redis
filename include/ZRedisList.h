#pragma once
#include "ZRedisBase.h"
#include "ZRedisConnection.h"
#include <vector>
#include <string>

class ZRedisList : public ZRedisBase
{
public:
    ZRedisList() = default;
    ~ZRedisList() = default;

    RedisStatus Llen(const std::string key,int &len);


    //insert list header
    RedisStatus Lpush(const std::string key,std::vector<std::string> &list,int &listlen);

    RedisStatus Lpush(const std::string key,const std::string &value,int &listlen);

    //inert list end
    RedisStatus LpushX(const std::string key,std::vector<std::string> &list,int &listlen);


    RedisStatus LpushX(const std::string key,const std::string &value,int &listlen);

    RedisStatus Rpop(const std::string key);

    RedisStatus Ltrim(const std::string key,int start,int end);


    //命令用于移除并返回列表的第一个元素。
    RedisStatus Lpop(const std::string key,std::string &result);
    RedisStatus Lpop(const std::string key);



    //返回列表中指定区间内的元素
    RedisStatus Lrange(const std::string key,int start,int end,std::vector<std::string> &result);


private:
};
