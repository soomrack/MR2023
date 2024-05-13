#include <iostream>

using namespace std;

class QueueNode
{
public:
    int data;
    int priority;
    QueueNode* next;

    QueueNode(int data, int prior) : data(data), next(nullptr), priority(prior){}
    ~QueueNode() {}
};

class PriorityQueue
{
private:
    QueueNode* head;
    QueueNode* tail;
    size_t size;

public:
    PriorityQueue(): head(nullptr), tail(nullptr), size(0) {}
    ~PriorityQueue();

    bool is_empty();
    size_t get_size();
    void push(int data, int prior);
    int pop();
    int get_head();
    void clear();
};

bool PriorityQueue::is_empty()
{
    return size == 0;
}

size_t PriorityQueue::get_size()
{
    return size;
}
 
void PriorityQueue::push(int data, int prior)
{
    QueueNode* element = new QueueNode(data, prior);
    if (is_empty() || prior < head->priority)
    {
        element->next = head;
        head = element;
        if (tail == nullptr)
            tail = element;
    }
    else
    {
        QueueNode* current = head;
        while(current->next != nullptr && prior > current->next->priority)
            current = current->next;
        element->next = current->next;
        current->next = element;
        if (element->next == nullptr)
            tail = element;
    }
    size++;
}

int PriorityQueue::pop(){
    if (is_empty())
        throw domain_error("Error: Queue is empty");
    QueueNode* element = head;
    int head_val = element->data;
    head = element->next;
    delete element;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    size--;

    return head_val;
}

int PriorityQueue::get_head(){
    if (is_empty())
       throw domain_error("Error: Queue is empty");   
    return head->data;
}

void PriorityQueue::clear() {
    QueueNode* current = head;
    while (current != nullptr) {
        QueueNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

PriorityQueue::~PriorityQueue()
{
    clear();
}


int main(){
    PriorityQueue Q;
    Q.push(1,2);
    Q.push(2,1);
    Q.push(3,3);
    cout << Q.get_head() << "\n";
    Q.pop();
    cout << Q.get_head() << "\n";
    Q.pop();
    cout << Q.get_head() << "\n";
    Q.push(1,2);
    Q.push(2,1);
    Q.push(3,3);
    Q.clear();
}