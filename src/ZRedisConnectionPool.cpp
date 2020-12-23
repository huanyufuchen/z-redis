
#include <iostream>
#include "ZRedisConnectionPool.h"
#include <glog/logging.h>
std::vector<std::shared_ptr<ZRedisConnection>> ZRedisConnectionPool::connect_pool_;
std::mutex ZRedisConnectionPool::mtx_;
bool ZRedisConnectionPool::init(std::string ip, int port, std::string pwd,int db, int pool_size) {
    bool flag = true;
    if(pool_size <= 0)
    {
        flag = false;
    }
    mtx_.lock();
    for (int i = 0; i < pool_size; ++i) {
        ZRedisConnection* con = new ZRedisConnection();
        if(con->Connect(ip,port,pwd,db))
        {
            connect_pool_.push_back(std::shared_ptr<ZRedisConnection>(con));
        }else{
            LOG(ERROR) << "connect redirs :" <<ip << ":" << port << pwd << "failed";
        }
    }
    int real_pool_size = connect_pool_.size();
    mtx_.unlock();
    if(pool_size > real_pool_size)
    {
        LOG(ERROR) << "redis pool init failed! hope pool size:" << pool_size << "real size is " << real_pool_size;
        flag = false;
    }else{
        LOG(INFO) << "redis pool init success! pool size:" << real_pool_size;
    }

    return flag;
}


std::shared_ptr<ZRedisConnection> ZRedisConnectionPool::Get() {

    mtx_.lock();
    if(connect_pool_.size() == 0)
    {
        throw "Zzredis pool is empty";
    }

    std::shared_ptr<ZRedisConnection> tmp = connect_pool_.front();
    connect_pool_.erase(connect_pool_.begin());
    mtx_.unlock();
    return tmp;
}

void ZRedisConnectionPool::Back(std::shared_ptr<ZRedisConnection> &con) {
    mtx_.lock();
    connect_pool_.push_back(con);
    mtx_.unlock();
}

int ZRedisConnectionPool::size() {

    mtx_.lock();
    int size = connect_pool_.size();
    mtx_.unlock();
    return size;
}
