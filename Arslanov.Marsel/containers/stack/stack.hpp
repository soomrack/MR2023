#pragma once

#include "single_linked_list.hpp"

using namespace single_linked_list;

class Stack : private Single_linked_list
{
public:
    Stack() = default;
    Stack(const Stack& other) = default;
    ~Stack() = default;

    Stack& push(const data_type& data) {
        push_back(data);

        return *this;
    };

    Stack& pop() {
        if (!get_size()) {
            // throw exeption
        }
        pop_back();

        return *this;
    };

    data_type top() {
        if (!get_size()) {
            // throw exeption
        }

        return tail->get_data();
    };
};