#include <iostream>
#include <cstdlib> // Для использования rand()
#include <algorithm>
#include <string>

using namespace std;
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* _head;

public:
    // Конструктор 	по умолчанию.
    LinkedList() : _head(nullptr) {}


    //Конструктор копирования
    LinkedList(const LinkedList& other) :_head(nullptr) {
        Node<T>* otherCurrent = other._head;
        while (otherCurrent) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    //Конструктор, заполняющий список случайными значениями согласно заданию.
    LinkedList(int size) : _head(nullptr) {
        for (int i = 0; i < size; ++i) {
            push_tail(rand() % 100); // случайные значения от 0 до 99
        }
    }

    // Деструктор
    ~LinkedList() {
        Node<T>* current = _head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        _head = nullptr;
    }

    void swap(LinkedList& other) noexcept {
        std::swap(_head, other._head);
    }
    // Операция присваивания
    LinkedList& operator=(const LinkedList& other) {
        LinkedList temp(other);
        swap(temp);
        return *this;
    }

    // Добавление элемента в конец списка — push_tail
    void push_tail(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!_head) {
            _head = newNode;
        }
        else {
            Node<T>* current = _head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    //Добавление другого списка LinkedList в конец списка — push_tail(перегруженный метод).
    void push_tail(const LinkedList& other) {
        Node<T>* current = other._head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    //Добавление элемента в начало списка — push_head.
    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = _head;
        _head = newNode;
    }

    //Добавление списка LinkedList 	в начало списка — push_head(перегруженный метод).
    void push_head(const LinkedList& other) {
        auto new_list = other;
        new_list.push_tail(*this);
        *this = new_list;
    }

    //Удаление элемента из начала списка — pop_head.
    void pop_head() {
        if (_head) {
            Node<T>* temp = _head;
            _head = _head->next;
            delete temp;
        }
    }
    //Удаление элемента из конца списка — pop_tail.
    void pop_tail() {
        if (!_head) return;

        if (!_head->next) {
            delete _head;
            _head = nullptr;
        }
        else {
            Node<T>* current = _head;
            while (current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
    }

    //Удаление 	всех элементов Node с информационным полем,
    //равным переданному — delete_node.
    void delete_node(const T& value) {
        Node<T>* current = _head;
        Node<T>* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                }
                else {
                    pop_head();
                    current = _head;
                }
            }
            else {
                previous = current;
                current = current->next;
            }
        }
    }

    int size() const {
        int count = 0;
        Node<T>* current = _head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Операция доступа по индексу (в двух вариантах: для чтения/записи).
    T& operator[](int index) {
        Node<T>* current = _head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }

        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }

        return current->data;
    }

    const T& operator[](int index) const {
        Node<T>* current = _head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }

        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }

        return current->data;
    }

    Node<T>* get_head() const {
        return _head;
    }

    // Сложение двух чисел, представленных в виде списков
    LinkedList<T> operator+(const LinkedList& other) const {
        LinkedList<T> result;
        Node<T>* currentThis = _head;
        Node<T>* currentOther = other._head;
        int carry = 0;

        while (currentThis || currentOther || carry) {
            int sum = (currentThis ? currentThis->data : 0) + (currentOther ? currentOther->data : 0) + carry;
            carry = sum / 10;
            sum %= 10;
            result.push_tail(sum);

            if (currentThis) currentThis = currentThis->next;
            if (currentOther) currentOther = currentOther->next;
        }

        return result;
    }

    // Умножение двух чисел, представленных в виде списков
    LinkedList<T> operator*(const LinkedList& other) const {
        LinkedList<T> result;

        for (int i = 0; i < other.size(); ++i) {
            LinkedList<T> temp = *this;
            int multiplier = other[i];

            for (int j = 1; j < multiplier; ++j) {
                temp = temp + *this;
            }

            temp.push_tail(std::stoi(std::to_string(multiplier) + std::string(i, '0')));

            result = result + temp;
        }

        return result;
    }

    // Оператор вывода на печать
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Node<T>* current = list._head;
        while (current) {
            os << current->data;
            if (current->next) os << " -> ";
            current = current->next;
        }
        return os;
    }

};


int main() {
    LinkedList<int> num1;
    num1.push_tail(1);
    num1.push_tail(2);
    num1.push_tail(3);

    LinkedList<int> num2;
    num2.push_tail(4);
    num2.push_tail(5);
    num2.push_tail(5);
    num2.push_tail(5);

    LinkedList<int> sum = num1 + num2;
    LinkedList<int> product = num1 * num2;

    std::cout << "Number 1: " << num1 << std::endl;
    std::cout << "Number 2: " << num2 << std::endl;
    std::cout << "Сложить: " << sum << std::endl;
    std::cout << "Умножить: " << product << std::endl;

    return 0;
}


