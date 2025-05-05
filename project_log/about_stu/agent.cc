#include <iostream>
#include <string>

// 抽象主题接口
class RentHouse
{
public:
    virtual void rentHouse() = 0;
};

// 真实主题：房东类
class Landlord : public RentHouse
{
public:
    void rentHouse() override
    {
        std::cout << "将房子租出去\n";
    }
};

// 代理类：中介
class Intermediary : public RentHouse
{
public:
    void rentHouse() override
    {
        std::cout << "发布招租启示\n";
        std::cout << "带人看房\n";
        _landlord.rentHouse(); // 调用真实对象
        std::cout << "负责租后维修\n";
    }

private:
    Landlord _landlord; // 持有目标对象
};

// 客户端调用
int main()
{
    Intermediary intermediary;
    intermediary.rentHouse();
    return 0;
}