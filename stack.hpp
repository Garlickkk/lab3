#ifndef STACK_HPP
#define STACK_HPP

#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include <functional>
#include <iostream>

template<class T>
class Stack {
private:
    DynamicArray<T> *data;

public:
    Stack(); // пустой стек
    Stack(T *items, int count); // стек из массива
    Stack(const Stack<T> &other); // коп конструктор
    ~Stack();

    void Push(T item);
    T Pop();
    T Top() const;
    bool IsEmpty() const;
    int GetSize() const;

    int IndexOf(const Stack<T> &subseq) const; // инд первого вхождения
    bool Contains(const Stack<T> &subseq) const; // пр-ка наличия п-ти
    Stack<int> *FindAllOccurrences(const Stack<T> &subseq) const; // все вхождения

    Stack<T> *Map(std::function<T(T)> f) const; // поэлементное преобразование
    Stack<T> *Map(std::function<T(T, int)> f) const; // Map с индексом
    Stack<T> *Where(std::function<bool(T)> f) const;
    T Reduce(std::function<T(T, T)> f, T init) const;
    Stack<T> *Zip(const Stack<T> *other, std::function<T(T, T)> f) const; // поэлементная операция
    Stack<T> *Concat(const Stack<T> *other) const; // объединение 2 ст

    void Print(std::ostream &os = std::cout) const; // вывод

    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stack);
};

template<class T>
Stack<T>::Stack() {
    this->data = new DynamicArray<T>(0);
}

template<class T>
Stack<T>::Stack(T *items, int count) {
    if (count < 0) {
        throw InvalidArgumentException("размер не может быть отрицательным");
    }
    if (items == nullptr && count > 0) {
        throw InvalidArgumentException("Указатель не должен быть 0");
    }
    this->data = new DynamicArray<T>(count); // выд памяти
    for (int i = 0; i < count; i++) {
        this->data->Set(i, items[i]); // копирование эл
    }
}

template<class T>
Stack<T>::Stack(const Stack<T> &other) {
    this->data = new DynamicArray<T>(*other.data);
}

template<class T>
Stack<T>::~Stack() {
    delete this->data;
}

template<class T>
void Stack<T>::Push(T item) {
    int oldSize = this->data->GetSize();
    this->data->Resize(oldSize + 1); // увеличиваем размера массива на 1
    this->data->Set(oldSize, item); // запись элемента
}

template<class T>
T Stack<T>::Pop() {
    if (this->data->GetSize() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    int lastIndex = this->data->GetSize() - 1;
    T item = this->data->Get(lastIndex);
    this->data->Resize(lastIndex);
    return item;
}

template<class T>
T Stack<T>::Top() const {
    if (this->data->GetSize() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    return this->data->Get(this->data->GetSize() - 1);
}

template<class T>
bool Stack<T>::IsEmpty() const {
    return this->data->GetSize() == 0;
}

template<class T>
int Stack<T>::GetSize() const {
    return this->data->GetSize();
}


template<class T>
int Stack<T>::IndexOf(const Stack<T> &subseq) const {
    if (subseq.GetSize() == 0) { // пустая подп-ть
        return 0; // считается найденной в начале
    }
    if (subseq.GetSize() > this->GetSize()) { // подп-ть длиннее стека
        return -1;
    }

    for (int i = 0; i <= this->GetSize() - subseq.GetSize(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.GetSize(); j++) {
            if (this->data->Get(i + j) != subseq.data->Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return i; // индекс начала
        }
    }
    return -1;
}

template<class T>
bool Stack<T>::Contains(const Stack<T> &subseq) const {
    return IndexOf(subseq) != -1; // если индекс не -1, значит содержит
}

template<class T>
Stack<int> *Stack<T>::FindAllOccurrences(const Stack<T> &subseq) const {
    Stack<int> *result = new Stack<int>(); // стек для хранения индексов

    if (subseq.GetSize() == 0 || subseq.GetSize() > this->GetSize()) {
        return result; // пустой стек
    }

    for (int i = 0; i <= this->GetSize() - subseq.GetSize(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.GetSize(); j++) {
            if (this->data->Get(i + j) != subseq.data->Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            result->Push(i); // индекс вхождения
        }
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Concat(const Stack<T> *other) const {
    Stack<T> *result = new Stack<T>();

    for (int i = 0; i < this->GetSize(); i++) { // копируем элементы текущего стека
        result->Push(this->data->Get(i));
    }

    for (int i = 0; i < other->GetSize(); i++) { // копируем элементы второго стека
        result->Push(other->data->Get(i));
    }

    return result;
}


template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < this->GetSize(); i++) {
        result->Push(f(this->data->Get(i))); // применяем функцию и добавляем в новый стек
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T, int)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < this->GetSize(); i++) {
        result->Push(f(this->data->Get(i), i)); // передаём элемент и его индекс
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Where(std::function<bool(T)> f) const {
    Stack<T> *result = new Stack<T>();
    for (int i = 0; i < this->GetSize(); i++) {
        T val = this->data->Get(i);
        if (f(val)) {
            result->Push(val);
        }
    }
    return result;
}

template<class T>
T Stack<T>::Reduce(std::function<T(T, T)> f, T init) const {
    T acc = init;
    for (int i = 0; i < this->GetSize(); i++) {
        acc = f(acc, this->data->Get(i));
    }
    return acc;
}

template<class T>
Stack<T> *Stack<T>::Zip(const Stack<T> *other, std::function<T(T, T)> f) const {
    Stack<T> *result = new Stack<T>();
    int minSize;
    if (this->GetSize() < other->GetSize()) {
        minSize = this->GetSize();
    } else {
        minSize = other->GetSize();
    }
    for (int i = 0; i < minSize; i++) {
        result->Push(f(this->data->Get(i), other->data->Get(i)));
    }
    return result;
}


template<class T>
void Stack<T>::Print(std::ostream &os) const {
    os << "[";
    for (int i = 0; i < this->GetSize(); i++) {
        if (i > 0) os << ", ";
        os << this->data->Get(i);
    }
    os << "]";
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
    stack.Print(os);
    return os;
}

#endif // STACK_HPP