#include <iostream>
using namespace std;
//求斐波那契数列的第N项
long long Fibonacci_2(unsigned int n)
{
    int result[2] = {0 , 1};
    if(n < 2){
        return result[n];
    }
    long long fibNMinusOne = 1;
    long long fibNMinusTwo = 0;
    long long fibN = 0;
    for (unsigned int i = 2; i <= n ; ++i) {
        fibN = fibNMinusTwo + fibNMinusOne;
        fibNMinusTwo = fibNMinusOne;
        fibNMinusOne = fibN;
    }
    return fibN;
 }
int main()
{
    cout<<Fibonacci_2(100)<<endl;
    return 0;
}