#include <iostream>
using namespace std;
// 1+2+3+...+n������ʵ�ַ�ʽ�ݹ顢ѭ��
 
int AddFrom1ToN_Recursive(int n)
{
    return n<=0 ? 0 : n + AddFrom1ToN_Recursive(n-1);
}
 
int AddFrom1ToN_Iterative(int n)
{
    int result = 0;
    for (int i = 0; i <= n ; ++i) {
        result += i;
    }
    return result;
}
 
int main()
{
    cout<<AddFrom1ToN_Recursive(100)<<endl;
    cout<<AddFrom1ToN_Iterative(100)<<endl;
    return 0;
}