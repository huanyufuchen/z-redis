#include "ZRedisString.h"
#include <sstream>

RedisStatus ZRedisString::Set(std::string key,int value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisString::Set(std::string key,int64_t value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisString::Set(std::string key,double value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisString::Set(std::string key,float value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisString::Set(std::string key,std::string value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisString::Set(std::string key,bool value){
    std::string cmd = setcmd(key,value);
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisString::Set(std::string key, void* value,size_t valen_len)
{
    std::stringstream ss;
    ss << "SET " << key << " %b";
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        valen_len = res.inter;
    }

}

RedisStatus ZRedisString::Get(std::string key,std::string &value)
{
    std::stringstream ss;
    ss << "GET " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    value = res.strdata;
    return s;
}

RedisStatus ZRedisString::Get(std::string key,void *value)
{
    std::stringstream ss;
    ss << "GET " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    value = (void *) res.strdata.data();
    return s;
}


//RedisStatus ZRedisString::Get(std::string key,std::shared_ptr<unsigned char> &value)
//{
//    std::stringstream ss;
//    ss << "GET " << key;
//    std::string cmd = ss.str();
////    con->pm_rr = (redisReply*)redisCommand(con->pm_rct, cmd.c_str());
//
//    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
////    return con->HandleReplayString(value,M_BINARY);
//}

RedisStatus  ZRedisString::Incr(std::string key, int64_t &value)
{
     std::stringstream ss;
    ss << "INCR " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    value = res.inter;
    return s;
}