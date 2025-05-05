#include <iostream>
#include <memory>
using namespace std;

// 抽象产品 A：CPU
class CPU
{
public:
    virtual void compute() = 0;
    virtual ~CPU() = default;
};

// 抽象产品 B：主板 MainBoard
class MainBoard
{
public:
    virtual void installCPU() = 0;
    virtual ~MainBoard() = default;
};

// 具体产品 A1：华硕 CPU
class AsusCPU : public CPU
{
public:
    void compute() override
    {
        cout << "华硕 CPU 正在计算...\n";
    }
};

// 具体产品 B1：华硕主板
class AsusMainBoard : public MainBoard
{
public:
    void installCPU() override
    {
        cout << "正在将华硕 CPU 安装到华硕主板上...\n";
    }
};

// 具体产品 A2：联想 CPU
class LenovoCPU : public CPU
{
public:
    void compute() override
    {
        cout << "联想 CPU 正在计算...\n";
    }
};

// 具体产品 B2：联想主板
class LenovoMainBoard : public MainBoard
{
public:
    void installCPU() override
    {
        cout << "正在将联想 CPU 安装到联想主板上...\n";
    }
};

// 抽象工厂：电脑工厂
class ComputerFactory
{
public:
    virtual unique_ptr<CPU> createCPU() = 0;
    virtual unique_ptr<MainBoard> createMainBoard() = 0;
    virtual ~ComputerFactory() = default;
};

// 具体工厂：华硕工厂
class AsusFactory : public ComputerFactory
{
public:
    unique_ptr<CPU> createCPU() override
    {
        return make_unique<AsusCPU>();
    }

    unique_ptr<MainBoard> createMainBoard() override
    {
        return make_unique<AsusMainBoard>();
    }
};

// 具体工厂：联想工厂
class LenovoFactory : public ComputerFactory
{
public:
    unique_ptr<CPU> createCPU() override
    {
        return make_unique<LenovoCPU>();
    }

    unique_ptr<MainBoard> createMainBoard() override
    {
        return make_unique<LenovoMainBoard>();
    }
};

// 客户端函数：组装电脑
void assembleComputer(unique_ptr<ComputerFactory> factory)
{
    auto cpu = factory->createCPU();
    auto mb = factory->createMainBoard();
    mb->installCPU();
    cpu->compute();
}

int main()
{
    cout << "--- 组装华硕电脑 ---\n";
    std::unique_ptr<ComputerFactory> computer(new AsusFactory());
    computer->createMainBoard()->installCPU();
    computer->createCPU()->compute();
    // assembleComputer(make_unique<AsusFactory>());

    cout << "\n--- 组装联想电脑 ---\n";
    computer.reset(new LenovoFactory());
    computer->createMainBoard()->installCPU();
    computer->createCPU()->compute();
    // assembleComputer(make_unique<LenovoFactory>());

    return 0;
}
