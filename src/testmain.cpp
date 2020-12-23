#include "ZRedisConnection.h"
#include "ZRedisKey.h"
#include "ZRedisList.h"
#include "ZRedisString.h"
#include "ZRedis.h"
#include "../../commonutil/include/common_funcs.h"
#include <iostream>
#include <string>
#include <string.h>
#include <ZRedisConnectionPool.h>

struct calc_struct
{
    int index = 0;
    char vin[40];
    float aa = 0.0;
};
struct re_data
{
    calc_struct data[20];
    int len = 1;
};
int main()
{

    RedisConfig redis_conf;
    GetRedisConfig(redis_conf);
//    DLOG(INFO) << "redis info : ip" << redis_conf.redis_ip << " port:" << redis_conf.redis_port << " pwd:" << redis_conf.redis_pwd;
    ZRedisConnectionPool::init(redis_conf.redis_ip,redis_conf.redis_port,redis_conf.redis_pwd,3);
    std::shared_ptr<ZRedisConnection> con = ZRedisConnectionPool::Get();
    RedisResult res;
    RedisStatus status = con->ExecCmd("keys *",res);
    ZRedisConnectionPool::Back(con);
    ZRedisString zstr;
    for (int i = 0; i < 20; ++i) {
        zstr.Set("ceshi",i);
    }


    return 0;
}