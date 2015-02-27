#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

template <class T>
class Stack{
    private:
        T *stk;
    public:
        int top, size;
        Stack(void);
        Stack(int);
        bool empty(void);
        bool full(void);
        void push(T);
        T pop(void);
        void printTopOfStack(void);
        void clearStack(void);
        void eval(string&);

};

template <class T>
Stack<T>::Stack(void)
{
    size = 20;
    top = -1;
    stk = new T[size]; //Carved out of the heap an array stk[20]
}

template <class T>
Stack<T>::Stack(int setsize)
{
    size = setsize;
    top = -1;
    stk = new T[size]; //Carved out of the heap an array stk[setsize]
}

template <class T>
bool Stack<T>::empty()
{
    if (top <= -1)
        return true;
    else
        return false;
}

template <class T>
bool Stack<T>::full()
{
    int temp = size-1;
    if (top >= temp)
        return true;
    else
        return false;
}

template <class T>
void Stack<T>::push(T data)
{
    if (full())
        cout << "\nOh Dear Watson! The stack has overflown!\n";
    else
    {
        ++top;
        stk[top] = data;
    }
}

template <class T>
T Stack<T>::pop()
{T static nothing;
    if (empty())
    {
        cout << "\nOh Dear Watson! The stack has underflown!\n";
        return nothing;
    }

    else
        return stk [top--];
}

template <class T>
void Stack<T>::printTopOfStack()
{
        if (empty())
        {
            cout << "\nOh Dear Watson! The stack has underflown!\n";
        }
        else
        {
            //for (int i=0; i<size; i++)
                cout << stk[0] << endl;
        }
}

template <class T>
void Stack<T>::clearStack()
{
    if(empty())
        cerr << "Stack underflow." << endl;
    else
    {
        top = -1;
    }
}


char * nextToken(string &expr)
{
    std::string tokenl;
    char * token;
    char * writable = new char[expr.size() + 1];
    std::copy(expr.begin(),expr.end(),writable);
    writable[expr.size()] = '/0';
    tokenl = std::string(strtok(writable,","));
    token = strtok(writable,",");
    int tokenLength = tokenl.length();
    expr.erase(0,(tokenLength+1));
    return token;
}

template <class T>
void Stack<T>::eval(string &expr)
{
    int t1,t2;
    char * token;
    token = nextToken(expr);
    while(token[0]!='!')
    {
       if ((token[0]>=48) && (token[0]<=57))
        {
            push(atoi(token));
        }
        else
        {
        t2 = pop();
        t1 = pop();
            switch(token[0])
            {
                case '-':
                    push(t1-t2);
                    break;
                case '+':
                    push(t1+t2);
                    break;
                case '*':
                    push(t1*t2);
                    break;
                case '/':
                    if(t2!=0)
                        push(t1/t2);
                    else
                    {
                        cerr << "Division by zero error" << endl;
                        return;
                    }
                    break;
                default: cout << "Please input a valid operator into the expression string" << endl; break;
            }
        }
        token = nextToken(expr);
    }
    printTopOfStack();
    clearStack();
}
