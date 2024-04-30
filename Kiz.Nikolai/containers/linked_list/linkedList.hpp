#include "abstractContainer.hpp"
#include "listNode.hpp"
#include <utility>

template<typename T>
class SingleLinkedList: public AbstractContainer<T> {

    friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T>& list) {
        SLLNode<T>* item = list._head;
        os << "[ ";
        if (list._sz == 0) {return os << "empty ]\n";}
        while (item != nullptr) {
            os << *item;
            item = &item->next();
        }
        return os << "]\n";
    }

private:

    SLLNode<T>* _head{nullptr};
    SLLNode<T>* _tail{nullptr};
    size_t _sz{0};
    void swap(AbstractContainer<T>& other) override;

public:

    explicit SingleLinkedList(const T& value);
    SingleLinkedList(SingleLinkedList<T>& copy);
    SingleLinkedList(SingleLinkedList<T>&& copy_rvalue);
    SingleLinkedList(std::initializer_list<T> l);
    SingleLinkedList() = default;
    ~SingleLinkedList();
    SingleLinkedList<T>& operator=(SingleLinkedList<T> other);

    void push_front(const T& value);  
    void push_back(const T& value) override;  
    void insert(size_t index, const T& value) override;  
    T pop_front();  
    T pop_back() override;  
    T pop_at(const size_t idx);  
    void clear() override;  
    

    inline size_t size() const {return _sz;}
    SLLNode<T>& operator[](const size_t idx);
    const SLLNode<T>& operator[](const size_t idx) const;
    
};  //  class SingleLinkedList


template<typename T>
SingleLinkedList<T>::SingleLinkedList(const T& value): _head{new SLLNode<T>(value)}, _tail{_head}, _sz{1} {}


template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    while (_head) {
        SLLNode<T>* temp = _head->_next;
        delete _head;
        _head = temp;
    }
}

template<typename T>
void SingleLinkedList<T>::swap(AbstractContainer<T>& other) {
    std::swap(_head, dynamic_cast<SingleLinkedList<T>&>(other)._head);
    std::swap(_tail, dynamic_cast<SingleLinkedList<T>&>(other)._tail);
    std::swap(_sz, dynamic_cast<SingleLinkedList<T>&>(other)._sz); 
}


template<typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>& copy): SingleLinkedList(copy._head->_data) {
    SLLNode<T>* copy_node = copy._head->_next;
    while (copy_node) {
        push_back(copy_node->_data);
        copy_node = copy_node->_next;
    }

}

template<typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T>&& copy_rvalue):   _head(copy_rvalue._head),
                                                                             _tail{copy_rvalue._tail},
                                                                            _sz{copy_rvalue._sz} 
                                                                            {
        copy_rvalue._head = nullptr;
        copy_rvalue._tail = nullptr;
        copy_rvalue._sz = 0;
}


template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList<T>other) {
    swap(other);
    return *this;
}


template<typename T>
SLLNode<T>& SingleLinkedList<T>::operator[](const size_t idx) {
    return const_cast<SLLNode<T>&>(std::as_const(*this)[idx]);
}


template<typename T>
const SLLNode<T>& SingleLinkedList<T>::operator[](const size_t idx) const {
    if (idx >= _sz) throw std::runtime_error("Bad index.");
    
    SLLNode<T>* node = _head;
    for (size_t i = 0; i < idx; ++i) {
        node = node->_next;
    }
    return *node;
}


template<typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> l) {
    for (T value: l) {
        push_back(value);
    }
}


template<typename T>
void SingleLinkedList<T>::push_back(const T& value) {
    if (_sz == 0) {
        _head = new SLLNode<T>(value);
        _tail = _head;
    }
    else {
        _tail->_next = new SLLNode<T>(value);
        _tail = _tail->_next;
    }
    ++_sz;
}


template<typename T>
void SingleLinkedList<T>::insert(size_t idx, const T& value) {
    if (idx > _sz) throw std::runtime_error("Bad insertion index.");
    if (idx == 0) return push_front(value);
    if (idx == _sz) return push_back(value);

    SLLNode<T>* new_item = new SLLNode<T>(value, &((*this)[idx]));
    (*this)[idx-1]._next = new_item;
    ++_sz;
}


template<typename T>
void SingleLinkedList<T>::push_front(const T& value) {
    if (_sz == 0) return push_back(value);

    SLLNode<T>* new_value = new SLLNode<T>(value, _head);
    _head = new_value;
    ++_sz;
}


template<typename T>
T SingleLinkedList<T>::pop_front() {
    if (_sz == 0) throw std::runtime_error("Pop from empty list.");

    SLLNode<T>* new_front = _head->_next;
    T value = _head->_data;
    delete _head;
    _head = new_front;

    --_sz;
    if (_sz == 0) _tail = nullptr;
    return value;
}


template<typename T>
T SingleLinkedList<T>::pop_back() {
    if (_sz == 0) throw std::runtime_error("Pop from empty list.");
    if (_sz == 1) return pop_front();

    SLLNode<T>* new_last = &(*this)[_sz-2];
    T value = _tail->_data;
    new_last->_next = nullptr;
    delete _tail;
    _tail = new_last;

    --_sz;
    return value;
}


template<typename T>
T SingleLinkedList<T>::pop_at(size_t idx) {
    if (idx == 0) return pop_front();
    if (idx == _sz-1) return pop_back();

    SLLNode<T>* prev_item = &(*this)[idx-1];
    SLLNode<T>* this_item = &(*this)[idx];
    T pop_value = this_item->_data;
    prev_item->_next = this_item->_next;
    delete this_item;

    --_sz;
    return pop_value;
}


template<typename T>
void SingleLinkedList<T>::clear() {
    while (_head) pop_back();
}

