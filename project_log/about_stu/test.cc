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

class Computer
{
public:
    using ptr = std::shared_ptr<Computer>;
    void setBoard(const std::string &board) { _board = board; };
    void setDisplay(const std::string &display) { _display = display; };
    virtual void setOs() = 0;
    std::string toString()
    {
        return "Computer:{\n\tboard=" + _board + ",\n\tdisplay=" + _display + ",\n\tOs=" + _os + "\n}\n";
    }

protected:
    std::string _board, _display, _os;
};

class MacBook : public Computer
{
public:
    using ptr = std::shared_ptr<MacBook>;
    virtual void setOs() override
    {
        _os = "Mac OS";
    }
};

class Buider
{
public:
    using ptr = std::shared_ptr<Buider>;
    virtual void buildBoard(const std::string &board) = 0;
    virtual void buildDisplay(const std::string &display) = 0;
    virtual void buildOs() = 0;
    virtual Computer::ptr build() = 0;
};

class MacBoosBuider : public Buider
{
public:
    using ptr = std::shared_ptr<MacBoosBuider>;
    MacBoosBuider() : _computer(new MacBook()) {};
    virtual void buildBoard(const std::string &board) override
    {
        _computer->setBoard(board);
    }
    virtual void buildDisplay(const std::string &display) override
    {
        _computer->setDisplay(display);
    }
    virtual void buildOs() override
    {
        _computer->setOs();
    }
    virtual Computer::ptr build() override
    {
        return _computer;
    }

private:
    Computer::ptr _computer;
};

class Director
{
public:
    Director(Buider *builder) : _builder(builder) {};
    void construct(const std::string &board, const std::string &display)
    {
        _builder->buildBoard(board);
        _builder->buildDisplay(display);
        _builder->buildOs();
    }

private:
    Buider::ptr _builder;
};

int main()
{
    Buider *builder = new MacBoosBuider();
    std::unique_ptr<Director> pd(new Director(builder));
    pd->construct("英特尔主板", "AUC显示器aaa");
    Computer::ptr computer = builder->build();
    std::cout << computer->toString();
    return 0;
}