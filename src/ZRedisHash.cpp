#include "ZRedisHash.h"
#include <iostream>
#include <sstream>

RedisStatus ZRedisHash::Hmset(std::string key,std::map<std::string,std::string> value)
{
    std::stringstream ss;
    ss << "HMSET " << key << " ";
    std::map<std::string,std::string>::iterator it = value.begin();
    for(it;it != value.end();it++)
    {
        ss << it->first << " " << it->second << " ";
    }
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}
RedisStatus ZRedisHash::Hmget(std::string key,std::map<std::string,std::string> &result)
{

    std::stringstream ss;
    ss << "HMGET " << key << " ";
    std::map<std::string,std::string>::iterator it = result.begin();
    for(it;it != result.end();it++)
    {
        ss << it->first << " ";
    }
    std::string cmd = ss.str();

    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        int index = 0;
        it = result.begin();
        for(it;it != result.end();it++)
        {
            result.insert({it->first,std::string(res.vecdata[index])});
            index++;
        }
    }
    return s;
}


RedisStatus ZRedisHash::Hset(std::string key, std::string field, std::string value) {
    std::stringstream ss;
    ss << "HSET " << key << " " << field << " " <<value;

    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisHash::Hmget(std::string key,std::vector<std::string> fields,std::map<std::string,std::string> &result)
{
    std::stringstream ss;
    ss << "HMGET " << key << " ";
    std::vector<std::string>::iterator it = fields.begin();
    for(it;it != fields.end();it++)
    {
        ss << *it << " ";
    }
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        if(res.type == redis_reply_array)
        {
            int index = 0;
            it = fields.begin();
            for(it;it != fields.end();it++)
            {
                result.insert({*it,std::string(res.vecdata[index])});
                index++;
            }
        }
    }
    return s;
}


RedisStatus ZRedisHash::Hget(std::string key,std::string field,std::string &value)
{
    std::stringstream ss;
    ss << "HGET " << key << " " << field;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        value = res.strdata;
    }
    return s;
}


RedisStatus ZRedisHash::Hexist(std::string key,std::string field,int &status)
{
    std::stringstream ss;
    ss << "HEXISTS  " << key << " " << field;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        status = res.inter;
    }
    return s;
}

RedisStatus ZRedisHash::Hdel(std::string key, std::string field, int &status) {
    std::stringstream ss;
    ss << "HDEL  " << key << " " << field;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        status = res.inter;
    }
    return s;
}
