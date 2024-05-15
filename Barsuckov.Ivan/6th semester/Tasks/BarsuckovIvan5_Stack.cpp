#include <iostream>
#include <string.h>
#include <string>


typedef int ArrayItem;


class stack_item {
public:
    ArrayItem data;
    stack_item* next;
};


class stack {
private:
    stack_item* head;
public:
    stack();
    ~stack();
    ArrayItem peak();
    size_t size();
    void push(ArrayItem value);
    ArrayItem pop();
    int empty();
    void clear();
    void pop_all();
    void print_stack();
};


class stack_exception : public std::exception {
private:
    std::string msg;
public:
    stack_exception(std::string msg) : msg{ msg } {}
    std::string get_message() const { return msg; }
};

stack_exception NULL_HEAD("Stack is empty");


stack::stack()
{
    head = NULL;
}


void stack::clear()
{
    if (head == NULL) return;

    ArrayItem trash = 0;

    do {
        trash = pop();
    } while (head != NULL);
}


stack::~stack()
{
    clear();
}


void stack::print_stack()
{
    stack_item* buff = head;

    while (buff != NULL) {
        std::cout << buff->data << " ";
        buff = buff->next;
    }

    std::cout << std::endl;
}


ArrayItem stack::peak()
{
    return head->data;
}


size_t stack::size()
{
    if (head == NULL) throw NULL_HEAD;

    stack_item* buff = head;
    size_t counter = 0;

    while (buff != NULL) {
        buff = buff->next;
        counter++;
    }

    return counter;
}


void stack::push(ArrayItem value)
{
    stack_item* buf = new stack_item;
    buf->data = value;
    buf->next = NULL;

    if (head == NULL) head = buf;
    else {
        buf->next = head;
        head = buf;
    }
}


ArrayItem stack::pop()
{
    if (head == NULL) throw NULL_HEAD;

    ArrayItem pop_data = head->data;

    head->data = 0;
    head = head->next;

    return pop_data;
}


void stack::pop_all()
{
    if (head == NULL) throw NULL_HEAD;

    ArrayItem buf = 0;

    do {
        buf = pop();
        std::cout << buf << " ";
    } while (head != NULL);

    std::cout << std::endl;
}


int stack::empty()
{
    if (head == NULL) return 1;
    else return 0;
}


int main()
{
    stack stack;

    stack.push(456);
    stack.push(2);
    stack.push(47);
    stack.push(4);

    stack.print_stack();

    std::cout << "Size is " << stack.size() << std::endl;

    std::cout << "Head is " << stack.peak() << std::endl;

    std::cout << stack.pop() << std::endl;

    stack.print_stack();

    std::cout << stack.empty() << std::endl;

    stack.pop_all();

    std::cout << stack.empty() << std::endl;
}