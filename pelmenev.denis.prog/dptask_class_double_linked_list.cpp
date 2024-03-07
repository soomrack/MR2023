#include <iostream>
#include <math.h>
#include <string.h>
#include <string>


typedef int ArrayItem;


class double_linked_list_item {
public:
    ArrayItem data;
    double_linked_list_item* next;
    double_linked_list_item* previous;  
};


class double_linked_list {
private:
    double_linked_list_item* head;
    double_linked_list_item* tail;
public:
    double_linked_list();
    size_t get_size();
    ArrayItem get_element(size_t position);
    void swap_data(double_linked_list_item* el_one, double_linked_list_item* el_two);
    void push_back(ArrayItem value);
    void pop_back();
    void push_at(size_t position, ArrayItem value);
    void pop_head();
    void pop_at(size_t position);
    double_linked_list_item* counter(size_t position);
    void print_list();
public:
    void sort_bubble();
    void sort_insertion();
};


class double_linked_list_exception: public std::exception {
private:
    std::string msg;
public:
    double_linked_list_exception(std::string msg) : msg{msg} {}
    std::string get_message() const { return msg; }
};

double_linked_list_exception OUT_OF_RANGE("Position is out of range\n");
double_linked_list_exception NULL_HEAD("Your list is empty");


double_linked_list::double_linked_list()
{
    head = NULL;
    tail = head;
}


void double_linked_list::print_list()
{
    double_linked_list_item* buff = head;

    while (buff != NULL) {
        std::cout << buff->data << " ";
        buff = buff->next;
    }

    std::cout << std::endl;
}


double_linked_list_item* double_linked_list::counter(size_t position)
{
    double_linked_list_item* before = head;
    size_t counter = 0;

    while (counter < position) {
        before = before->next;
        ++counter;
    }

    return before;
}


size_t double_linked_list::get_size()
{
    if (head == NULL) throw NULL_HEAD;

    double_linked_list_item* buff = head;
    size_t counter = 0;

    while (buff != NULL) {
        buff = buff->next;
        counter++;
    }

    return counter;
}

//position starts from zero
ArrayItem double_linked_list::get_element(size_t position)
{
    if (position >= get_size()) throw OUT_OF_RANGE;

    double_linked_list_item* current;

    current = counter(position);

    return current->data;
}


void double_linked_list::swap_data(double_linked_list_item* el_one, double_linked_list_item* el_two)
{
    el_one->data = el_one->data ^ el_two->data;
    el_two->data = el_one->data ^ el_two->data;
    el_one->data = el_two->data ^ el_one->data;
}


void double_linked_list::push_back(ArrayItem value)
{
    double_linked_list_item* buf = new double_linked_list_item;
    buf->data = value;
    buf->next = NULL;
    buf->previous = NULL;

    if (head == NULL) {
        head = buf;
        tail = head;
    } else {
        double_linked_list_item* count = head;

        while (count->next != NULL)
            count = count->next;
        
        count->next = buf;
        buf->previous = count;
        tail = buf;
    }
}

//position starts from zero
void double_linked_list::push_at(size_t position, ArrayItem value)
{
    if (position >= get_size()) {
        push_back(value);
        return;
    }

    double_linked_list_item* buf = new double_linked_list_item;
    buf->data = value;
    buf->next = NULL;
    buf->previous = NULL;

    if (position == 0) {
        swap_data(head, buf);
        buf->next = head->next;
        head->next->previous = buf;
        buf->previous = head;
        head->next = buf;
    } else {
        double_linked_list_item* before;

        before = counter(position - 1);
        
        buf->next = before->next;
        buf->previous = before;
        before->next->previous = buf;
        before->next = buf;
    }
}


void double_linked_list::pop_back()
{
    if (head == NULL) throw NULL_HEAD;

    double_linked_list_item* last = tail;

    tail = last->previous;
    last->data = 0;
    tail->next = NULL;
}


void double_linked_list::pop_head()
{
    if (get_size() == 1) {
        head = NULL;
        return;
    }

    double_linked_list_item* next = head->next;

    swap_data(head, next);

    head->next = next->next;
    next->next->previous = head;
    next->data = 0;
    next->next = NULL;
    next->previous = NULL;
}

//position starts from zero
void double_linked_list::pop_at(size_t position)
{
    if (position >= get_size()) throw OUT_OF_RANGE;

    if (position == 0) {
        pop_head();
        return;
    }

    double_linked_list_item* current;

    current = counter(position);

    if (current == tail) {
        pop_back();
        return;
    }

    double_linked_list_item* before = current->previous;
    
    before->next = current->next;
    current->next->previous = before;
    current->data = 0;
    current->next = NULL;
    current->previous = NULL;
}


void double_linked_list::sort_bubble()
{
    size_t size = get_size();

    double_linked_list_item* buff;
    double_linked_list_item* next;

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


void double_linked_list::sort_insertion()
{
    size_t size = get_size();

    double_linked_list_item* buff;
    double_linked_list_item* prev;

    for (size_t sorted = 1; sorted < size; ++sorted) {
        buff = counter(sorted);
        prev = buff->previous;

        for (size_t idx = sorted; idx > 0; --idx) {
            if (buff->data < prev->data) 
                swap_data(buff, prev);
            else break;

            buff = buff->previous;
            prev = buff->previous;
        }
    }
}


int main()
{
    double_linked_list list;

    list.push_back(8);
    list.push_back(6);
    list.push_back(2);
    list.push_back(15);
    list.push_back(1);

    list.print_list();

    std::cout << list.get_element(3) << std::endl;

    list.pop_back();

    list.push_at(2, 10);

    list.pop_at(4);

    list.print_list();

    //list.sort_bubble();
    list.sort_insertion();

    list.print_list();
}