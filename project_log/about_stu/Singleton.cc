#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <future>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <utility>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <sstream>
#include <fstream>

/*
饿汉模式 --
*/
class Singleton_hunger
{
private:
    static Singleton_hunger _eton;
    Singleton_hunger() : _data(99)
    {
        std::cout << "单例对象(懒汉)构造成功" << std::endl;
    };
    ~Singleton_hunger() {};
    Singleton_hunger(const Singleton_hunger &) = delete;
    Singleton_hunger &operator=(const Singleton_hunger &) = delete;
    // 拷贝复制已被静止

private:
    int _data;

public:
    static Singleton_hunger &getInstance()
    {
        return _eton;
    }
    int getData()
    {
        return _data;
    }
};

Singleton_hunger Singleton_hunger::_eton;

/*
懒汉模式:懒加载 -- 延迟思想--一个对象在使用的时候才会进行实例化
*/
class Singleton_lazy
{
private:
    Singleton_lazy() : _data(99)
    {
        std::cout << "单例对象(饿汉)构造成功" << std::endl;
    };
    ~Singleton_lazy() {};
    Singleton_lazy(const Singleton_lazy &) = delete;

    int _data;

public:
    static Singleton_lazy &getInstance()
    {
        static Singleton_lazy _eton;
        return _eton;
    }
    int getData()
    {
        return _data;
    }
};

void test()
{
    // std::cout << Singleton_hunger::getInstance().getData() << "\n";
    std::cout << Singleton_lazy::getInstance().getData() << "\n";
}

int main()
{
    test();
}