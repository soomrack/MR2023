#include <iostream>
#include <stdexcept>

class LinkedListItem {
public:
    int data;
    LinkedListItem* next;
};

class LinkedList {
private:
    LinkedListItem* head;
    LinkedListItem* walk_head;
public:
    LinkedList();
    LinkedList(const LinkedList& L);
    LinkedList(LinkedList&& L);
    ~LinkedList(); // Добавим деструктор для освобождения памяти
    void Push(int n);
    int Pop();
    void print();
    bool walk_next();
    void add_next(int n);
    void del_next();
};

LinkedList::LinkedList() {
    head = nullptr;
    walk_head = nullptr;
}

LinkedList::LinkedList(const LinkedList& L) {
    if (L.head == nullptr) {
        head = nullptr;
        walk_head = nullptr;
        return;
    }
    LinkedListItem* tmp_head = nullptr;
    for (LinkedListItem* tmp_idx = L.head; tmp_idx != nullptr; tmp_idx = tmp_idx->next) {
        LinkedListItem* tmp_item = new LinkedListItem;
        tmp_item->data = tmp_idx->data;
        tmp_item->next = nullptr;
        if (tmp_head == nullptr) {
            head = tmp_item;
            tmp_head = tmp_item;
        }
        else {
            tmp_head->next = tmp_item;
            tmp_head = tmp_item;
        }
    }
    walk_head = head;
}

LinkedList::LinkedList(LinkedList&& L) {
    head = L.head;
    walk_head = head;
    L.head = nullptr;
}

LinkedList::~LinkedList() {
    LinkedListItem* current = head;
    while (current != nullptr) {
        LinkedListItem* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::Push(int n) {
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) head = tmp;
    else {
        tmp->next = head;
        head = tmp;
    }
    walk_head = head;
}

int LinkedList::Pop() {
    if (head != nullptr) {
        int popped_value = head->data;
        LinkedListItem* tmp = head;
        head = head->next;
        walk_head = head;
        delete tmp;
        return popped_value;
    }
    else {
        throw std::runtime_error("List is empty");
    }
}

void LinkedList::print() {
    LinkedListItem* Tmp = head;
    while (Tmp != nullptr) {
        std::cout << Tmp->data << "\t";
        Tmp = Tmp->next;
    }
    std::cout << "\n";
}

bool LinkedList::walk_next() {
    if (walk_head->next != nullptr) {
        walk_head = walk_head->next;
        return true; // Успешное перемещение
    }
    else {
        return false; // Достигнут конец списка
    }
}

void LinkedList::add_next(int n) {
    LinkedListItem* tmp = new LinkedListItem;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr) {
        head = tmp;
        walk_head = head;
    }
    else {
        tmp->next = walk_head->next;
        walk_head->next = tmp;
    }
}

void LinkedList::del_next() {
    if (walk_head->next != nullptr) {
        walk_head->next->data = 0;
        walk_head->next = walk_head->next->next;
    }
}

int main() {
    LinkedList list;
    unsigned int choise, run = 1;
    int number;
    while (run) {
        std::cout << "выбор: ";
        std::cin >> choise;

        switch (choise) {
        case 0:
            run = 0;
            break;

        case 1:
            try {
                int popped_value = list.Pop();
                std::cout << "Извлечено: " << popped_value << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
            }
            break;

        case 2:
            std::cout << "число: ";
            std::cin >> number;
            list.Push(number);
            break;

        case 3:
            list.print();
            break;

        case 4:
            if (!list.walk_next()) {
                std::cout << "Достигнут конец списка" << std::endl;
            }
            break;

        case 5:
            list.walk_head = list.head; // Сброс walk_head на head
            break;

        case 6:
            std::cout << "число: ";
            std::cin >> number;
            list.add_next(number);
            break;

        case 7:
            list.del_next();
            break;

        default:
            printf("неправильный выбор\n");
            break;
        }
        list.print();
    }
    return 0;
}
