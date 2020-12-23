##安装

1. 首先依赖于hiredis，因此先安装hiredis。
```shell script
#首先下载源码
git clone https://github.com/redis/hiredis.git
#然后进入源码目录
make && make install
```
2. 编译z-redis；进入z-redis目录
```shell script
mkdir build
cd build
cmake ..
make
```

## z-redis的功能特色
- 断线重连
- 连接池
- 方便扩展
- 多种数据类型操作
- 使用简单

## z-redis的使用

> 使用非常简单：
> 1. 首先初始化一次，根据需要建立必要的连接池大小。
> 2. 然后实例化对应的数据类型操作类，记性对应的操作，方法名基本就是命令名。

- 首先初始化
```c++
//初始化连接池和密码
参数一：redis ip
参数二：redis port
参数三：redis 密码
参数四：redis 库
参数五：连接池个数
bool issucccess = ZRedisConnectionPool::init("127.0.0.1",6379,"passwd",0,5);
```

- string 的使用
```c++
//设置
ZRedisString zstr;
zstr.Set("user","zaizai");

//获取
std::string user;
RedisStatus res = zstr.Set("user",user);
if(res == M_REDIS_OK)
{
    std::cout <<user <<std::endl;
}else{
    std::cout << zstr.GetErr() <<std::endl;
};
```



