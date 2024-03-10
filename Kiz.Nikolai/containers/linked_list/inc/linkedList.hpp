#include "linkedListNode.hpp"
#include <utility>

template<typename T>
class LinkedList {

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        LinkedListNode<T>* item = list.head;
        if (list.sz == 0) {return os << "empty\n";}
        while (item != nullptr) {
            os << *item;
            item = item->next();
        }
        return os << "\n";
    }

private:

    LinkedListNode<T>* head{nullptr};
    LinkedListNode<T>* tail{nullptr};
    size_t sz{0};

public:

    explicit LinkedList(const T& value);
    LinkedList(std::initializer_list<T> l);
    LinkedList() = default;
    ~LinkedList();


    void push_front(const T& value);  //  done
    void push_back(const T& value);  //  done
    void insert(size_t index, const T& value);  //  done
    T pop_front();  //  done
    T pop_back();  //  done
    T pop_at(const size_t idx);  //  done
    void clear();
    

    inline size_t size() const {return sz;}
    LinkedListNode<T>& operator[](const size_t idx);
    const LinkedListNode<T>& operator[](const size_t idx) const;
    
};  //  class LinkedList


template<typename T>
LinkedList<T>::LinkedList(const T& value):head{new LinkedListNode(value)}, tail{head}, sz{1} {}


template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> l) {
    for (T value: l) {
        push_back(value);
    }
}


template<typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        LinkedListNode<T>* temp = head->_next;
        delete head;
        head = temp;
    }
}


template<typename T>
void LinkedList<T>::push_back(const T& value) {
    if (sz == 0) {
        head = new LinkedListNode(value);
        tail = head;
    }
    else {
    tail->_next = new LinkedListNode(value);
    tail = tail->_next;
    }
    ++sz;
}


template<typename T>
LinkedListNode<T>& LinkedList<T>::operator[](const size_t idx) {
    return const_cast<LinkedListNode<T>&>(std::as_const(*this)[idx]);
}


template<typename T>
const LinkedListNode<T>& LinkedList<T>::operator[](const size_t idx) const {
        if (idx >= sz) throw std::runtime_error("Bad index.");
    LinkedListNode<T>* node = head;
    for (size_t i = 0; i < idx; ++i) {
        node = node->_next;
    }
    return *node;
}


template<typename T>
void LinkedList<T>::insert(size_t idx, const T& value) {
    if (idx > sz) throw std::runtime_error("Bad insert index.");
    if (idx == 0) return push_front(value);
    if (idx == sz) return push_back(value);
    LinkedListNode<T>* new_item = new LinkedListNode<T>(value, &((*this)[idx]));
    (*this)[idx-1]._next = new_item;
    ++sz;
}


template<typename T>
void LinkedList<T>::push_front(const T& value) {
    if (sz == 0) {
        push_back(value);
        return;
    }
    LinkedListNode<T>* new_value = new LinkedListNode<T>(value, head);
    head = new_value;
    ++sz;
}


template<typename T>
T LinkedList<T>::pop_front() {
    if (sz == 0) throw std::runtime_error("Pop from empty list.");
    LinkedListNode<T>* new_front = head->_next;
    T front_value = head->_data;
    delete head;
    head = new_front;
    --sz;
    if (sz == 0) tail = nullptr;
    return front_value;
}


template<typename T>
T LinkedList<T>::pop_back() {
    if (sz == 0) throw std::runtime_error("Pop from empty list.");
    if (sz == 1) return pop_front();
    LinkedListNode<T>* new_last = &(*this)[sz-2];
    T back_value = tail->_data;
    new_last->_next = nullptr;
    delete tail;
    tail = new_last;
    --sz;
    return back_value;
}


template<typename T>
T LinkedList<T>::pop_at(size_t idx) {
    if (idx == 0) return pop_front();
    if (idx == sz-1) return pop_back();
    LinkedListNode<T>* prev_item = &(*this)[idx-1];
    LinkedListNode<T>* this_item = &(*this)[idx];
    T pop_value = this_item->_data;
    prev_item->_next = this_item->_next;
    delete this_item;
    --sz;
    return pop_value;
}


template<typename T>
void LinkedList<T>::clear() {
    while (head) pop_back();
}