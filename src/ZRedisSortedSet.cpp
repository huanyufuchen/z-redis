
#include "ZRedisSortedSet.h"



RedisStatus ZRedisSortedSet::Zadd(std::string key, std::map <int64_t, std::string> members) {

    std::stringstream ss;
    ss << "ZADD " << key << " ";
    for(auto it = members.begin();it != members.end();it++)
    {
        ss << it->first << " " <<it->second << " ";
    }
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisSortedSet::Zadd(std::string key, int64_t score, std::string val) {
    std::stringstream ss;
    ss << "ZADD " << key << " " << score << " " << val;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}


RedisStatus ZRedisSortedSet::Zcard(std::string key,int& val) {
    std::stringstream ss;
    ss << "ZCARD " << key;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        val = res.inter;
    }
    return s;
}



RedisStatus ZRedisSortedSet::Zrem(std::string key,std::string member) {
    std::stringstream ss;
    ss << "ZREM " << key << member;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisSortedSet::ZremRangekByRank(std::string key, int64_t start, int64_t stop, int &len) {
    std::stringstream ss;
    ss << "ZREMRANGEBYRANK " << key << " " << start << " " << stop;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        len = res.inter;
    }
    return s;
}


RedisStatus ZRedisSortedSet::Zrange(std::string key, int64_t start, int64_t stop, std::vector<std::string> &values) {
    std::stringstream ss;
    ss << "ZRANGE " << key << " " << start << " " << stop;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        for (size_t i = 0; i < res.vecdata.size(); ++i) {
            values.push_back(res.vecdata[i]);
        }
    }
    return s;
}

RedisStatus ZRedisSortedSet::ZrevRange(std::string key, int64_t start, int64_t stop, std::vector<std::string> &values) {
    std::stringstream ss;
    ss << "ZREVRANGE " << key << " " << start << " " << stop;
    std::string cmd = ss.str();
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    if(s == M_REDIS_OK)
    {
        for (size_t i = 0; i < res.vecdata.size(); ++i) {
            values.push_back(res.vecdata[i]);
        }
    }
    return s;
}


