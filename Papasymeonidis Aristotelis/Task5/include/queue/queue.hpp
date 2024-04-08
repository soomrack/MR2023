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
    void pop_first();
    void pop_head();
    void pop_element(size_t index);
    void print() const;
    void push_element(size_t index, const T& value);
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
    
    do
    {
        if(current_node->priority > current_node->next->priority){
            head = current_node->next;
            head->next = current_node;
            current_node -> next = current_node -> next -> next;
            previously = head; 
        }

    } while (current_node->next != nullptr || current_node->priority > current_node->next->priority)
    {
        previously->next = current_node->next;
        current_node -> next = current_node -> next -> next;
        previously = previously->next;
    }
   }
   
        
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

template<typename T>
void queue<T>::pop_first() {
    queue_node<T>*next_ptr = head->next;
    next_ptr->preview = nullptr;
    delete[] head;
    head = next_ptr;
}


template<typename T>
void queue<T>::pop_head(){
    queue_node<T>*next_ptr = head->next;
    delete[] head;
    head = next_ptr;
}

template<typename T>
void queue<T>::pop_element(size_t index){
    if(index == 0) {
        pop_head();
        return;
    }
    queue_node<T>* current_ptr = head;
    for(size_t current_idx = 1; current_idx < index; ++current_idx) {
        current_ptr = current_ptr->next;
     }
    if(current_ptr->next->next != nullptr) {
        queue_node<T>*next_ptr = current_ptr->next;
        current_ptr->next = current_ptr->next->next;
        current_ptr->next->preview = current_ptr;
        delete[] next_ptr;
    }else {
        std::cout<<"Error! This element is the last one"<<std::endl;
     }
}

template<typename T>
void queue<T>::push_element(size_t index, const T& value) {
    if(index == 0) {
        push_head(value);
        return;
    }

    queue_node<T>* current_ptr = head;
    for(size_t current_idx = 1; current_idx < index - 1; ++current_idx) {
        if(current_ptr == nullptr) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }
        current_ptr = current_ptr->next;
    }

    if(current_ptr != nullptr) {
        queue_node<T>* next_ptr = new queue_node<T>{current_ptr, value, current_ptr->next};
        current_ptr->next = next_ptr;
    } else {
        std::cout << "Unknown error" << std::endl;
    }
}

#endif //QUEUE_HPP
