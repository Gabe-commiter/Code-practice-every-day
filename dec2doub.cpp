#include<iostream>
#include<vector>
#include"math.h"
#include<iomanip>
#include <fstream>

using namespace std;

vector<bool> zhengshu;//���������ֵĶ�����
vector<bool> xiaoshu;//��С�����ֵĶ�����

vector<bool> get_zhengshu_2b(float a)
{
    vector<bool> x;
    x.clear();
    //��λ������a xxxx xxxx��1000 0000�룬�õ�ÿλ�Ķ�������
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
    //��ȡ�������ֵĶ�������
    float fabs_a = fabs(a);//ȡ����ֵ
    zhengshu.clear();
    xiaoshu.clear();
    zhengshu = get_zhengshu_2b(fabs_a);

    //��ȡС�����ֵĶ�������
    float n = 2;   //С��λ�Ľ���ȡ����
    float b = (fabs_a - floor(fabs_a));

    //ÿ�γ���2�жϸ�λ��0����1
    while (!b == 0)
    {
        if ((1.0 / n) < b)
        {
            xiaoshu.push_back(1);
            //��Ϊ1��b��ȥ��λ����Ӧ��ʮ����С����С �������жϵ�һλ��ֱ��b=0
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
int get_jiema()  //���ؽ���
{
    for (int i = 0; i < 8; i++) {
        if (zhengshu[i] == 1)//�жϴ�������һ��Ϊ1��λ��
            return 7 - i;        // ���ؽ����С
    }
}
vector<bool> get_yima()//�õ�����
{
    int e = get_jiema();
    e = e + 127;  //����ƫ�Ƶõ�����
    return get_zhengshu_2b(e);//���ػ�õ�����Ķ�������ʽ
}
vector<bool> get_weima()//���β��
{
    vector <bool> m;
    //С���Ķ�����ǰ�����񻯵���õ�β��
    xiaoshu.insert(xiaoshu.begin(), zhengshu.begin() + (8 - get_jiema()), zhengshu.end());
    m = xiaoshu;
    return m;
}
vector<bool> to_IEEE754(float x)
{
    vector<bool> IEEE;
    IEEE.clear();
    get_2b(x);   //�õ�x�Ķ�������
    /*
    //���ԭ���Ķ�������ʽ
    cout << "����ֵ�Ķ�������Ϊ��" << endl;
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
    //�������
    cout << "����Ϊ��" << endl;


    vector<bool> E = get_yima();
    for (int i = 0; i < 8; i++)
    {
        cout << E[i];
    }
    cout << endl;
    */
    //��ϳɶ̸��������룺
    vector<bool> yima;
    yima.clear();
    yima = get_yima();
    vector<bool> weima;
    weima.clear();
    weima = get_weima();

    if (x > 0)//�жϲ���ӷ���λ
    {
        IEEE.insert(IEEE.end(), 1, 0);
    }
    else
    {
        IEEE.insert(IEEE.end(), 1, 1);
    }
    IEEE.insert(IEEE.end(), yima.begin(), yima.end());//�������
    IEEE.insert(IEEE.end(), weima.begin(), weima.end());//���β��
    IEEE.insert(IEEE.end(), 32 - 9 - weima.size(), 0);//β������ ��32λ
    return IEEE;
}
void get_hex(vector<bool> E)//�õ�ʮ��������ʾ
{
    ofstream out;
    out.open("D:\\Desktop\\���.txt", ios::app);

    vector<bool>::iterator ite = E.begin();//������
    int sum = 0;
    int n = 8;
    while (n--)//����ѭ��
    {
        for (int i = 0; i < 4; i++)//��ÿ4λ��ʮ�����Ʊ�ʾ
        {
            sum = sum + (*ite)*pow(2, 3 - i);//8 4 2 1
            ite++;
        }

        cout << setiosflags(ios::uppercase) << hex << sum;//16���ƴ�д��ĸ���

        out << setiosflags(ios::uppercase) << hex << sum;// д���ļ�
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
    //////////////��ʮ���ƵĶ̸���������//////////////////////////////////////

    if (!in.good())
    {
        cout << "�ļ���ʧ��" << endl;
        system("pause");
        return 0;
    }
    while (!in.eof())
    {
        float x;
        vector<bool> IEEE;
        in >> x;
        cout << x <<"ת��Ϊ��" ;
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
    cout << "ת�����" << endl;
    system("pause");

    return 0;

}
