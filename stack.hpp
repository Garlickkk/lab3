#ifndef STACK_HPP
#define STACK_HPP

#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "exceptions.hpp"
#include <functional>

template <class T>
class Stack {
private:
    Sequence<T>* data;
    bool ownsData;  // флаг, нужно ли удалять data

public:
    Stack() : data(new MutableArraySequence<T>()), ownsData(true) {}

    Stack(Sequence<T>* seq) : data(seq), ownsData(false) {}

    Stack(const Stack<T>& other) : data(other.data->Empty()), ownsData(true) {
        for (int i = 0; i < other.data->GetLength(); i++) {
            data->Append(other.data->Get(i));
        }
    }

    ~Stack() {
        if (ownsData && data != nullptr) {
            delete data;
        }
    }

    Stack<T>& operator=(const Stack<T>& other) {
        if (this != &other) {
            if (ownsData && data != nullptr) {
                delete data;
            }
            data = other.data->Empty();
            ownsData = true;
            for (int i = 0; i < other.data->GetLength(); i++) {
                data->Append(other.data->Get(i));
            }
        }
        return *this;
    }


    void Push(T item) {
        data->Append(item);
    }

    T Pop() {
        if (data->GetLength() == 0) {
            throw EmptyContainerException("Стек пуст");
        }
        T item = data->GetLast();
        //новая последовательность без последнего элемента
        if (data->GetLength() == 1) {
            Sequence<T>* newData = data->Empty();
            if (ownsData) delete data;
            data = newData;
            ownsData = true;
        } else {
            Sequence<T>* newData = data->GetSubsequence(0, data->GetLength() - 2);
            if (ownsData) delete data;
            data = newData;
            ownsData = true;
        }
        return item;
    }

    T Top() const {
        if (data->GetLength() == 0) {
            throw EmptyContainerException("Стек пуст");
        }
        return data->GetLast();
    }

    bool IsEmpty() const {
        return data->GetLength() == 0;
    }

    int GetSize() const {
        return data->GetLength();
    }

    // Операции Sequence
    Sequence<T>* Map(std::function<T(T)> f) const {
        return data->Map(f);
    }

    Sequence<T>* Where(std::function<bool(T)> f) const {
        return data->Where(f);
    }

    T Reduce(std::function<T(T, T)> f, T init) const {
        return data->Reduce(f, init);
    }

    Sequence<T>* Zip(Stack<T>* other, std::function<T(T, T)> f) const {
        return data->Zip(other->data, f);
    }

    // Сортировка
    Stack<T>* Sort() const {
        int n = data->GetLength();
        T* arr = new T[n];
        for (int i = 0; i < n; i++) {
            arr[i] = data->Get(i);
        }
        for (int i = 0; i < n - 1; i++) { // Пузырьковая сортировка
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        Sequence<T>* sorted = new MutableArraySequence<T>(arr, n);
        delete[] arr;
        return new Stack<T>(sorted);
    }


    Stack<T>* Concat(Stack<T>* other) const {
        Sequence<T>* combined = data->Concat(other->data);
        return new Stack<T>(combined);
    }

    Sequence<T>* GetSubsequence(int start, int end) const { // Получение подпоследовательности
        return data->GetSubsequence(start, end);
    }


    void Print(std::ostream& os = std::cout) const { // вывод стека
        os << "Стек: [";
        for (int i = 0; i < data->GetLength(); i++) {
            if (i > 0) os << ", ";
            os << data->Get(i);
        }
        os << "]";
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) { // перезагрузка оператора
        stack.Print(os);
        return os;
    }
};

#endif // STACK_HPP