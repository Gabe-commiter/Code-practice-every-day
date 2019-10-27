#include <iostream>
#include <stack>
#include <exception>
using namespace std;
//用两个栈来实现一个队列的代码
template <typename T>class CQueue
{
public:
    CQueue(void){};
    ~CQueue(void){};
    void appendTail(const T& element);
    T deleteHead();

private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T> void CQueue<T>::appendTail(const T &element)
{
    stack1.push(element);
}

template <typename T>T CQueue<T>::deleteHead()
{
    if(stack2.size() <= 0){
        while (stack1.size()>0){
            T& data = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }

    if(stack2.size() == 0)
        throw new exception();

    T head = stack2.top();
    stack2.pop();

    return head;
}

int main()
{

    CQueue<int > myqueue;
    for (int i = 0; i < 5; ++i) {
        myqueue.appendTail(i);
    }
    for (int j = 0; j < 5; ++j) {
        int k = myqueue.deleteHead();
        cout<< k <<" ";
    }

}


