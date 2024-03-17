#include <dynamic_array.h>
#include <linked_list.h>
#include <doubly_linked_list.h>
#include <queue.h>

int main() {
    // Dynamic array example
    std::cout << "Dynamic array:" << std::endl;

    DynamicArray array(20, 24);
    for (size_t i = 0; i < array.get_size(); i++)
        array.set(i, int(i * i));

    DynamicArray copy_array(array);
    copy_array.resize(24, 28);

    array.print();
    copy_array.print();

    // Singly linked list example
    std::cout << std::endl << "Singly linked list:" << std::endl;

    LinkedList list;
    for (size_t i = 5; i < 12; i++)
        list.push_back(int(i - 3));

    LinkedList move_list = std::move(list);
    move_list.insert(2, 10);
    move_list.remove(4);
    move_list.print();

    move_list.pop_back();
    move_list.print();

    std::cout << move_list.get(3) << std::endl;


    // Doubly linked list example
    std::cout << std::endl << "Doubly linked list:" << std::endl;

    DoublyLinkedList double_list;

    // Queue example
    std::cout << std::endl << "Queue:" << std::endl;

    Queue queue;

    return 0;
}
