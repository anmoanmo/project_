#include <iostream>
#include <memory>
#include <string>

/* 抽象产品类 */
class Computer
{
public:
    using ptr = std::shared_ptr<Computer>;
    void setBoard(const std::string &board) { _board = board; }
    void setDisplay(const std::string &display) { _display = display; }
    virtual void setOs() = 0;
    std::string toString()
    {
        return "Computer:{\n\tboard=" + _board + ",\n\tdisplay=" + _display + ",\n\tOs=" + _os + "\n}\n";
    }

protected:
    std::string _board, _display, _os;
};

/* 具体产品类 */
class MacBook : public Computer
{
public:
    using ptr = std::shared_ptr<MacBook>;
    virtual void setOs() override
    {
        _os = "Mac OS X12";
    }
};

/* 抽象建造者 */
class Builder
{
public:
    using ptr = std::shared_ptr<Builder>;
    virtual void buildBoard(const std::string &board) = 0;
    virtual void buildDisplay(const std::string &display) = 0;
    virtual void buildOs() = 0;
    virtual Computer::ptr build() = 0;
};

/* 具体建造者 */
class MacBookBuilder : public Builder
{
public:
    using ptr = std::shared_ptr<MacBookBuilder>;
    MacBookBuilder() : _computer(new MacBook()) {}
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

/* 指挥者类 */
class Director
{
public:
    Director(Builder *builder) : _builder(builder) {}
    void construct(const std::string &board, const std::string &display)
    {
        _builder->buildBoard(board);
        _builder->buildDisplay(display);
        _builder->buildOs();
    }

private:
    Builder::ptr _builder;
};

/* 测试主函数 */
int main()
{
    Builder *builder = new MacBookBuilder();
    std::unique_ptr<Director> pd(new Director(builder));
    pd->construct("英特尔主板", "VOC显示器");
    Computer::ptr computer = builder->build();
    std::cout << computer->toString();
    return 0;
}