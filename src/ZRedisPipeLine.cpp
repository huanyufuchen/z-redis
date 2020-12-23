#include <iostream>
#include <ZRedisConnectionPool.h>
#include "ZRedisPipeLine.h"




RedisStatus ZRedisPipeLine::PipLine(std::vector<std::string> vcmd, std::vector<RedisResult> &vresult)
{
    RedisStatus status = M_REDIS_OK;
    if (vcmd.empty()){
        return M_EXE_COMMAND_ERROR;
    }

    std::shared_ptr<ZRedisConnection> con = ZRedisConnectionPool::Get();
    for (int i = 0; i < vcmd.size(); i ++)
    {
        redisAppendCommand(con->pm_rct, vcmd[i].c_str());
    }

    for (int i = 0; i < vcmd.size(); i ++)
    {
        int ret = -1;
        RedisResult result;
        redisReply *replay = NULL;
        if (redisGetReply(con->pm_rct, (void **)&replay) == REDIS_OK && replay != NULL)
        {
            con->ParseReplay(result,replay);
        }
        else
        {
            if(replay !=NULL)
            {
                freeReplyObject(replay);
                replay = NULL;
            }
            status = M_REPLY_ERROR;
        }

        vresult.push_back(result);
    }
    ZRedisConnectionPool::Back(con);
    status = M_REDIS_OK;
    return status;
}