#include <iostream>


class Node {
public:
    int data;
    Node* next;
};


class Priority_queue {
private:
    Node* tail;

public:
    Priority_queue(): tail(nullptr) {};
    ~Priority_queue();
    void print_queue();
    void push(int value);
    int pop();
};    


Priority_queue:: ~Priority_queue()
{
    while (tail != nullptr){
        Node* temporary = tail;
        tail = tail->next;
        delete temporary;
    }
}


void Priority_queue:: push(int value)
{
    Node* new_element = new Node();
    if (tail == nullptr || value > tail->data){
        new_element->data = value;
        new_element->next = tail;
        tail = new_element;
    } else {
        Node* temporary = tail;
        while(value < tail->next->data){
            tail= tail->next;
        }

        new_element->next = tail->next;
        tail->next = new_element;
        new_element->data = value;
        tail = temporary;
    }
}


int Priority_queue:: pop()
{
    Node* temporary = tail;
    while(tail->next->next != nullptr)
        tail = tail->next;

    int buffer = tail->next->data;
    delete tail->next;
    tail->next = nullptr;
    tail = temporary;
    return buffer;
}


void Priority_queue:: print_queue()
{
    Node* temporary = tail;
    while(tail != nullptr){
        std::cout<<tail->data<<"  ";
        tail = tail->next;
    }
    std::cout<<std::endl;

    tail = temporary;
}


int main()
{
    Priority_queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(4);
    queue.push(3);
    queue.push(5);
    queue.print_queue();

    queue.pop();
    queue.print_queue();

    queue.pop();
    queue.pop();
    queue.print_queue();
}
