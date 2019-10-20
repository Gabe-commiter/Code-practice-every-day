#include "util.h"
 
// 定义测试数据结构体
typedef struct test_data
{
    int time_t;
    int l_weight;
    int r_weight;
} data;
 
// 字符串分割函数
vector<string> &split(const string &str, const string &delimiters, vector<string> &elems, bool skip_empty = true)
{
    string::size_type pos, prev = 0;
    while ((pos = str.find_first_of(delimiters, prev)) != string::npos) {
        if (pos > prev) {
            if (skip_empty && 0 == pos - prev) break;
            elems.emplace_back(str, prev, pos - prev);
        }
        prev = pos + 1;
    }
    if (prev < str.size()) elems.emplace_back(str, prev, str.size() - prev);
    return elems;
}
// 结构体和容器初始化函数
void init(data &temp_data, vector<string> &result)
{
    temp_data = {0, 0, 0};
    result.clear();
}
// string转int函数
void str2int(data &temp_data, vector<string> &result)
{
    stringstream converterStream;
    for (int i = 0; i < result.size(); ++i) {
        converterStream << result[i];
        converterStream >> *((int *) &temp_data + i);
        converterStream.clear();
    }
}
// 检查打开文件是否成功的包裹函数
void check_file(ifstream &infile)
{
    if (!infile.is_open()) {
        perror("fopen");
        exit(1);
    }
}
//主函数
int main()
{
    ifstream infile("D:/310848210.dat");
    data temp_data;
    vector<data> last_data;
    vector<string> result;
    string temp, temp1;
    check_file(infile);
    getline(infile, temp1);
    while (getline(infile, temp)) {
        split(temp, ":,;", result);
        str2int(temp_data, result);
        last_data.push_back(temp_data);
        init(temp_data, result);
    }
    cout << last_data.size() << endl;
    infile.close();
    return 0;
}