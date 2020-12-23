#include "ZRedisKey.h"
#include <sstream>
#include <iostream>

RedisStatus ZRedisKey::KeyExists(const std::string key,int &exists)
{
    std::string cmd = "EXISTS " + key;
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        exists = res.inter;
    }
    return s;
}


RedisStatus ZRedisKey::DelKey(const std::string key)
{
    std::string cmd = "DEL " + key;
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisKey::ExpireKey(const std::string key,int time)
{
    std::stringstream ss;
    ss << "EXPIRE " << key << " " << time;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisKey::PttlKey(const std::string key)
{
    std::stringstream ss;
    ss << "PTTL  " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;

}

RedisStatus ZRedisKey::Keys(const std::string pattern_key,std::vector<std::string> result) {
    std::stringstream ss;
    ss << "KEYS  " << pattern_key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        for (int i = 0; i < res.vecdata.size(); ++i) {
            result.push_back(res.vecdata.at(i));
        }
    }
    return s;
}
