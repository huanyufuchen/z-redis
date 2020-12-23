#pragma once
#include "ZRedisConnection.h"
#include "ZRedisBase.h"


template <typename T>
std::string setcmd(std::string key,T value)
{

    std::stringstream ss;
    ss << "SET " << key << " " << value;
    std::string cmd = ss.str();
    return cmd;
}

class ZRedisString : public ZRedisBase
{
public:
//    ZRedisString(ZRedisConnection *con) = delete;
    ZRedisString() = default;
    ~ZRedisString() = default;

    RedisStatus Set(std::string key,int value);
    RedisStatus Set(std::string key,int64_t value);
    RedisStatus Set(std::string key,double value);
    RedisStatus Set(std::string key, std::string value);
    RedisStatus Set(std::string key, float value);
    RedisStatus Set(std::string key, bool value);
    RedisStatus Set(std::string key, void* value,size_t valen_len);

    RedisStatus Incr(std::string key, int64_t &value);


    RedisStatus Get(std::string key,std::string &value);
    RedisStatus Get(std::string key,void *value);
    RedisStatus Get(std::string key,std::shared_ptr<unsigned char> &value);

private:
    /* data */
};

