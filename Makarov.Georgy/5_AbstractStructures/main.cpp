#include <dynamic_array.h>
#include <linked_list.h>
#include <queue.h>

int main() {
    // Dynamic array example
    DynamicArray array(20, 24);
    for (size_t i = 0; i < array.get_size(); i++)
        array.set(i, int(i * i));

    DynamicArray copy_array(array);
    copy_array.resize(24, 28);

    array.print();
    copy_array.print();

    // Linked list example
    LinkedList linked_list;

    // Queue example
    Queue queue;

    return 0;
}
