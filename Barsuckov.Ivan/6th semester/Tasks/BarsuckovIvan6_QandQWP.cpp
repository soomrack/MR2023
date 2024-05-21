#include <iostream>
#include <string.h>
#include <string>


typedef int ArrayItem;


class queue_item {
public:
    int priority;
    ArrayItem data;
    queue_item* next;
    queue_item* previous;
};


class queue {
private:
    queue_item* head;
    queue_item* tail;

    void ranking();
    void swap_elements(queue_item* cur, queue_item* next);
    void swap_head(queue_item* cur, queue_item* next);
    void swap_tail(queue_item* cur, queue_item* next);
    void swap_head_and_tail(queue_item* cur, queue_item* next);
public:
    queue();
    ~queue();
    void clear();
    size_t get_size();
    void push(ArrayItem value, int priority);
    ArrayItem pop();
    void print();
    void print_with_priority();
};


class queue_exception : public std::exception {
private:
    std::string msg;
public:
    queue_exception(std::string msg) : msg{ msg } {}
    std::string get_message() const { return msg; }
};

queue_exception NULL_HEAD("Your queue is empty");


queue::queue()
{
    head = NULL;
    tail = NULL;
}


void queue::clear()
{
    if (head == NULL) return;

    ArrayItem trash = 0;

    do {
        trash = pop();
    } while (head != NULL);
}


queue::~queue()
{
    clear();
}


void queue::print()
{
    if (head == NULL) throw NULL_HEAD;

    queue_item* buff = head;

    while (buff != NULL) {
        std::cout << buff->data << " ";
        buff = buff->next;
    }

    std::cout << std::endl;
}


//print with priority class
void queue::print_with_priority()
{
    if (head == NULL) throw NULL_HEAD;

    queue_item* buff = head;

    while (buff != NULL) {
        std::cout << buff->data << "[" << buff->priority << "] ";
        buff = buff->next;
    }

    std::cout << std::endl;
}


size_t queue::get_size()
{
    if (head == NULL) throw NULL_HEAD;

    queue_item* buff = head;
    size_t counter = 0;

    while (buff != NULL) {
        buff = buff->next;
        counter++;
    }

    return counter;
}


void queue::swap_head(queue_item* cur, queue_item* next)
{
    cur->next = next->next;
    next->previous = NULL;

    next->next->previous = cur;

    next->next = cur;
    cur->previous = next;

    head = next;
}


void queue::swap_tail(queue_item* cur, queue_item* next)
{
    cur->next = NULL;
    next->previous = cur->previous;

    cur->previous->next = next;

    next->next = cur;
    cur->previous = next;

    tail = cur;
}


void queue::swap_head_and_tail(queue_item* cur, queue_item* next)
{
    cur->next = NULL;
    next->previous = NULL;

    next->next = cur;
    cur->previous = next;

    head = next;
    tail = cur;
}


void queue::swap_elements(queue_item* cur, queue_item* next)
{
    if ((cur == head) && (next == tail)) {
        swap_head_and_tail(cur, next);
        return;
    }

    if (cur == head) {
        swap_head(cur, next);
        return;
    }

    if (next == tail) {
        swap_tail(cur, next);
        return;
    }

    cur->next = next->next;
    next->next->previous = cur;

    next->previous = cur->previous;
    cur->previous->next = next;

    next->next = cur;
    cur->previous = next;
}


void queue::ranking()
{
    queue_item* counter = head;

    while (counter->next != NULL) {
        if (counter->priority >= counter->next->priority) {
            return;
        }

        swap_elements(counter, counter->next);
    }
}


void queue::push(ArrayItem value, int priority)
{
    queue_item* buf = new queue_item;
    buf->data = value;
    buf->priority = priority;
    buf->next = NULL;
    buf->previous = NULL;

    if (head == NULL) {
        head = buf;
        tail = head;
    }
    else {
        head->previous = buf;
        buf->next = head;
        head = buf;

        ranking();
    }
}


ArrayItem queue::pop()
{
    if (head == NULL) throw NULL_HEAD;

    ArrayItem pop_data = head->data;

    if (head == tail) {
        head = NULL;
        tail = NULL;
        return pop_data;
    }

    queue_item* last = tail;

    pop_data = last->data;

    tail = last->previous;
    last->data = 0;
    tail->next = NULL;

    return pop_data;
}


int main()
{
    queue qqq;

    qqq.push(7, 3);
    qqq.push(4, 6);
    qqq.push(8, 0);
    qqq.push(9, 1);
    qqq.push(0, 0);

    qqq.print();
    qqq.print_with_priority();

    std::cout << "Queue's size is " << qqq.get_size() << std::endl;

    std::cout << qqq.pop() << std::endl;
    std::cout << qqq.pop() << std::endl;
    std::cout << qqq.pop() << std::endl;

    qqq.print();
    qqq.print_with_priority();
}