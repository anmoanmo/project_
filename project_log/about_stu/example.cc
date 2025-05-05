/*
不定参宏函数的使用
*/

#include <cstdio>
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>

// ANSI color codes
#define CLR_RED "\033[1;31m"
#define CLR_GREEN "\033[1;32m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_BLUE "\033[1;34m"
#define CLR_RESET "\033[0m"

// 彩色日志宏（默认使用绿色输出）
#define LOG(fmt, ...) \
    printf("[%s : %d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

void printNum(int n, ...)
{
    va_list al;
    va_start(al, n); // 让 al 指向 n 参数之后的第一个可变参数

    for (int i = 0; i < n; i++)
    {
        int num = va_arg(al, int); // 从可变参数中取出一个整型参数
        std::cout << num << std::endl;
    }

    va_end(al); // 清空可变参数列表，实际是将 al 置空
}

void myprintf(const char *fmt, ...)
{
    char *res;
    va_list al;
    va_start(al, fmt);

    int len = vasprintf(&res, fmt, al);
    if (len != -1)
    {
        printf(res);
        free(res);
    }

    va_end(al);
}

void xprintf()
{
    std::cout << std::endl;
}

template <typename T, typename... Args>
void xprintf(const T &value, Args &&...args)
{
    std::cout << value << " ";
    if ((sizeof...(args)) > 0)
    {
        xprintf(std::forward<Args>(args)...); // 递归展开
    }
    else
    {
        xprintf();
    }
}

template <typename... Args>
void xprintf_c17(Args &&...args)
{
    (std::cout << ... << args);
}

int main()
{

    LOG("%s", "你好！测试11");
    printNum(5, 1, 2, 3, 4, 5);
    myprintf("%s - %d\n", "我可能把你和夏天相比拟？", 112);
    xprintf_c17("aaa", "你好啊", "测试下c++的不定参宏函数");

    // printf("[,%s - %d]  %s - %d\n", __FILE__, __LINE__, "啊啊??", 123);
    return 0;
}