#pragma once

#include "ZRedisBase.h"

class ZRedisPipeLine : public ZRedisBase {


public:

    ZRedisPipeLine() = default;
    ~ZRedisPipeLine() = default;


    RedisStatus PipLine(std::vector<std::string> vcmd, std::vector<RedisResult> &vresult);

};