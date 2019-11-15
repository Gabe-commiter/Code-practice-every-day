#include<iostream>
#include<vector>
#include"math.h"
#include<iomanip>
#include <fstream>

using namespace std;

vector<bool> zhengshu;//存整数部分的二进制
vector<bool> xiaoshu;//存小数部分的二进制

vector<bool> get_zhengshu_2b(float a)
{
    vector<bool> x;
    x.clear();
    //八位二进制a xxxx xxxx与1000 0000与，得到每位的二进制数
    for (int i = 0; i < 8; i++)
    {
        if ((((int)a)&(0x80 >> i)))
        {
            x.push_back(1);
        }
        else
        {
            x.push_back(0);
        }
    }
    return x;
}

void get_2b(float a)
{
    //获取整数部分的二进制码
    float fabs_a = fabs(a);//取绝对值
    zhengshu.clear();
    xiaoshu.clear();
    zhengshu = get_zhengshu_2b(fabs_a);

    //获取小数部分的二进制码
    float n = 2;   //小数位的阶数取倒数
    float b = (fabs_a - floor(fabs_a));

    //每次除以2判断该位是0还是1
    while (!b == 0)
    {
        if ((1.0 / n) < b)
        {
            xiaoshu.push_back(1);
            //若为1则b减去该位所对应的十进制小数大小 ，继续判断低一位，直到b=0
            b = b - (1.0 / n);
        }
        else if ((1.0 / n) > b)
        {
            xiaoshu.push_back(0);
        }
        else if ((1.0 / n) == b)
        {
            xiaoshu.push_back(1);
            break;
        }
        n = n * 2;
    }
}
int get_jiema()  //返回阶码
{
    for (int i = 0; i < 8; i++) {
        if (zhengshu[i] == 1)//判断从左边起第一个为1的位置
            return 7 - i;        // 返回阶码大小
    }
}
vector<bool> get_yima()//得到移码
{
    int e = get_jiema();
    e = e + 127;  //阶码偏移得到移码
    return get_zhengshu_2b(e);//返回获得的移码的二进制形式
}
vector<bool> get_weima()//获得尾码
{
    vector <bool> m;
    //小数的二进制前插入规格化的码得到尾码
    xiaoshu.insert(xiaoshu.begin(), zhengshu.begin() + (8 - get_jiema()), zhengshu.end());
    m = xiaoshu;
    return m;
}
vector<bool> to_IEEE754(float x)
{
    vector<bool> IEEE;
    IEEE.clear();
    get_2b(x);   //得到x的二进制码
    /*
    //输出原数的二进制形式
    cout << "绝对值的二进制数为：" << endl;
    for (int i = 0; i < zhengshu.size(); i++)
    {
        cout << zhengshu[i];
    }
    cout << ".";
    for (int i = 0; i < xiaoshu.size(); i++)
    {
        cout << xiaoshu[i];
    }
    cout << endl;
    //输出移码
    cout << "移码为：" << endl;


    vector<bool> E = get_yima();
    for (int i = 0; i < 8; i++)
    {
        cout << E[i];
    }
    cout << endl;
    */
    //组合成短浮点数代码：
    vector<bool> yima;
    yima.clear();
    yima = get_yima();
    vector<bool> weima;
    weima.clear();
    weima = get_weima();

    if (x > 0)//判断并添加符号位
    {
        IEEE.insert(IEEE.end(), 1, 0);
    }
    else
    {
        IEEE.insert(IEEE.end(), 1, 1);
    }
    IEEE.insert(IEEE.end(), yima.begin(), yima.end());//添加移码
    IEEE.insert(IEEE.end(), weima.begin(), weima.end());//添加尾码
    IEEE.insert(IEEE.end(), 32 - 9 - weima.size(), 0);//尾部补零 共32位
    return IEEE;
}
void get_hex(vector<bool> E)//得到十六进制显示
{
    ofstream out;
    out.open("D:\\Desktop\\输出.txt", ios::app);

    vector<bool>::iterator ite = E.begin();//迭代器
    int sum = 0;
    int n = 8;
    while (n--)//八组循环
    {
        for (int i = 0; i < 4; i++)//求每4位的十六进制表示
        {
            sum = sum + (*ite)*pow(2, 3 - i);//8 4 2 1
            ite++;
        }

        cout << setiosflags(ios::uppercase) << hex << sum;//16进制大写字母输出

        out << setiosflags(ios::uppercase) << hex << sum;// 写入文件
        sum = 0;
    }
    out << endl;
    out.close();
    cout << endl;
}



int main()
{
    ofstream myFile;
    ifstream in;
    in.open("D:\\P1.txt");
    myFile.open("D:/data.txt",ios_base::out);
    //////////////求十进制的短浮点数代码//////////////////////////////////////

    if (!in.good())
    {
        cout << "文件打开失败" << endl;
        system("pause");
        return 0;
    }
    while (!in.eof())
    {
        float x;
        vector<bool> IEEE;
        in >> x;
        cout << x <<"转换为：" ;
        IEEE = to_IEEE754(x);
        //get_hex(IEEE);
        for (int i = 0; i <=31 ; ++i) {
            myFile << IEEE[i];
        }
        myFile<<endl;
        IEEE.clear();
        cout  << endl;
        //system("pause");
    }
    in.close();
    myFile.close();
    cout << "转换完成" << endl;
    system("pause");

    return 0;

}
