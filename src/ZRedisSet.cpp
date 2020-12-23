#include "ZRedisSet.h"
#include <iostream>
#include <sstream>

RedisStatus ZRedisSet::Sadd(std::string key,std::vector<std::string> member)
{
    std::stringstream ss;
    ss << "SADD " << key << " ";
    std::vector<std::string>::iterator it = member.begin();
    for(it;it != member.end();it++)
    {
        ss << *it << " ";
    }
    std::string cmd = ss.str();
//    con->pm_rr = (redisReply*)redisCommand(con->pm_rct, cmd.c_str());
//    int status;
    RedisResult res;
//    RedisStatus s = con->ParseReplay(res);
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisSet::Sadd(std::string key,std::string member)
{
    std::stringstream ss;
    ss << "SADD " << key << " " << member;
    std::string cmd = ss.str();
//    con->pm_rr = (redisReply*)redisCommand(con->pm_rct, cmd.c_str());

    RedisResult res;
//    RedisStatus s = con->ParseReplay(res);
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisSet::SisMember(std::string key,std::string value,int &exists)
{
    std::stringstream ss;
    ss << "SISMEMBER " << key << " " << value;
    std::string cmd = ss.str();
//    con->pm_rr = (redisReply*)redisCommand(con->pm_rct, cmd.c_str());

    RedisResult res;
//    RedisStatus s = con->ParseReplay(res);
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        exists = res.inter;
    }
    return s;
}



RedisStatus ZRedisSet::Smembers(std::string key,std::vector<std::string> &result)
{
    std::stringstream ss;
    ss << "SMEMBERS " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);

    if(s == M_REDIS_OK)
    {
        for (int i = 0; i < res.vecdata.size(); ++i) {
            result.push_back(res.vecdata[i]);
        }
    }
    return s;
}

RedisStatus ZRedisSet::Spop(std::string key, std::vector<std::string> &values, int count) {
    std::stringstream ss;
    if(count>0){
        ss << "SPOP " << key << " " << count;
    }else{
        ss << "SPOP " << key;
    }

    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        for (int i = 0; i < res.vecdata.size(); ++i) {
            values.push_back(res.vecdata[i]);
        }
    }
    return s;
}




RedisStatus ZRedisSet::Srem(std::string key, std::string value) {
    std::stringstream ss;
    ss << "SREM " << key << " " << value;

    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}
