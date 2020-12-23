#pragma once


#include "ZRedisBase.h"


class ZRedisTransactions :public ZRedisBase {
public:

    ZRedisTransactions();
    ~ZRedisTransactions();
    RedisStatus Multi();

    RedisStatus Exec();


public:
    static std::shared_ptr<ZRedisConnection> conn;
    static bool start_transactions;
private:

};

