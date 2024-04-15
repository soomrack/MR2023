#include <iostream>

template <typename T>
class Stack
{
private:
    int arr[100];
    int top;

public:
    Stack();

public:
    void push(T value);
    T pop();
    T peek();
    bool is_empty()
};

template <typename T>
Stack<T>::Stack() : top(-1){};

template <typename T>
void Stack<T>::push(T value)
{
    if (top < 99){
        arr[++top] = value;
    }
    else{
        std::cout << "Stack overflow" << std::endl;
    }
}

template <typename T>
T Stack<T>::pop()
{
    if (top >= 0){
    return arr[top--];

    } else{
    std::cout << "С пуст" << std::endl;
    return 0;
    }
}


template <typename T>
T Stack<T>::pop()
{
if (top >= 0){
    return arr[top--];
}else{
    std::cout << "С пуст" << std::endl;
    return 0;
    }
}

template <typename T>
bool Stack<T>::is_empty()
{
    return top == -1;
}