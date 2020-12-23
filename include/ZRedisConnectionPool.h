#pragma once

#include <string>
#include <memory>
#include "ZRedisConnection.h"
#include <vector>
#include <queue>
#include <mutex>

class ZRedisConnectionPool {

public:
    /**
     * 初始化连接池
     * @param ip    服务ip
     * @param port  服务端口
     * @param pwd   服务密码
     * @param db    库
     * @param pool_size 连接池大小
     * @return
     */
    static bool init(std::string ip,int port,std::string pwd,int db=0,int pool_size = 2);

    /**
     * 获取连接池的一个连接
     * @return
     */
    static std::shared_ptr<ZRedisConnection> Get();

    /**
     * 将获取的连接返回连接池
     * @param con
     */
    static void Back(std::shared_ptr<ZRedisConnection> &con);


    /**
     * 获取当前连接池可用连接资源数
     * @return
     */
    static int size();

private:
    static std::mutex mtx_;         //资源锁，防止多线程操作连接池
    static std::vector<std::shared_ptr<ZRedisConnection>> connect_pool_;            //连接池容器

};