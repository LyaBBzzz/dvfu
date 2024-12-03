#include <iostream>
#include <locale.h>

struct Node {
    int data;
    Node* prev;
    Node* next;
};

class List {
private:
    Node* head;
    Node* tail;

public:
    // Инициализация списка
    List() {
        head = nullptr;
        tail = nullptr;
    }

    // Освобождение памяти
    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Добавление элемента в начало
    void add(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        }
        else {
            tail = newNode;
        }

        head = newNode;
    }

    // Удаление всех вхождений заданного элемента
    void remove(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                current = current->next;
            }
        }
    }

    // Поиск элемента
    bool find(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Печать списка
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Указатель на голову списка
    Node* getHead() const {
        return head;
    }

    // Пересечение
    static List intersection(const List& list1, const List& list2) {
        List result;
        Node* current1 = list1.head;

        while (current1 != nullptr) {
            int value = current1->data;
            if (list2.find(value)) {
                result.add(value);
            }
            current1 = current1->next;
        }

        return result;
    }
};

/*int main() {
    List list1;
    List list2;

    // Добавление элементов в первый список
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list1.add(4);

    // Добавление элементов во второй список
    list2.add(3);
    list2.add(4);
    list2.add(5);
    list2.add(6);

    // Выводим списки
    std::cout << "list 1: ";
    list1.print();

    std::cout << "list 2: ";
    list2.print();

    // Поиск элемента в списке
    int elementToFind = 3;
    bool found = list1.find(elementToFind);
    if (found) {
        std::cout << "Element " << elementToFind << " found in list 1." << std::endl;
    }
    else {
        std::cout << "Element " << elementToFind << " not found in list 1." << std::endl;
    }

    // Нахождение пересечения списков
    List intersectionResult = List::intersection(list1, list2);

    // Вывод результата пересечения
    std::cout << "perese4enie: ";
    intersectionResult.print();

    // Удаление элемента из списка
    int elementToRemove = 2;
    list1.remove(elementToRemove);

    // Вывод списка после удаления
    std::cout << "1 list after delete " << elementToRemove << ": ";
    list1.print();

    return 0;
}*/
