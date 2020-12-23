#include <ZRedisConnectionPool.h>
#include "ZRedisTransactions.h"

std::shared_ptr<ZRedisConnection> ZRedisTransactions::conn = nullptr;
bool ZRedisTransactions::start_transactions = false;
RedisStatus ZRedisTransactions::Multi() {
    std::string cmd = "MULTI";
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

RedisStatus ZRedisTransactions::Exec() {
    std::string cmd = "EXEC";
    RedisResult res;
    RedisStatus s = ZRedisConnection::ExecCmd(cmd.c_str(),res);
    return s;
}

ZRedisTransactions::ZRedisTransactions() {
    conn = ZRedisConnectionPool::Get();
}

ZRedisTransactions::~ZRedisTransactions(){
    ZRedisConnectionPool::Back(conn);
}

