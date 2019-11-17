#include<iostream>
using namespace std;
//统计输入的整数中的二进制表示中1的个数
//此解法可能引起死循环
int NumberOf1(int n)
{
    int count = 0;
    while (n)
    {
        if(n & 1)
            count++;
        n = n >> 1;
    }
    return count;
}
//常规解法
int NumberOf2(int n)
{
    int count = 0;
    unsigned int flag = 1;
    while (flag)
    {
        if(n & flag)
            count++;
        flag = flag << 1;
    }
    return count;
}
//高级解法
int NumberOf3(int n)
{
    int count = 0;
    while (n)
    {
        ++count;
        n = (n -1)&n;
    }
    return count;
}
//用一条语句来判断输入的数是不是2的整数幂
bool JudgeNumIsMultipleOf2(int n)
{
//    if(((n -1)&n) == 0)
//        return true;
//    else
//        return false;
    return ((n - 1) & n) == 0;
}
//输入两个整数m和n，那么需要改变m二进制中表示的多少位，才能得到n
int Judge(int n, int m)
{
    int result = m ^ n;
    return NumberOf3(result);
}