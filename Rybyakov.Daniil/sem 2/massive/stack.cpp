#include <iostream>


template<typename T>
class Node {
private:
    template<typename> friend class Stack;
    Node* next;
public:
    Node(T _val) : val(_val), next(nullptr) {}
    T val;
};


template<typename T>
class Stack {
private:
    Node<T>* st;
    Node<T>* last;
public:
    Stack() : st(nullptr), last(nullptr) {}
    bool is_empty();
    void push(T _val);
    void print();
    void pop();
};


template<typename T>
bool Stack<T>::is_empty() {
    return st == nullptr;
}


template<typename T>
void Stack<T>::push(T _val) {
    Node<T>* el = new Node<T>(_val);
    if (is_empty()) {
        st = el;
        last = el;
        return;
    }
    el->next = st;
    st = el;
}


template<typename T>
void Stack<T>::print() {
    if (is_empty()) {
        std::cout << "stack is empty" << std::endl;
        return;
    }
    std::cout << st->val << std::endl;
}


template<typename T>
void Stack<T>::pop() {
    if (is_empty()) return;
    Node<T>* el = st;
    st = el->next;
    delete el;
}



int main() {
    Stack<int> A;
    A.push(3);
    std::cout << "is empty? " << A.is_empty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}