#ifndef STACK_HPP
#define STACK_HPP

#include "array_sequence.hpp"
#include "exceptions.hpp"
#include <functional>


template<class T>
class Stack {
private:
    Sequence<T> *data;

public:
    Stack();
    explicit Stack(Sequence<T> *seq); // создание нового стека из результата операции над seq (map, ....)
    ~Stack();


    void Push(T item);
    T Pop();
    T Top() const;
    bool IsEmpty() const;
    int GetSize() const;

    int IndexOf(const Stack<T>& subseq) const; // инд первого вхожд подпосл
    bool Contains(const Stack<T>& subseq) const; // проверка наличия подпосл
    Stack<int>* FindAllOccurrences(const Stack<T>& subseq) const; // все вхождения

    Stack<T> *Map(std::function<T(T)> f) const;
    Stack<T> *Map(std::function<T(T, int)> f) const;
    Stack<T> *Where(std::function<bool(T)> f) const;
    T Reduce(std::function<T(T, T)> f, T init) const;
    Stack<T> *Zip(Stack<T> *other, std::function<T(T, T)> f) const;
    Stack<T> *Concat(Stack<T> *other) const;
    Sequence<T> *GetSubsequence(int start, int end) const;
    Stack<T> *Skip(int n) const;
    Stack<T> *Take(int n) const;

    void Print(std::ostream &os = std::cout) const;

    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const Stack<U> &stack);
};


template<class T>
Stack<T>::Stack() : data(new MutableArraySequence<T>()) {}

template<class T>
Stack<T>::Stack(Sequence<T> *seq) : data(seq->Empty()) {
    for (int i = 0; i < seq->GetLength(); i++) {
        Sequence<T> *temp = data->Append(seq->Get(i));
        if (temp != data) {
            delete data;
            data = temp;
        }
    }
}

template<class T>
Stack<T>::~Stack() {
    delete data;
}

template<class T>
void Stack<T>::Push(T item) {
    Sequence<T> *temp = data->Append(item);
    if (temp != data) {
        delete data;
        data = temp;
    }
}

template<class T>
T Stack<T>::Pop() {
    if (data->GetLength() == 0) {
        throw EmptyContainerException("Стек пуст");
    }
    T item = data->GetLast();
    if (data->GetLength() == 1) { // 1 эл -> пустая подпос
        Sequence<T> *newData = data->Empty();
        delete data;
        data = newData;
    } else { // иначе посл без последнего эл
        Sequence<T> *newData = data->GetSubsequence(0, data->GetLength() - 2);
        delete data;
        data = newData;
    }
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
int Stack<T>::IndexOf(const Stack<T>& subseq) const {
    if (subseq.GetSize() == 0) { // если п-ть пустая
        return 0;
    }
    if (subseq.GetSize() > GetSize()) { // если п-ть длиннее чем стек
        return -1;
    }

    for (int i = 0; i <= GetSize() - subseq.GetSize(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.GetSize(); j++) {
            if (data->Get(i + j) != subseq.data->Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

template<class T>
bool Stack<T>::Contains(const Stack<T>& subseq) const {
    return IndexOf(subseq) != -1; // если не вернул -1 -> содержит
}

template<class T>
Stack<int>* Stack<T>::FindAllOccurrences(const Stack<T>& subseq) const {
    Stack<int>* result = new Stack<int>();

    if (subseq.GetSize() == 0 || subseq.GetSize() > GetSize()) {
        return result; // пустой стек
    }

    for (int i = 0; i <= GetSize() - subseq.GetSize(); i++) {
        bool found = true;
        for (int j = 0; j < subseq.GetSize(); j++) {
            if (data->Get(i + j) != subseq.data->Get(j)) {
                found = false;
                break;
            }
        }
        if (found) {
            result->Push(i);
        }
    }
    return result;
}

template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T)> f) const {
    Sequence<T> *mapped = data->Map(f);
    return new Stack<T>(mapped);
}

template<class T>
Stack<T> *Stack<T>::Map(std::function<T(T, int)> f) const {
    Sequence<T> *mapped = data->Map(f);
    return new Stack<T>(mapped);
}

template<class T>
Stack<T> *Stack<T>::Where(std::function<bool(T)> f) const {
    Sequence<T> *filtered = data->Where(f);
    return new Stack<T>(filtered);
}

template<class T>
T Stack<T>::Reduce(std::function<T(T, T)> f, T init) const {
    return data->Reduce(f, init);
}

template<class T>
Stack<T> *Stack<T>::Zip(Stack<T> *other, std::function<T(T, T)> f) const {
    Sequence<T> *zipped = data->Zip(other->data, f);
    return new Stack<T>(zipped);
}

template<class T>
Stack<T> *Stack<T>::Concat(Stack<T> *other) const {
    Sequence<T> *combined = data->Concat(other->data);
    return new Stack<T>(combined);
}

template<class T>
Sequence<T> *Stack<T>::GetSubsequence(int start, int end) const {
    if (start < 0 || start >= GetSize()) {
        throw IndexOutOfRangeException(start, GetSize());
    }
    if (end < 0 || end >= GetSize()) {
        throw IndexOutOfRangeException(end, GetSize());
    }
    if (end < start) {
        throw IndexOutOfRangeException("start > end");
    }
    return data->GetSubsequence(start, end);
}

template<class T>
Stack<T> *Stack<T>::Skip(int n) const {
    if (n < 0) {
        throw InvalidArgumentException("n не может быть отрицательным");
    }
    Sequence<T> *skipped = data->Skip(n);
    return new Stack<T>(skipped);
}

template<class T>
Stack<T> *Stack<T>::Take(int n) const {
    if (n < 0) {
        throw InvalidArgumentException("n не может быть отрицательным");
    }
    Sequence<T> *taken = data->Take(n);
    return new Stack<T>(taken);
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

template<class T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
    stack.Print(os);
    return os;
}

#endif // STACK_HPP