
#include "ZRedisConnection.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <memory>
#include <ZRedisConnectionPool.h>
#include <ZRedisBase.h>
#include <thread>
#include <glog/logging.h>
#include "ZRedisTransactions.h"
ZRedisConnection::ZRedisConnection(){
}


bool ZRedisConnection::Connect(const std::string &addr, int port, const std::string &pwd,int db) {
    addr_ = addr;
    port_ = port;
    pwd_ = pwd;
    pm_rct = redisConnect(addr_.c_str(), port_);
    if (pm_rct->err)
    {
        is_connect_ = false;
    }
    if (!pwd_.empty())
    {
        ConnectAuth(pwd_);
    }
    SelectDb(db);

    is_connect_ = true;
    return is_connect_;
}

/*
使用密码登录
psw：登录密码
成功返回M_REDIS_OK，失败返回<0
*/
int ZRedisConnection::ConnectAuth(const std::string &psw)
{
    std::string cmd = "auth " + psw;
    pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());
    return 0;
}


int ZRedisConnection::SelectDb(const int &db)
{
    std::string cmd = "select " + std::to_string(db);
    pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());
    return 0;
}

ZRedisConnection::~ZRedisConnection()
{
    redisFree(pm_rct);
}

bool ZRedisConnection::IsConnect()
{
    return is_connect_;
}

RedisStatus ZRedisConnection::CheckErr(redisReply *reply)
{
    if(reply == NULL)
    {
        reply = pm_rr;
    }
    if (pm_rct->err)
    {
//        error_msg = pm_rct->errstr;
        ZRedisBase::SetError(pm_rct->errstr);
        return M_CONTEXT_ERROR;
    }
    if (reply == NULL)
    {
//        error_msg = "auth redisReply is NULL";
        ZRedisBase::SetError("auth redisReply is NULL");
        return M_REPLY_ERROR;
    }
    return M_REDIS_OK;
}

RedisStatus ZRedisConnection::ParseReplay(RedisResult &result,redisReply *reply)
{
    if(reply == NULL)
    {
        reply = pm_rr;
    }
    RedisStatus s = CheckErr(reply);
    if(s != M_REDIS_OK)
    {
        FreeRedisReply(reply);
        return s;
    }

    switch(reply->type)
    {
        case REDIS_REPLY_STATUS:
            s = M_REDIS_OK;
            result.type = reply->type;
            result.strdata = reply->str;
            break;
        case REDIS_REPLY_ERROR:
            s = M_REPLY_ERROR;
            result.type = redis_reply_null;
            result.strdata =reply->str;
            ZRedisBase::SetError(reply->str);
            break;
        case REDIS_REPLY_STRING:
            s = M_REDIS_OK;
            result.type = redis_reply_string;
            result.strdata = reply->str;
            break;
        case REDIS_REPLY_INTEGER:
            s = M_REDIS_OK;
            result.type = redis_reply_integer;
            result.inter = reply->integer;
            break;
        case REDIS_REPLY_ARRAY:
            s = M_REDIS_OK;
            result.type = redis_reply_array;
            for (int i = 0; i < reply->elements; i ++)
            {
                if(reply->element[i]->type == REDIS_REPLY_NIL)
                {
                    result.vecdata.push_back(NIL);
                }else{
                    if(reply->element[i]->str==NULL)
                    {
                        result.vecdata.push_back("null");
                    }else{
                        result.vecdata.push_back(reply->element[i]->str);
                    }
                }

            }
            break;
        case REDIS_REPLY_NIL:
            s = M_NIL_ERROR;
            result.type = redis_reply_null;
            result.strdata = "REDIS_REPLY_NIL";
            if(reply->str == NULL)
            {
                ZRedisBase::SetError("REDIS_REPLY_NIL");
            }else{
                ZRedisBase::SetError(reply->str);
            }
            break;
        default:
            s = M_REPLY_ERROR;
            result.type = redis_reply_invalid;
            break;
    }

    FreeRedisReply(reply);
    return s;
}

int ZRedisConnection::FreeRedisReply(redisReply *reply)
{
    if (reply)
    {
        freeReplyObject(reply);
        reply = NULL;
    }
    return 0;
}

RedisStatus ZRedisConnection::ExecCmd(const std::string &cmd,RedisResult &res)
{

    if(cmd == "MUTI"){
        ZRedisTransactions::start_transactions = true;
    }else if(cmd == "EXEC"){
        ZRedisTransactions::start_transactions = false;
    }

    std::shared_ptr<ZRedisConnection> con;
    //事务连接
    if(ZRedisTransactions::start_transactions)
    {
        con = ZRedisTransactions::conn;
    }else{
        con = ZRedisConnectionPool::Get();
    }


    //掉线重连
    int index = 0;
    while (con->pm_rr == NULL) {
        ZRedisConnection * zcon  = new ZRedisConnection();
        zcon->Connect(con->addr_,con->port_,con->pwd_);
        con.reset(zcon);
        LOG(ERROR) << "offline reconnect count :" << index++;
        int sleep_time = index*2+1;
        std::this_thread::sleep_for(std::chrono::seconds (sleep_time));
    }

    con->pm_rr = (redisReply*)redisCommand(con->pm_rct, cmd.c_str());
    RedisStatus s = con->ParseReplay(res);

    //非事务回收
    if(!ZRedisTransactions::start_transactions) {
        ZRedisConnectionPool::Back(con);
    }
    return s;
}


