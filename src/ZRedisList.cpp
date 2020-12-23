#include "ZRedisList.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>


RedisStatus ZRedisList::Llen(const std::string key,int &len)
{
    std::stringstream ss;
    ss << "LLEN " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    len = res.inter;
    return s;
}

RedisStatus ZRedisList::Lpush(const std::string key,std::vector<std::string> &list,int &listlen)
{
    std::stringstream ss;
    ss << "LPUSH " << key << " ";
    for (int i = 0; i < list.size(); i++)
    {
        ss << list.at(i) << " ";
    }
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    listlen = res.inter;
    return s;
}


RedisStatus ZRedisList::Lpush(const std::string key,const std::string &value,int &listlen)
{
    std::stringstream ss;
    ss << "LPUSH " << key << " " << value;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    listlen = res.inter;
    return s;
}



RedisStatus ZRedisList::LpushX(const std::string key,std::vector<std::string> &list,int &listlen)
{
    std::stringstream ss;
    ss << "LPUSHX " << key << " ";
    for (int i = 0; i < list.size(); i++)
    {
        ss << list.at(i) << " ";
    }
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK) {
        listlen = res.inter;
    }
    return s;
}



RedisStatus ZRedisList::LpushX(const std::string key,const std::string &value,int &listlen)
{
    std::stringstream ss;
    ss << "LPUSHX " << key << " " << value;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK) {
        listlen = res.inter;
    }
    return s;
}

RedisStatus ZRedisList::Rpop(const std::string key)
{
    std::stringstream ss;
    ss << "RPOP " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisList::Ltrim(const std::string key,int start,int end)
{
    std::stringstream ss;
    ss << "LTRIM " << key << " " << start << " " << end;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}






RedisStatus ZRedisList::Lpop(const std::string key,std::string &result)
{
    std::stringstream ss;
    ss << "LPOP " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK) {
        result = res.strdata;
    }
    return s;
}


RedisStatus ZRedisList::Lpop(const std::string key)
{
    std::stringstream ss;
    ss << "LPOP " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisList::Lrange(const std::string key,int start,int end,std::vector<std::string> &result)
{
    std::stringstream ss;
    ss << "LRANGE " << key << " "<< start << " " << end;
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