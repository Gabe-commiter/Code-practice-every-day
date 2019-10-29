#include <iostream>
using namespace std;
 
long long Fibonacci_1(unsigned int n)
{
    if(n <= 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    return Fibonacci_1(n - 1 ) + Fibonacci_1(n - 2);
}
int main()
{
    cout<<Fibonacci_1(100)<<endl;
    return 0;
}