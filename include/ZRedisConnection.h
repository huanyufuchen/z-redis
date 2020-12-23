#pragma once
#include <string>
#include <hiredis/hiredis.h>
#include <vector>
#include <memory>

#define NIL "NIL"
enum RedisStatus
{
    M_REDIS_OK = 0, //执行成功
    M_CONNECT_FAIL = -1, //连接redis失败
    M_CONTEXT_ERROR = -2, //RedisContext返回错误
    M_REPLY_ERROR = -3, //redisReply错误
    M_EXE_COMMAND_ERROR = -4, //redis命令执行错误
    M_NIL_ERROR = -5 //nil
};

enum ReturnType
{
    M_INT = 0,
    M_BIG_INT,
    M_BINARY,
    M_STRING,
};

typedef enum en_redisResultType
{
    redis_reply_invalid = -1,
    redis_reply_string,
    redis_reply_integer,
    redis_reply_array,
    redis_reply_null
}RedisResultType;

typedef struct st_redisResult
{
    int type;
    size_t inter;
    std::string strdata;
    std::vector<std::string> vecdata;
}RedisResult;

class ZRedisConnection
{

public:
    ZRedisConnection();
    ~ZRedisConnection();
    /**
     * 连接服务
     * @param addr  地址
     * @param port  端口
     * @param pwd   密码
     * @param db    数据库
     * @return      是否成功
     */
    bool Connect(const std::string &addr, int port, const std::string &pwd = "",int db=0);


    /**
     * 是否连接
     * @return
     */
    bool IsConnect();

    /**
     * 解析结果
     * @param result
     * @param reply
     * @return
     */
    RedisStatus ParseReplay(RedisResult &result, redisReply *reply = NULL);

    /**
     * 执行命令
     * @param cmd
     * @param res
     * @return
     */
    static RedisStatus ExecCmd(const std::string &cmd, RedisResult &res);
private:
    /**
     * 使用密码
     * @param psw
     * @return
     */
    int ConnectAuth(const std::string &psw);
    /**
     * 释放命令执行结果的内存
     * @param reply
     * @return
     */
    int FreeRedisReply(redisReply *reply);

    /**
     * 解析错误
     * @param reply
     * @return
     */
    RedisStatus CheckErr(redisReply *reply = NULL);

    /**
     * 选择数据库
     * @param db
     * @return
     */
    int SelectDb(const int &db);

public:

    redisContext* pm_rct; //redis结构体
    redisReply* pm_rr; //返回结构体

    std::string addr_; //IP地址
    int port_; //端口号
    std::string pwd_; //密码

private:
    bool is_connect_ = false;
};
