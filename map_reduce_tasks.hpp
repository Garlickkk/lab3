#ifndef MAP_REDUCE_TASKS_HPP
#define MAP_REDUCE_TASKS_HPP

#include "sequence.hpp"
#include "array_sequence.hpp"
#include <cmath>
#include <algorithm>
#include <tuple> // мин макс и авг

// П-1
inline std::tuple<double, double, double> computeMinMaxAvg(Sequence<int> *seq) {
    if (seq->GetLength() == 0) {
        throw InvalidArgumentException("Последовательность пуста");
    }

    struct Acc {
        int minVal;
        int maxVal;
        long long sum;
        int count;
    };

    Acc acc{seq->Get(0), seq->Get(0), 0, 0};

    for (int i = 0; i < seq->GetLength(); i++) {
        int val = seq->Get(i);
        if (val < acc.minVal) acc.minVal = val;
        if (val > acc.maxVal) acc.maxVal = val;
        acc.sum += val;
        acc.count++;
    }

    double avg = static_cast<double>(acc.sum) / acc.count; // преобразуем сумму из long long в double
    return {
        static_cast<double>(acc.minVal), // Преобразуем minVal в double
        static_cast<double>(acc.maxVal), // Преобразуем maxVal в double
        avg
    };
}

// П-2
inline double computeMedian(Sequence<int> *seq) {
    if (seq->GetLength() == 0) {
        throw InvalidArgumentException("Последовательность пуста");
    }

    int n = seq->GetLength();
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = seq->Get(i);
    }

    std::sort(arr, arr + n);

    double median;
    if (n % 2 == 1) {
        median = arr[n / 2];
    } else {
        median = (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    }

    delete[] arr;
    return median;
}

// П-5 префиксы
inline Sequence<Sequence<int> *> *computePrefixes(Sequence<int> *seq) {
    MutableArraySequence<Sequence<int> *> *result = new MutableArraySequence<Sequence<int> *>();

    MutableArraySequence<int> *current = new MutableArraySequence<int>();
    for (int i = 0; i < seq->GetLength(); i++) {
        current->Append(seq->Get(i)); // добавление элемента в конец
        MutableArraySequence<int> *copy = new MutableArraySequence<int>(); // копия текущего префикса(current будет меняться)
        for (int j = 0; j < current->GetLength(); j++) {
            copy->Append(current->Get(j));
        }
        result->Append(copy); // указатель на копию в финальной последовательности
    }
    delete current;

    return result;
}

// П-5 постфиксы
inline Sequence<Sequence<int> *> *computeSuffixes(Sequence<int> *seq) { // принимаем последовательность и
    // возвращаем список всех начальных отрезков
    MutableArraySequence<Sequence<int> *> *result = new MutableArraySequence<Sequence<int> *>();
    int n = seq->GetLength();

    for (int i = 0; i < n; i++) {
        result->Append(seq->GetSubsequence(i, n - 1));
    }

    return result;
}

// П-8
inline Sequence<int> *computeMirrorSum(Sequence<int> *seq) {
    int n = seq->GetLength();
    if (n == 0) {
        return new MutableArraySequence<int>();
    }


    MutableArraySequence<int> *reversed = new MutableArraySequence<int>(); // отраженная последовательность
    for (int i = n - 1; i >= 0; i--) {
        reversed->Append(seq->Get(i));
    }

    Sequence<int> *result = seq->Zip(reversed, [](int a, int b) { return a + b; }); // поэлементное сложение

    delete reversed; // удаление отраженной последовательности
    return result;
}

#endif // MAP_REDUCE_TASKS_HPP