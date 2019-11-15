
/*
        Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
        R:测量噪声，R增大，动态响应变慢，收敛稳定性变好
*/

/* 卡尔曼滤波处理雷达高度表程序*/
#include <iostream>
#include <fstream>
using namespace std;
static float KalmanFilter(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
{

    float R = MeasureNoise_R;
    float Q = ProcessNiose_Q;

    static float x_last = 160;
    float x_mid = x_last;
    float x_now;

    static float p_last = 0.01;
    float p_mid ;
    float p_now;

    float kg;

    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
    /*
     *  卡尔曼滤波的五个重要公式
     */
    kg=p_mid/(p_mid+R);                 //kg为kalman filter，R 为噪声
    x_now=x_mid+kg*(ResrcData-x_mid);   //估计出的最优值
    p_now=(1-kg)*p_mid;                 //最优值对应的covariance
    p_last = p_now;                     //更新covariance 值
    x_last = x_now;                     //更新系统状态值
    return p_now;
}
int main()
{
    ofstream out;
    ifstream in;
    float x = 0.0;
    float fa = 0.0;
    in.open("D:/p1.txt");
    out.open("D:/pk.txt",ios_base::out);
    if (!in.good()&&!out.good())
    {
        cout << "文件打开失败" << endl;
        system("pause");
        return 0;
    }
    while (!in.eof())
    {
        
        in >> x;
        fa = KalmanFilter(x,0.001,2308);
        out << fa <<endl;

    }
    in.close();
    out.close();
    cout << "转换完成" << endl;
    system("pause");

    return 0;

}