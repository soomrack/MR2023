//
// Created by simeonidi03 on 25/3/24.
//
#ifndef QUEUE_HPP
#define QUEUE_HPP


template<typename T>
class queue_node {
public:
    int priority;
    T data;
    queue_node<T>* next;
    queue_node(const T& data) : priority(0), data(data), next(nullptr) {}
    queue_node(const T& data, queue_node<T>* next) : priority(0), data(data), next(next) {}
    queue_node(const int priority, const T& data, const queue_node<T>* next) : priority(priority), data(data), next(nullptr) {}
};


template<typename T>
class queue{
private:
    queue_node<T>* head;
    queue_node<T>* first;
    
    public:
    queue() : head(nullptr) {}
    ~queue();

    void push_node_queue(const T& value, const int priority);
    void print() const;
    queue_node<T>* pop_first_queue();
    void sort(queue_node<T>* previously, queue_node<T>* current);
};

template<typename T>
queue<T>::~queue() {
    while (head != nullptr) {
        queue_node<T>* del_node_ptr = head;
        head = head->next;
        delete del_node_ptr;
    }
}


template<typename T>
void queue<T>::sort(queue_node<T>* previously, queue_node<T>* current){
    head = current->next;
    head->next = current;
    current->next = current->next->next;
    previously = head; 
}


template<typename T>
void queue<T>::push_node_queue(const T& value, const int priority) 
{
    queue_node<T>* new_node = new queue_node<T>(priority, value, nullptr);
    if (head == nullptr) {
        head = new_node;
        first = new_node;
    } else {
        new_node->next = head;
        head = new_node;
        queue_node<T>* current_node = head;  
        queue_node<T>* previously = head;  
    
        if(current_node->priority > current_node->next->priority) sort(previously, current_node);
        
        while (current_node->next != nullptr || current_node->priority > current_node->next->priority){
            previously->next = current_node->next;
            current_node -> next = current_node -> next -> next;
            previously = previously->next;
        }
    }  
}


template<typename T>
queue_node<T>* queue<T>::pop_first_queue(){
    queue_node<T>* current_node = head;

    while (current_node->next != first)
    {
        current_node = current_node->next;
    }

    if(first->next != nullptr){
        delete[] first->next;
        first->next = nullptr;
    }
    first = current_node;

    return first->next;
}


template<typename T>
void queue<T>::print() const {
    node<T> *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


#endif //QUEUE_HPP
