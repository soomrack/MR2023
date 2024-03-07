#include <iostream>
#include <math.h>
#include <string.h>
#include <string>


typedef int ArrayItem;


class linked_list_item {
public:
    ArrayItem data;
    linked_list_item* next;    
};


class linked_list {
private:
    linked_list_item* head;
public:
    linked_list();
    //~linked_list();
    size_t get_size();
    ArrayItem get_element(size_t position);
    void swap_data(linked_list_item* el_one, linked_list_item* el_two);
    void push_back(ArrayItem value);
    void pop_back();
    void push_at(size_t position, ArrayItem value);
    void pop_head();
    void pop_at(size_t position);
    void print_list();
public:
    void sort_bubble();
};


class linked_list_exception: public std::exception {
private:
    std::string msg;
public:
    linked_list_exception(std::string msg) : msg{msg} {}
    std::string get_message() const { return msg; }
};

linked_list_exception OUT_OF_RANGE("Position is out of range\n");
linked_list_exception NULL_HEAD("Your list is empty");


linked_list::linked_list()
{
    head = NULL;
}


/* linked_list::~linked_list()
{
    head->data = 0;
    head->next = NULL
} */


void linked_list::print_list()
{
    linked_list_item* buff = head;

    while (buff != NULL) {
        std::cout << buff->data << " ";
        buff = buff->next;
    }

    std::cout << std::endl;
}


size_t linked_list::get_size()
{
    if (head == NULL) throw NULL_HEAD;

    linked_list_item* buff = head;
    size_t counter = 0;

    while (buff != NULL) {
        buff = buff->next;
        counter++;
    }

    return counter;
}

//position starts from zero
ArrayItem linked_list::get_element(size_t position)
{
    if (position >= get_size()) throw OUT_OF_RANGE;

    linked_list_item* current = head;
    size_t counter = 0;

    while (counter < position) {
        current = current->next;
        ++counter;
    }

    return current->data;
}


void linked_list::swap_data(linked_list_item* el_one, linked_list_item* el_two)
{
    el_one->data = el_one->data ^ el_two->data;
    el_two->data = el_one->data ^ el_two->data;
    el_one->data = el_two->data ^ el_one->data;
}


void linked_list::push_back(ArrayItem value)
{
    linked_list_item* buf = new linked_list_item;
    buf->data = value;
    buf->next = NULL;

    if (head == NULL) head = buf;
    else {
        linked_list_item* count = head;

        while (count->next != NULL)
            count = count->next;
        
        count->next = buf;
    }
}

//position starts from zero
void linked_list::push_at(size_t position, ArrayItem value)
{
    if (position >= get_size()) {
        push_back(value);
        return;
    }

    linked_list_item* buf = new linked_list_item;
    buf->data = value;
    buf->next = NULL;

    if (position == 0) {
        swap_data(head, buf);
        buf->next = head->next;
        head->next = buf;
    } else {
        linked_list_item* previous = head;
        size_t counter = 0;

        while (counter < position - 1) {
            previous = previous->next;
            ++counter;
        }
        
        buf->next = previous->next;
        previous->next = buf;
    }
}


void linked_list::pop_back()
{
    if (head == NULL) throw NULL_HEAD;

    linked_list_item* last = head;

    while (last->next != NULL)
        last = last->next;
    
    linked_list_item* count = head;

    while (count->next != last)
        count = count->next;
    
    last->data = 0;
    count->next = NULL;
}


void linked_list::pop_head()
{
    if (get_size() == 1) {
        head = NULL;
        return;
    }

    linked_list_item* next = head->next;

    swap_data(head, next);

    head->next = next->next;
    next->data = 0;
    next->next = NULL;
}

//position starts from zero
void linked_list::pop_at(size_t position)
{
    if (position >= get_size()) throw OUT_OF_RANGE;

    if (position == 0) {
        pop_head();
        return;
    }

    linked_list_item* previous = head;
    size_t counter = 0;

    while (counter < position - 1) {
        previous = previous->next;
        counter++;
    }

    linked_list_item* current = head;

    while (previous->next != current)
        current = current->next;
    
    previous->next = current->next;
    current->data = 0;
    current->next = NULL;
}


void linked_list::sort_bubble()
{
    size_t size = get_size();

    linked_list_item* buff;
    linked_list_item* next;

    for (size_t sorted = size; sorted > 1; --sorted) {
        buff = head;
        next = head->next;

        for (size_t idx = 0; idx < sorted - 1; ++idx) {
            if (buff->data > next->data) swap_data(buff, next);

            buff = buff->next;
            next = buff->next;
        }
    }
}


int main()
{
    linked_list list;

    list.push_back(4);
    list.push_back(2);
    list.push_back(8);
    list.push_back(5);
    list.push_back(7);

    list.print_list();

    std::cout << "List's size is " << list.get_size() << std::endl;

    list.pop_back();

    list.push_at(2, 9);
    list.print_list();

    list.pop_at(2);
    list.print_list();

    list.push_at(1, 0);

    list.sort_bubble();

    list.print_list();

    std::cout << list.get_element(2) << std::endl;

    return 0;
}
