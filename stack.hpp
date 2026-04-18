#ifndef STACK_HPP
#define STACK_HPP

#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"
#include <functional>
#include <stdexcept>

template<class T>
class Stack {
private:
    Sequence<T> *data;
    bool ownsData; // флаг, нужно ли удалять data

    void EnsureOwnership(); //гарантирует, что стек владеет своими данными

public:
    Stack();

    explicit Stack(Sequence<T> *seq); // забирает владение памятью для предотвращения утечек памяти при создании
    // новых последоватльеостей в методе sort and concat

    // Конструктор копирования: создаёт глубокую копию данных другого стека
    Stack(const Stack<T> &other);


    ~Stack();

    // Оператор присваивания: глубокая копия
    Stack<T> &operator=(const Stack<T> &other);


    void Push(T item); // Добавление элемента на вершину стека

    T Pop(); // Удаление элемента с вершины стека


    T Top() const; // элемент н вершине


    bool IsEmpty() const;


    int GetSize() const;


    Sequence<T> *Map(std::function<T(T)> f) const;

    Sequence<T> *Where(std::function<bool(T)> f) const;

    T Reduce(std::function<T(T, T)> f, T init) const;

    Sequence<T> *Zip(Stack<T> *other, std::function<T(T, T)> f) const;

    Stack<T> *Sort() const; // сорт возвр новый отсортированный стек

    Stack<T> *Concat(Stack<T> *other) const;

    Sequence<T> *GetSubsequence(int start, int end) const;

    void Print(std::ostream &os = std::cout) const;

    template<class U> // Перегрузка оператора вывода
    friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stack);
};


template<class T>
void Stack<T>::EnsureOwnership() {
    if (!ownsData) {
        // Создаём новую последовательность того же типа, что и data
        Sequence<T> *copiedData = data->Empty();
        for (int i = 0; i < data->GetLength(); i++) {
            Sequence<T> *temp = copiedData->Append(data->Get(i));
            if (temp != copiedData) {
                delete copiedData;
                copiedData = temp;
            }
        }
        data = copiedData;
        ownsData = true;
    }
}

template<class T>
Stack<T>::Stack() : data(new MutableArraySequence<T>()), ownsData(true) {
}

template<class T>
Stack<T>::Stack(Sequence<T> *seq) : data(seq), ownsData(true) {
    // Конструктор из существующей последовательности
}

// Конструктор копирования
template<class T>
Stack<T>::Stack(const Stack<T> &other) : data(other.data->Empty()), ownsData(true) {
    for (int i = 0; i < other.data->GetLength(); i++) {
        Sequence<T> *temp = data->Append(other.data->Get(i));
        if (temp != data) {
            delete data;
            data = temp;
        }
    }
}


template<class T>
Stack<T>::~Stack() {
    if (ownsData && data != nullptr) {
        delete data;
    }
}


template<class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
    // Оператор присваивания
    if (this != &other) {
        // Удаляем старые данные, если владеем ими
        if (ownsData && data != nullptr) {
            delete data;
        }
        data = other.data->Empty(); // создание новой пустой подпоследовательности
        ownsData = true;
        for (int i = 0; i < other.data->GetLength(); i++) {
            // Копируем элементы
            Sequence<T> *temp = data->Append(other.data->Get(i));
            if (temp != data) {
                delete data;
                data = temp;
            }
        }
    }
    return *this;
}

template<class T>
void Stack<T>::Push(T item) {
    EnsureOwnership();

    Sequence<T> *temp = data->Append(item);
    if (temp != data) {
        delete data;
        data = temp;
    }
}

template<class T>
T Stack<T>::Pop() {
    EnsureOwnership();

    if (data->GetLength() == 0) {
        throw EmptyContainerException("Стек пуст");
    }

    T item = data->GetLast();

    if (data->GetLength() == 1) {
        // Если остался один элемент, создаём пустую последовательность
        Sequence<T> *newData = data->Empty();
        delete data;
        data = newData;
    } else {
        // подпоследовательность без последнего элемента
        Sequence<T> *newData = data->GetSubsequence(0, data->GetLength() - 2);
        delete data;
        data = newData;
    }
    // ownsData = true

    return item;
}

template<class T>
T Stack<T>::Top() const {
    if (data->GetLength() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    return data->GetLast();
}


template<class T>
bool Stack<T>::IsEmpty() const {
    return data->GetLength() == 0;
}


template<class T>
int Stack<T>::GetSize() const {
    return data->GetLength();
}


template<class T>
Sequence<T> *Stack<T>::Map(std::function<T(T)> f) const {
    return data->Map(f);
}


template<class T>
Sequence<T> *Stack<T>::Where(std::function<bool(T)> f) const {
    return data->Where(f);
}


template<class T>
T Stack<T>::Reduce(std::function<T(T, T)> f, T init) const {
    return data->Reduce(f, init);
}


template<class T>
Sequence<T> *Stack<T>::Zip(Stack<T> *other, std::function<T(T, T)> f) const {
    return data->Zip(other->data, f);
}

template<class T>
Stack<T> *Stack<T>::Sort() const {
    int n = data->GetLength();
    T *arr = new T[n];
    for (int i = 0; i < n; i++) {
        arr[i] = data->Get(i);
    }
    // Пузырьковая сортировка
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    Sequence<T> *sorted = new MutableArraySequence<T>(arr, n);
    delete[] arr;

    return new Stack<T>(sorted);
}


template<class T>
Stack<T> *Stack<T>::Concat(Stack<T> *other) const {
    Sequence<T> *combined = data->Concat(other->data);
    return new Stack<T>(combined);
}

template<class T> // получение подпоследовательности
Sequence<T> *Stack<T>::GetSubsequence(int start, int end) const {
    return data->GetSubsequence(start, end);
}

template<class T>
void Stack<T>::Print(std::ostream &os) const {
    os << "[";
    for (int i = 0; i < data->GetLength(); i++) {
        if (i > 0) os << ", ";
        os << data->Get(i);
    }
    os << "]";
}

template<class T> // Перегрузка оператора вывода
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
    stack.Print(os);
    return os;
}

#endif // STACK_HPP
