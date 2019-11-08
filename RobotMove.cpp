#include <cstdio>
int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited);
bool check(int threshold, int rows, int cols, int row, int col, const bool* visited);
int getDigitSum(int number);

// 这个题要求的是能达到的符合条件的所有格子的数目，有些理解为什么这么写了！
int movingCount(int threshold, int rows, int cols)
{
    if(threshold < 0 || rows <= 0 || cols <= 0)
        return 0;
    bool *visited = new bool[rows * cols];// 建一个矩阵大小的bool矩阵
    // 初始化矩阵
    for (int i = 0; i < rows * cols; ++i) {
        visited[i] = false;
    }

    int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
    delete [] visited;// 防止内存泄漏
    return count;
}

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited)
{
    int count = 0;
    if(check(threshold,rows, cols, row, col, visited))// 判断传进来的（row,col）是否符合约束
    {
        visited[row * cols + col] = true;// 符合的话，相应的bool矩阵置1
        count = 1 + movingCountCore(threshold, rows, cols,
                                    row - 1, col, visited)
            + movingCountCore(threshold, rows, cols,
                              row, col - 1, visited)
            + movingCountCore(threshold, rows, cols,
                              row + 1, col, visited)
            + movingCountCore(threshold, rows, cols,
                              row, col + 1, visited);
    }
    return count;
}
// 判断是否符合约束的函数
bool check(int threshold, int rows, int cols, int row, int col, const bool* visited)
{
    return row >= 0 && row < rows && col >= 0 && col < cols && getDigitSum(row) + getDigitSum(col) <= threshold
        && !visited[row * cols + col];
}
// 求一个输入的整数的各个数位之和
int getDigitSum(int number)
{
    int sum = 0;
    while(number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

// ====================测试代码====================
void test(char* testName, int threshold, int rows, int cols, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(movingCount(threshold, rows, cols) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// 方格多行多列
void test1()
{
    test("Test1", 5, 10, 10, 21);
}

// 方格多行多列
void test2()
{
    test("Test2", 15, 20, 20, 359);
}

// 方格只有一行，机器人只能到达部分方格
void test3()
{
    test("Test3", 10, 1, 100, 29);
}

// 方格只有一行，机器人能到达所有方格
void test4()
{
    test("Test4", 10, 1, 10, 10);
}

// 方格只有一列，机器人只能到达部分方格
void test5()
{
    test("Test5", 15, 100, 1, 79);
}

// 方格只有一列，机器人能到达所有方格
void test6()
{
    test("Test6", 15, 10, 1, 10);
}

// 方格只有一行一列
void test7()
{
    test("Test7", 15, 1, 1, 1);
}

// 方格只有一行一列
void test8()
{
    test("Test8", 0, 1, 1, 1);
}

// 机器人不能进入任意一个方格
void test9()
{
    test("Test9", -10, 10, 10, 0);
}

int main(int agrc, char* argv[])
{
    test1();
    
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();

    return 0;
}

