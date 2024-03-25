#include <dynamic_array.h>
#include <linked_list.h>
#include <doubly_linked_list.h>
#include <stack.h>
#include <queue.h>

int main() {
    // Dynamic array example
    std::cout << "Dynamic array:" << std::endl;

    DynamicArray array(20, 24);
    for (size_t i = 0; i < array.get_size(); i++)
        array.set(i, int(i * i));

    DynamicArray array_copied(array);
    array_copied.resize(24, 28);

    array.print();
    array_copied.print();


    // Singly linked list example
    std::cout << std::endl << "Singly linked list:" << std::endl;

    LinkedList list;
    for (size_t i = 10; i < 17; i++)
        list.push_back(int(i - 3));

    LinkedList list_moved = std::move(list);
    list_moved.insert(2, -5);
    list_moved.remove(4);
    list_moved.print();

    list_moved.pop_back();
    list_moved.print();

    std::cout << list_moved.get(3) << std::endl;


    // Doubly linked list example
    std::cout << std::endl << "Doubly linked list:" << std::endl;

    DoublyLinkedList doubly_list;
    for (size_t i = 5; i < 12; i++)
        doubly_list.push_head(int((i - 3) * (i + 3)));

    DoublyLinkedList doubly_list_copied(doubly_list);
    doubly_list_copied.insert(2, -15);
    doubly_list_copied.remove(4);
    doubly_list_copied.print();

    doubly_list_copied.pop_back();
    doubly_list_copied.print();

    std::cout << doubly_list_copied.get(3) << std::endl;


    // Stack example
    std::cout << std::endl << "Stack:" << std::endl;

    Stack stack;
    for (size_t i = 0; i < 20; i++) {
        stack.push(int(i * 2));
        std::cout << stack.top() << "\t";
    }
    std::cout << std::endl;

    Stack stack_moved = std::move(stack);
    for (size_t i = 0; i < 20; i++) {
        stack_moved.pop();
        std::cout << stack_moved.size() << "\t";
    }
    std::cout << std::endl;


    // Queue example
    std::cout << std::endl << "Queue:" << std::endl;

    Queue queue;
    for (size_t i = 90; i < 99; i++)
        queue.enqueue(int(i));
    queue.print_queue();

    Queue queue_copied(queue);
    for (size_t i = 0; i < 8; i++) {
        queue_copied.dequeue();
        std::cout << queue_copied.front() << "\t";
    }
    std::cout << std::endl;

    queue.enqueue(10);
    queue.enqueue(20, 2);
    queue.enqueue(30);
    queue.enqueue(40, 1);
    queue.enqueue(50, 2);
    queue.print_queue();

    return 0;
}
