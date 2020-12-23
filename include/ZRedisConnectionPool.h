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
     * ��ʼ�����ӳ�
     * @param ip    ����ip
     * @param port  ����˿�
     * @param pwd   ��������
     * @param db    ��
     * @param pool_size ���ӳش�С
     * @return
     */
    static bool init(std::string ip,int port,std::string pwd,int db=0,int pool_size = 2);

    /**
     * ��ȡ���ӳص�һ������
     * @return
     */
    static std::shared_ptr<ZRedisConnection> Get();

    /**
     * ����ȡ�����ӷ������ӳ�
     * @param con
     */
    static void Back(std::shared_ptr<ZRedisConnection> &con);


    /**
     * ��ȡ��ǰ���ӳؿ���������Դ��
     * @return
     */
    static int size();

private:
    static std::mutex mtx_;         //��Դ������ֹ���̲߳������ӳ�
    static std::vector<std::shared_ptr<ZRedisConnection>> connect_pool_;            //���ӳ�����

};