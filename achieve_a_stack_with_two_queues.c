#include <iostream>
#include <queue>
#include <exception>
using namespace std;
//用两个队列来实现一个栈
template <typename T>class CStack
{
public:
    CStack(void){};
    ~CStack(void){};
    void appendTail(const T& element);
    T deleteHead();

private:
    queue<T> queue1;
    queue<T> queue2;
};

template <typename T> void CStack<T>::appendTail(const T &element)
{
    if(!queue1.empty() && !queue2.empty()){

    }
    else{
        if(queue1.empty()){
            queue2.push(element);
        }
        else{
            queue1.push(element);
        }

    }
}

template <typename T>T CStack<T>::deleteHead()
{
    if (queue1.empty() && queue2.empty()) {
        //异常情况
        throw new exception();
    }
    T head;
    if (!queue1.empty()) {
        while (queue1.size() > 1) {
            T &data = queue1.front();
            queue1.pop();
            queue2.push(data);
        }
        head = queue1.front();
        queue1.pop();
    }
    else {
        while(queue2.size() > 1){
            T& data = queue2.front();
            queue2.pop();
            queue1.push(data);
        }
        head = queue2.front();
        queue2.pop();
    }
    return head;
}
void test(char actual, char expected)
{
    if (actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}


int main()
{

    CStack<char> stack;

    stack.appendTail('a');
    stack.appendTail('b');
    stack.appendTail('c');

    char head = stack.deleteHead();
    test(head, 'c');

    head = stack.deleteHead();
    test(head, 'b');

    stack.appendTail('d');
    head = stack.deleteHead();
    test(head, 'd');

    stack.appendTail('e');
    head = stack.deleteHead();
    test(head, 'e');

    head = stack.deleteHead();
    test(head, 'a');

    //空栈删除，触发异常
    //head = stack.deleteHead();

    getchar();
    return 0;

}


