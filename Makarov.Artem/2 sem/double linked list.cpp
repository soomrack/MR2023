﻿#include <iostream>


class Node 
{
public:
    int data;
    Node* prev;
    Node* next;

    Node(const int data, Node* prev = nullptr, Node* next = nullptr) : data(data), prev(prev), next(next) {}
};


class List 
{
private:
    Node* head;
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() { clear(); }

    void add_head(const int value);
    void add_tail(const int value);
    void delete_head();
    void delete_tail();

    int get_head_data();
    int get_tail_data();
    void clear();
};


void List::add_head(const int value) 
{
    if (head == nullptr) 
    {
        head = tail = new Node(value);
    }
    else 
    {
        Node* newNode = new Node(value, nullptr, head);
        head->prev = newNode;
        head = newNode;
    }
}


void List::add_tail(const int value) 
{
    if (tail == nullptr) 
    {
        head = tail = new Node(value);
    }
    else 
    {
        Node* newNode = new Node(value, tail, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}


void List::delete_head() 
{
    if (head == nullptr) 
    {
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) 
    {
        head->prev = nullptr;
    }
    else 
    {
        tail = nullptr;
    }
    delete temp;
}


void List::delete_tail() 
{
    if (tail == nullptr) 
    {
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) 
    {
        tail->next = nullptr;
    }
    else 
    {
        head = nullptr;
    }
    delete temp;
}


int List::get_head_data() 
{
    if (head != nullptr) 
    {
        return head->data;
    }
    else 
    {
        return 0; 
    }
}


int List::get_tail_data() 
{
    if (tail != nullptr) 
    {
        return tail->data;
    }
    else 
    {
        return 0; 
    }
}


void List::clear() 
{
    while (head != nullptr) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}


int main() 
{
    List list;
    list.add_head(7);
    list.add_head(18);
    list.add_head(3);
    list.add_tail(22);
    list.delete_head();
    list.delete_tail();
    list.clear();

    return 0;
}