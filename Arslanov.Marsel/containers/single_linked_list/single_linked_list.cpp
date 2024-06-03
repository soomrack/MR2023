#include "single_linked_list.hpp"

using namespace single_linked_list;

Single_linked_list::Single_linked_list(std::initializer_list<data_type> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        Single_linked_list::push_back(*it);
    }
}

Single_linked_list::Single_linked_list(const Single_linked_list& other) {
    if (other.size == 0) {
        return;
    }
    Node* temp_other = other.head;
    while (temp_other != nullptr) {
        this->push_back(temp_other->get_data());
        temp_other = temp_other->get_next();
        ++this->size;
    }
}

Single_linked_list::~Single_linked_list() {
    if (size == 0) {
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        temp = head->get_next();
        delete head;
        head = temp;
    }
}

Single_linked_list& Single_linked_list::push_back(Node& node) {
    if (!get_size()) {
        node.set_next(nullptr);
        tail = &node;
        head = tail;
        ++size;

        return *this;
    }

    tail->set_next(&node);
    node.set_next(nullptr);
    tail = &node;
    ++size;

    return *this;
}

Single_linked_list& Single_linked_list::push_back(const data_type& value) {
    Node* node = new Node(value);
    Single_linked_list::push_back(*node);
    return *this;
}

Single_linked_list& Single_linked_list::push_front(Node& node) {
    if (!get_size()) {
        push_back(node);

        return *this;
    }

    node.set_next(head);
    head = &node;
    ++size;

    return *this;
}

Single_linked_list& Single_linked_list::push_front(const data_type& value) {
    Node* node = new Node(value);
    Single_linked_list::push_front(*node);
    return *this;
}

Single_linked_list& Single_linked_list::pop_front() {
    if (!get_size()) {
        return *this;
    }

    Node* temp = head->get_next();
    delete head;
    head = temp;
    --size;

    return *this;
}

Single_linked_list& Single_linked_list::pop_back() {
    if (!get_size()) {
        return *this;
    }
    if (head == tail) {
        pop_front();
        return *this;
    }
    Node* temp = head;
    while (temp->get_next() != tail) {
        temp = temp->get_next();
    }
    delete tail;
    tail = temp;
    tail->set_next(nullptr);
    --size;

    return *this;
}

void Single_linked_list::remove(size_t idx) {
    if (idx >= size) {
        // throw exeption
    }
    if (idx == 0) {
        pop_front();
        return;
    }
    Node* temp = head;
    for (size_t index = 0; index < idx - 1; ++index) {
        temp = temp->get_next();
    }
    Node* node_to_delete = temp->get_next();
    temp->set_next(temp->get_next()->get_next());
    delete node_to_delete;
    --size;
}

void Single_linked_list::insertt(size_t idx, const data_type& value) {
    if (idx > size) {
        // throw exeption
    }
    if (idx == size) {
        push_back(value);
        return;
    }
    if (idx == 0) {
        push_front(value);
        return;
    }
    Node* new_node = new Node(value);
    Node* temp = head;
    for (size_t index = 0; index < idx - 1; ++index) {
        temp = temp->get_next();
    }
    new_node->set_next(temp->get_next());
    temp->set_next(new_node);
    ++size;
}