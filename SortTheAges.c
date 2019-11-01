#include <iostream>
using namespace std;
// 对一个公司中所有员工的年龄进行排序
/*parameters:
 * ages[]:the age of stuff
 * length:the length of the ages[]
 */
void SortAges(int ages[], int length)
{
    //对数组ages[]进行判断
    if(ages == nullptr || length <= 0)
        return;
    const int oldestAge = 99;
    //公司员工的年龄在0~99岁，所以timesOfAge[]数组的大小为100
    int timesOfAge[oldestAge + 1];
    //初始化数组timesOfAge[]
    for (int i = 0; i <= oldestAge ; ++i) {
        timesOfAge[i] = 0;
    }
    //ages[]中的元素为i就在timesOfAge[i]上加一，来统计年龄为i的人数
    for (int j = 0; j < length; ++j) {
        int age = ages[j];
        if(age < 0 || age > oldestAge)
            throw new std::exception();
        ++timesOfAge[age];
    }
    //遍历timesOfAge[]数组，某个年龄出现了多少次，就在数组ages[]里面设置几次年龄
    int index = 0;
    for (int k = 0; k <=oldestAge ; ++k) {
        for (int i = 0; i < timesOfAge[k]; ++i) {
            ages[index] = k;
            ++index;
        }
    }
}
int main()
{
   int arr[] = {22,40,18,19,50,21,22,33,44,43};
   int length = sizeof(arr) / sizeof(int);
   SortAges(arr,length);
    for (int i = 0; i < length; ++i) {
        cout<<arr[i]<<" ";
    }

}