##��װ

1. ����������hiredis������Ȱ�װhiredis��
```shell script
#��������Դ��
git clone https://github.com/redis/hiredis.git
#Ȼ�����Դ��Ŀ¼
make && make install
```
2. ����z-redis������z-redisĿ¼
```shell script
mkdir build
cd build
cmake ..
make
```

## z-redis�Ĺ�����ɫ
- ��������
- ���ӳ�
- ������չ
- �����������Ͳ���
- ʹ�ü�

## z-redis��ʹ��

> ʹ�÷ǳ��򵥣�
> 1. ���ȳ�ʼ��һ�Σ�������Ҫ������Ҫ�����ӳش�С��
> 2. Ȼ��ʵ������Ӧ���������Ͳ����࣬���Զ�Ӧ�Ĳ���������������������������

- ���ȳ�ʼ��
```c++
//��ʼ�����ӳغ�����
����һ��redis ip
��������redis port
��������redis ����
�����ģ�redis ��
�����壺���ӳظ���
bool issucccess = ZRedisConnectionPool::init("127.0.0.1",6379,"passwd",0,5);
```

- string ��ʹ��
```c++
//����
ZRedisString zstr;
zstr.Set("user","zaizai");

//��ȡ
std::string user;
RedisStatus res = zstr.Set("user",user);
if(res == M_REDIS_OK)
{
    std::cout <<user <<std::endl;
}else{
    std::cout << zstr.GetErr() <<std::endl;
};
```



