#include "abstractContainer.hpp"
#include "listNode.hpp"
#include <utility>

template<typename T>
class DoublyLinkedList: public AbstractContainer<T> {

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        DLLNode<T>* item = list._head;
        os << "[ ";
        if (list._sz == 0) {return os << "empty ]\n";}
        while (item != nullptr) {
            os << *item;
            item = &item->next();
        }
        return os << "]\n";
    }

private:
    DLLNode<T>* _head{nullptr};
    DLLNode<T>* _tail{nullptr};
    size_t _sz{0};
    void swap(AbstractContainer<T>& other) override;  //  done

public:

    explicit DoublyLinkedList(const T& value);  
    DoublyLinkedList(std::initializer_list<T> l);  
    DoublyLinkedList() = default;  
    DoublyLinkedList(DoublyLinkedList<T>& copy);  //  done
    DoublyLinkedList(DoublyLinkedList<T>&& copy_rvalue);  //  done
    ~DoublyLinkedList();  // done
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T> other);  //  done

    void push_back(const T& value) override;   
    void insert(size_t idx, const T& value) override;  
    T pop_back() override;  
    void clear() override;  // done

    void push_front(const T& value);  
    T pop_front();    
    T pop_at(const size_t idx);  
    

    inline size_t size() const {return _sz;}  
    DLLNode<T>& operator[](const size_t idx);  
    const DLLNode<T>& operator[](const size_t idx) const;  

};  //  class DoublyLinkedList



template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const T& value): _head{new DLLNode<T>(value)}, _tail{_head}, _sz{1} {}


template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    if (_sz == 0) {
        _head = new DLLNode<T>(value, nullptr, nullptr);
        _tail = _head;
    }
    else {
        _tail->_next = new DLLNode<T>(value, _tail, nullptr);
        _tail = _tail->_next;
    }
    ++_sz;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (_head) {
        DLLNode<T>* temp = _head->_next;
        delete _head;
        _head = temp;
    }
    
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> l) {
    for (T value: l) {
        push_back(value);
    }
}


template<typename T>
void DoublyLinkedList<T>::swap(AbstractContainer<T>& other) {
    std::swap(_head, dynamic_cast<DoublyLinkedList<T>&>(other)._head);
    std::swap(_tail, dynamic_cast<DoublyLinkedList<T>&>(other)._tail);
    std::swap(_sz, dynamic_cast<DoublyLinkedList<T>&>(other)._sz);
}


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>& other): DoublyLinkedList(other._head->_data) {
    DLLNode<T>* copy_node = other._head->_next;
    while (copy_node) {
        push_back(copy_node->_data);
        copy_node = copy_node->_next;
    }
}


template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& copy_rvalue):   _head(copy_rvalue._head),
                                                                            _tail(copy_rvalue._tail),
                                                                            _sz(copy_rvalue._sz)
                                                                            {
    copy_rvalue._head = nullptr;
    copy_rvalue._tail = nullptr;
    copy_rvalue._sz = 0;
}



template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T> other) {
    swap(other);
    return *this;
}


template<typename T>
void DoublyLinkedList<T>::insert(size_t idx, const T& value) {
    if (idx > _sz) throw std::runtime_error("Bad index for insertion.");

    if (idx == _sz) return push_back(value);
    DLLNode<T>* current_node = &((*this)[idx]);
    DLLNode<T>* prev_node = &((*this)[idx-1]);
    DLLNode<T>* new_node = new DLLNode<T>(value, prev_node, current_node);
    current_node->_prev = new_node;
    prev_node->_next = new_node;
    ++_sz;
}

template<typename T>
T DoublyLinkedList<T>::pop_back() {
    if (_sz == 0) throw std::runtime_error("Pop from empty list.");

    T value = _tail->_data;
    DLLNode<T>* new_tail = _tail->_prev;
    delete _tail;
    _tail = new_tail;
    if (_sz == 1) _head = nullptr;
    else _tail->_next = nullptr;

    --_sz;
    return value;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    while (_head) {
        pop_back();
    }
}


template<typename T>
const DLLNode<T>& DoublyLinkedList<T>::operator[](size_t idx) const {
    if (idx >= _sz) throw std::runtime_error("Bad index.");

    DLLNode<T>* node;
    if (idx >= _sz / 2) {
        node = _tail;
        for (size_t i = 0; i < _sz - (idx + 1); ++i)
            node = node->_prev;
    }
    else {
        node = _head;
        for (size_t i = 0; i < idx; ++i)
            node = node->_next;
    }

    return *node;
}

template <typename T>
DLLNode<T>& DoublyLinkedList<T>::operator[](size_t idx) {
    return const_cast<DLLNode<T>&>(std::as_const(*this)[idx]);
}


template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    if (_sz == 0) return push_back(value);

    DLLNode<T>* new_node = new DLLNode<T>(value, nullptr, _head);
    _head->_prev = new_node;
    _head = new_node;
} 


template<typename T>
T DoublyLinkedList<T>::pop_front() {
    if (_sz == 0) throw std::runtime_error("Pop from empty list.");
    if (_sz == 1) return pop_back();

    T value = _head->_data;
    DLLNode<T>* new_head = _head->_next;
    delete _head;
    _head = new_head;
    _head->_prev = nullptr;

    --_sz;
    return value;
}


template<typename T>
T DoublyLinkedList<T>::pop_at(size_t idx) {
    if (idx >= _sz) throw std::runtime_error("Bad pop index.");
    if (idx == 0) return pop_front();
    if (idx == _sz-1) return pop_back();

    DLLNode<T>* current_node = &(*this)[idx];
    T value = current_node->_data;
    current_node->_prev->_next = current_node->_next;
    current_node->_next->_prev = current_node->_prev;
    delete current_node;

    --_sz;
    return value;
}