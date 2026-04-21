#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "bit_sequence.hpp"
#include "map_reduce_tasks.hpp"
#include "stack.hpp"

void runAllTests();

using namespace std;

Sequence<int>* currentIntSeq = nullptr;
MutableBitSequence* currentBitSeq = nullptr;
Stack<int>* currentStack = nullptr;

enum SeqType {
    ARRAY_MUTABLE,
    ARRAY_IMMUTABLE,
    LIST_MUTABLE,
    LIST_IMMUTABLE,
    BIT_SEQUENCE,
    STACK
};

SeqType currentSeqType = ARRAY_MUTABLE;
bool isBitMode = false;
bool isStackMode = false;

void selectInitialType() {
    cout << "\n========================================\n";
    cout << "   ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ\n";
    cout << "========================================\n";
    cout << "1. MutableArraySequence   (изменяемый массив)\n";
    cout << "2. ImmutableArraySequence (неизменяемый массив)\n";
    cout << "3. MutableListSequence    (изменяемый список)\n";
    cout << "4. ImmutableListSequence  (неизменяемый список)\n";
    cout << "5. BitSequence            (битовая последовательность)\n";
    cout << "6. Stack                  (стек)\n";
    cout << "==========================\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }
    if (currentBitSeq != nullptr) {
        delete currentBitSeq;
        currentBitSeq = nullptr;
    }
    if (currentStack != nullptr) {
        delete currentStack;
        currentStack = nullptr;
    }

    switch (choice) {
        case 1:
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            isStackMode = false;
            currentIntSeq = new MutableArraySequence<int>();
            cout << "\nСоздана пустая MutableArraySequence<int>\n";
            break;
        case 2:
            currentSeqType = ARRAY_IMMUTABLE;
            isBitMode = false;
            isStackMode = false;
            currentIntSeq = new ImmutableArraySequence<int>();
            cout << "\nСоздана пустая ImmutableArraySequence<int>\n";
            break;
        case 3:
            currentSeqType = LIST_MUTABLE;
            isBitMode = false;
            isStackMode = false;
            currentIntSeq = new MutableListSequence<int>();
            cout << "\nСоздана пустая MutableListSequence<int>\n";
            break;
        case 4:
            currentSeqType = LIST_IMMUTABLE;
            isBitMode = false;
            isStackMode = false;
            currentIntSeq = new ImmutableListSequence<int>();
            cout << "\nСоздана пустая ImmutableListSequence<int>\n";
            break;
        case 5:
            currentSeqType = BIT_SEQUENCE;
            isBitMode = true;
            isStackMode = false;
            currentBitSeq = new MutableBitSequence();
            cout << "\nСоздана пустая MutableBitSequence\n";
            break;
        case 6:
            currentSeqType = STACK;
            isBitMode = false;
            isStackMode = true;
            currentStack = new Stack<int>();
            cout << "\nСоздан пустой Stack<int>\n";
            break;
        default:
            cout << "\nНеверный выбор! Создана последовательность по умолчанию.\n";
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            isStackMode = false;
            currentIntSeq = new MutableArraySequence<int>();
    }
}

void printMenu() {
    if (isStackMode) {
        cout << "\n========== МЕНЮ (СТЕК) ==========\n";
        cout << "1. Создать новый стек\n";
        cout << "2. Показать стек\n";
        cout << "3. Push (добавить на вершину)\n";
        cout << "4. Pop (удалить с вершины)\n";
        cout << "5. Top (посмотреть вершину)\n";
        cout << "6. IsEmpty (проверить пустоту)\n";
        cout << "7. GetSize (размер)\n";
        cout << "8. IndexOf (поиск подпоследовательности)\n";
        cout << "9. Contains (проверка наличия)\n";
        cout << "10. FindAllOccurrences (все вхождения)\n";
        cout << "11. Concat (объединить с другим стеком)\n";
        cout << "12. Map (применить функцию)\n";
        cout << "13. Where (фильтрация)\n";
        cout << "14. Reduce (свёртка)\n";
        cout << "15. Zip (поэлементная операция)\n";
        cout << "16. Skip (пропустить N элементов)\n";
        cout << "17. Take (взять N элементов)\n";
        cout << "18. Map-Reduce задачи\n";
        cout << "19. Запустить все тесты\n";
        cout << "0. Выход\n";
        cout << "================================\n";
        cout << "Текущий тип: Stack\n";
        cout << "Выберите действие: ";
        return;
    }

    if (isBitMode) {
        cout << "\n========== МЕНЮ (BITSEQUENCE) ==========\n";
        cout << "1. Создать новую BitSequence\n";
        cout << "2. Показать BitSequence\n";
        cout << "3. Append (добавить бит в конец)\n";
        cout << "4. Prepend (добавить бит в начало)\n";
        cout << "5. InsertAt (вставить по индексу)\n";
        cout << "6. Get (получить бит)\n";
        cout << "7. GetSubsequence (подпоследовательность)\n";
        cout << "8. Bitwise AND\n";
        cout << "9. Bitwise OR\n";
        cout << "10. Bitwise XOR\n";
        cout << "11. Bitwise NOT\n";
        cout << "12. GetLength\n";
        cout << "13. Запустить все тесты\n";
        cout << "0. Выход\n";
        cout << "==========================================\n";
        cout << "Текущий тип: BitSequence\n";
        cout << "Выберите действие: ";
        return;
    }

    cout << "\n========== МЕНЮ (SEQUENCE) ==========\n";
    cout << "1. Создать новую последовательность\n";
    cout << "2. Показать последовательность\n";
    cout << "3. Append (добавить в конец)\n";
    cout << "4. Prepend (добавить в начало)\n";
    cout << "5. InsertAt (вставить по индексу)\n";
    cout << "6. Get (получить элемент)\n";
    cout << "7. GetSubsequence (подпоследовательность)\n";
    cout << "8. Concat (объединить)\n";
    cout << "9. Map\n";
    cout << "10. Where\n";
    cout << "11. Reduce\n";
    cout << "12. Zip\n";
    cout << "13. Skip\n";
    cout << "14. Take\n";
    cout << "15. Переключиться на BitSequence\n";
    cout << "16. Переключиться на Stack\n";
    cout << "17. Map-Reduce задачи\n";
    cout << "18. Запустить все тесты\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
    cout << "Текущий тип: ";
    switch (currentSeqType) {
        case ARRAY_MUTABLE:   cout << "MutableArraySequence"; break;
        case ARRAY_IMMUTABLE: cout << "ImmutableArraySequence"; break;
        case LIST_MUTABLE:    cout << "MutableListSequence"; break;
        case LIST_IMMUTABLE:  cout << "ImmutableListSequence"; break;
        default:              cout << "Sequence"; break;
    }
    cout << "\nВыберите действие: ";
}

void createSequence() {
    if (isStackMode) {
        cout << "\n--- Создание Stack ---\n";
        if (currentStack != nullptr) {
            delete currentStack;
        }
        currentStack = new Stack<int>();
        cout << "Создан пустой Stack\n";
        return;
    }

    if (isBitMode) {
        cout << "\n--- Создание BitSequence ---\n";
        cout << "Введите строку из 0 и 1: ";
        string bits;
        cin >> bits;
        int len = bits.length();
        bool* arr = new bool[len];
        for (int i = 0; i < len; i++) {
            arr[i] = (bits[i] == '1');
        }
        if (currentBitSeq != nullptr) delete currentBitSeq;
        currentBitSeq = new MutableBitSequence(arr, len);
        delete[] arr;
        cout << "Создана BitSequence: ";
        currentBitSeq->Print();
        cout << endl;
        return;
    }

    cout << "\n--- Создание последовательности (int) ---\n";
    cout << "Выберите тип:\n";
    cout << "1. MutableArraySequence\n";
    cout << "2. ImmutableArraySequence\n";
    cout << "3. MutableListSequence\n";
    cout << "4. ImmutableListSequence\n";
    cout << "Ваш выбор: ";

    int typeChoice;
    cin >> typeChoice;

    cout << "Введите элементы через пробел (Enter для завершения): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    if (currentIntSeq != nullptr) {
        delete currentIntSeq;
        currentIntSeq = nullptr;
    }

    int val;
    vector<int> items;
    while (ss >> val) {
        items.push_back(val);
    }

    switch (typeChoice) {
        case 1:
            if (items.empty()) {
                currentIntSeq = new MutableArraySequence<int>();
            } else {
                currentIntSeq = new MutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_MUTABLE;
            cout << "Создана MutableArraySequence\n";
            break;
        case 2:
            if (items.empty()) {
                currentIntSeq = new ImmutableArraySequence<int>();
            } else {
                currentIntSeq = new ImmutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_IMMUTABLE;
            cout << "Создана ImmutableArraySequence\n";
            break;
        case 3:
            if (items.empty()) {
                currentIntSeq = new MutableListSequence<int>();
            } else {
                currentIntSeq = new MutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_MUTABLE;
            cout << "Создана MutableListSequence\n";
            break;
        case 4:
            if (items.empty()) {
                currentIntSeq = new ImmutableListSequence<int>();
            } else {
                currentIntSeq = new ImmutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_IMMUTABLE;
            cout << "Создана ImmutableListSequence\n";
            break;
        default:
            cout << "Неверный выбор!\n";
    }

    if (currentIntSeq != nullptr) {
        cout << "Текущая последовательность: " << *currentIntSeq << endl;
    }
}

void showSequence() {
    if (isStackMode) {
        if (currentStack == nullptr) {
            cout << "Stack не создан.\n";
            return;
        }
        cout << "Текущий Stack: " << *currentStack << endl;
        cout << "Размер: " << currentStack->GetSize() << endl;
        if (!currentStack->IsEmpty()) {
            cout << "Вершина (Top): " << currentStack->Top() << endl;
        }
        return;
    }

    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        cout << "Текущая BitSequence: ";
        currentBitSeq->Print();
        cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        cout << "Текущая последовательность: " << *currentIntSeq << endl;
        cout << "Длина: " << currentIntSeq->GetLength() << endl;
        if (currentIntSeq->GetLength() > 0) {
            cout << "Первый элемент: " << currentIntSeq->GetFirst() << endl;
            cout << "Последний элемент: " << currentIntSeq->GetLast() << endl;
        }
    }
}


void stackPush() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    int val;
    cout << "Введите значение для Push: ";
    cin >> val;
    currentStack->Push(val);
    cout << "Результат: " << *currentStack << endl;
}

void stackPop() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    try {
        int val = currentStack->Pop();
        cout << "Удалён элемент: " << val << endl;
        cout << "Результат: " << *currentStack << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void stackTop() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    try {
        cout << "Вершина (Top): " << currentStack->Top() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void stackIsEmpty() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "IsEmpty: " << (currentStack->IsEmpty() ? "true" : "false") << endl;
}

void stackGetSize() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "GetSize: " << currentStack->GetSize() << endl;
}

void stackIndexOf() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }
    Stack<int> subseq;
    for (int x : items) {
        subseq.Push(x);
    }
    int idx = currentStack->IndexOf(subseq);
    cout << "Индекс первого вхождения: " << idx << endl;
}

void stackContains() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для проверки (через пробел): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }
    Stack<int> subseq;
    for (int x : items) {
        subseq.Push(x);
    }
    cout << "Contains: " << (currentStack->Contains(subseq) ? "true" : "false") << endl;
}

void stackFindAllOccurrences() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите подпоследовательность для поиска (через пробел): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }
    Stack<int> subseq;
    for (int x : items) {
        subseq.Push(x);
    }
    Stack<int>* occurrences = currentStack->FindAllOccurrences(subseq);
    cout << "Индексы вхождений: " << *occurrences << endl;
    delete occurrences;
}

void stackConcat() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите элементы второго стека (через пробел): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }
    Stack<int> other;
    for (int x : items) {
        other.Push(x);
    }
    Stack<int>* result = currentStack->Concat(&other);
    cout << "Результат Concat: " << *result << endl;
    delete result;
}

void stackMap() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    int choice;
    cin >> choice;

    int arg;
    function<int(int)> func;
    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void stackWhere() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. Чётные\n";
    cout << "4. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int threshold;
    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x > threshold; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> threshold;
            pred = [threshold](int x) { return x < threshold; };
            break;
        case 3:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 4:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void stackReduce() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentStack->GetSize() > 0 ? currentStack->Top() : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentStack->GetSize() > 0 ? currentStack->Top() : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    int result = currentStack->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

void stackZip() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    cout << "Введите элементы второго стека (через пробел): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }
    Stack<int> other;
    for (int x : items) {
        other.Push(x);
    }
    cout << "Выберите операцию Zip:\n";
    cout << "1. Сложение\n";
    cout << "2. Вычитание (first - second)\n";
    cout << "3. Умножение\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            break;
        case 2:
            func = [](int a, int b) { return a - b; };
            break;
        case 3:
            func = [](int a, int b) { return a * b; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }
    Stack<int>* result = currentStack->Zip(&other, func);
    cout << "Результат Zip: " << *result << endl;
    delete result;
}

void stackSkip() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    int n;
    cout << "Сколько элементов пропустить? ";
    cin >> n;
    Stack<int>* result = currentStack->Skip(n);
    cout << "Результат Skip(" << n << "): " << *result << endl;
    delete result;
}

void stackTake() {
    if (currentStack == nullptr) {
        cout << "Stack не создан.\n";
        return;
    }
    int n;
    cout << "Сколько элементов взять? ";
    cin >> n;
    Stack<int>* result = currentStack->Take(n);
    cout << "Результат Take(" << n << "): " << *result << endl;
    delete result;
}


void appendElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        int bit;
        cout << "Введите бит (0 или 1): ";
        cin >> bit;
        currentBitSeq->Append(bit != 0);
        cout << "Результат: ";
        currentBitSeq->Print();
        cout << endl;
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        int val;
        cout << "Введите значение для добавления в конец: ";
        cin >> val;

        Sequence<int>* newSeq = currentIntSeq->Append(val);
        if (newSeq != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = newSeq;
        }
        cout << "Результат: " << *currentIntSeq << endl;
    }
}

void prependElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        int bit;
        cout << "Введите бит (0 или 1): ";
        cin >> bit;
        currentBitSeq->Prepend(bit != 0);
        cout << "Результат: ";
        currentBitSeq->Print();
        cout << endl;
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        int val;
        cout << "Введите значение для добавления в начало: ";
        cin >> val;

        Sequence<int>* newSeq = currentIntSeq->Prepend(val);
        if (newSeq != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = newSeq;
        }
        cout << "Результат: " << *currentIntSeq << endl;
    }
}

void insertAt() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        int index, bit;
        cout << "Введите индекс: ";
        cin >> index;
        cout << "Введите бит (0 или 1): ";
        cin >> bit;

        try {
            currentBitSeq->InsertAt(bit != 0, index);
            cout << "Результат: ";
            currentBitSeq->Print();
            cout << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        int val, index;
        cout << "Введите индекс: ";
        cin >> index;
        cout << "Введите значение: ";
        cin >> val;

        try {
            Sequence<int>* newSeq = currentIntSeq->InsertAt(val, index);
            if (newSeq != currentIntSeq) {
                delete currentIntSeq;
                currentIntSeq = newSeq;
            }
            cout << "Результат: " << *currentIntSeq << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void getElement() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        int index;
        cout << "Введите индекс: ";
        cin >> index;

        try {
            cout << "Бит[" << index << "] = " << currentBitSeq->Get(index) << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        int index;
        cout << "Введите индекс: ";
        cin >> index;

        try {
            cout << "Элемент[" << index << "] = " << currentIntSeq->Get(index) << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void getSubsequence() {
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана.\n";
            return;
        }
        int start, end;
        cout << "Введите startIndex: ";
        cin >> start;
        cout << "Введите endIndex: ";
        cin >> end;

        try {
            Sequence<bool>* sub = currentBitSeq->GetSubsequence(start, end);
            cout << "Подпоследовательность: ";
            dynamic_cast<BitSequence*>(sub)->Print();
            cout << endl;
            delete sub;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана.\n";
            return;
        }
        int start, end;
        cout << "Введите startIndex: ";
        cin >> start;
        cout << "Введите endIndex: ";
        cin >> end;

        try {
            Sequence<int>* sub = currentIntSeq->GetSubsequence(start, end);
            cout << "Подпоследовательность: " << *sub << endl;
            delete sub;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
}

void concatSequence() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Создайте последовательность для объединения:\n";
    cout << "Введите элементы через пробел: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    Sequence<int>* other = nullptr;
    cout << "Выберите тип для второй последовательности:\n";
    cout << "1. MutableArraySequence\n2. ImmutableArraySequence\n3. MutableListSequence\n4. ImmutableListSequence\n";
    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
        case 1:
            other = new MutableArraySequence<int>(items.data(), items.size());
            break;
        case 2:
            other = new ImmutableArraySequence<int>(items.data(), items.size());
            break;
        case 3:
            other = new MutableListSequence<int>(items.data(), items.size());
            break;
        case 4:
            other = new ImmutableListSequence<int>(items.data(), items.size());
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    try {
        Sequence<int>* result = currentIntSeq->Concat(other);
        if (result != currentIntSeq) {
            delete currentIntSeq;
            currentIntSeq = result;
        }
        cout << "Результат объединения: " << *currentIntSeq << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    delete other;
}

void mapOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите функцию Map:\n";
    cout << "1. Умножить на число\n";
    cout << "2. Прибавить число\n";
    cout << "3. Возвести в квадрат\n";
    cout << "4. Пользовательская функция (лямбда)\n";
    int choice;
    cin >> choice;

    function<int(int)> func;
    int arg;

    switch (choice) {
        case 1:
            cout << "Введите множитель: ";
            cin >> arg;
            func = [arg](int x) { return x * arg; };
            break;
        case 2:
            cout << "Введите слагаемое: ";
            cin >> arg;
            func = [arg](int x) { return x + arg; };
            break;
        case 3:
            func = [](int x) { return x * x; };
            break;
        case 4:
            cout << "Введите лямбда-выражение (будет использована x*2+1): ";
            func = [](int x) { return x * 2 + 1; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Map(func);
    cout << "Результат Map: " << *result << endl;
    delete result;
}

void whereOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите фильтр:\n";
    cout << "1. > N\n";
    cout << "2. < N\n";
    cout << "3. == N\n";
    cout << "4. Чётные\n";
    cout << "5. Нечётные\n";
    int choice;
    cin >> choice;

    function<bool(int)> pred;
    int arg;

    switch (choice) {
        case 1:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x > arg; };
            break;
        case 2:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x < arg; };
            break;
        case 3:
            cout << "Введите N: ";
            cin >> arg;
            pred = [arg](int x) { return x == arg; };
            break;
        case 4:
            pred = [](int x) { return x % 2 == 0; };
            break;
        case 5:
            pred = [](int x) { return x % 2 != 0; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Where(pred);
    cout << "Результат Where: " << *result << endl;
    delete result;
}

void reduceOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }

    cout << "Выберите операцию Reduce:\n";
    cout << "1. Сумма\n";
    cout << "2. Произведение\n";
    cout << "3. Максимум\n";
    cout << "4. Минимум\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    int init;

    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            init = 0;
            break;
        case 2:
            func = [](int a, int b) { return a * b; };
            init = 1;
            break;
        case 3:
            func = [](int a, int b) { return a > b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        case 4:
            func = [](int a, int b) { return a < b ? a : b; };
            init = currentIntSeq->GetLength() > 0 ? currentIntSeq->Get(0) : 0;
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    int result = currentIntSeq->Reduce(func, init);
    cout << "Результат Reduce: " << result << endl;
}

void zipOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Текущая последовательность не создана.\n";
        return;
    }

    cout << "Введите элементы второй последовательности через пробел: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string line;
    getline(cin, line);
    stringstream ss(line);

    vector<int> items;
    int val;
    while (ss >> val) {
        items.push_back(val);
    }

    MutableArraySequence<int> other(items.data(), items.size());

    cout << "Выберите операцию Zip:\n";
    cout << "1. Сложение\n";
    cout << "2. Вычитание (first - second)\n";
    cout << "3. Умножение\n";
    int choice;
    cin >> choice;

    function<int(int, int)> func;
    switch (choice) {
        case 1:
            func = [](int a, int b) { return a + b; };
            break;
        case 2:
            func = [](int a, int b) { return a - b; };
            break;
        case 3:
            func = [](int a, int b) { return a * b; };
            break;
        default:
            cout << "Неверный выбор\n";
            return;
    }

    Sequence<int>* result = currentIntSeq->Zip(&other, func);
    cout << "Результат Zip: " << *result << endl;
    delete result;
}

void skipOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    cout << "Сколько элементов пропустить? ";
    cin >> n;
    Sequence<int>* result = currentIntSeq->Skip(n);
    cout << "Результат Skip(" << n << "): " << *result << endl;
    delete result;
}

void takeOperation() {
    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана.\n";
        return;
    }
    int n;
    cout << "Сколько элементов взять? ";
    cin >> n;
    Sequence<int>* result = currentIntSeq->Take(n);
    cout << "Результат Take(" << n << "): " << *result << endl;
    delete result;
}


void bitCreate() {
    cout << "Введите строку из 0 и 1: ";
    string bits;
    cin >> bits;
    int len = bits.length();
    bool* arr = new bool[len];
    for (int i = 0; i < len; i++) {
        arr[i] = (bits[i] == '1');
    }
    if (currentBitSeq != nullptr) delete currentBitSeq;
    currentBitSeq = new MutableBitSequence(arr, len);
    delete[] arr;
    cout << "Создана BitSequence: ";
    currentBitSeq->Print();
    cout << endl;
}

void bitShow() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    cout << "Текущая BitSequence: ";
    currentBitSeq->Print();
    cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
}

void bitAppend() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    int bit;
    cout << "Введите бит (0 или 1): ";
    cin >> bit;
    currentBitSeq->Append(bit != 0);
    cout << "Результат: ";
    currentBitSeq->Print();
    cout << endl;
}

void bitPrepend() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    int bit;
    cout << "Введите бит (0 или 1): ";
    cin >> bit;
    currentBitSeq->Prepend(bit != 0);
    cout << "Результат: ";
    currentBitSeq->Print();
    cout << endl;
}

void bitInsertAt() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    int index, bit;
    cout << "Введите индекс: ";
    cin >> index;
    cout << "Введите бит (0 или 1): ";
    cin >> bit;
    try {
        currentBitSeq->InsertAt(bit != 0, index);
        cout << "Результат: ";
        currentBitSeq->Print();
        cout << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitGet() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    int index;
    cout << "Введите индекс: ";
    cin >> index;
    try {
        cout << "Бит[" << index << "] = " << currentBitSeq->Get(index) << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitGetSubsequence() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    int start, end;
    cout << "Введите startIndex: ";
    cin >> start;
    cout << "Введите endIndex: ";
    cin >> end;
    try {
        Sequence<bool>* sub = currentBitSeq->GetSubsequence(start, end);
        cout << "Подпоследовательность: ";
        dynamic_cast<BitSequence*>(sub)->Print();
        cout << endl;
        delete sub;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitAnd() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    cout << "Введите вторую BitSequence (строка из 0 и 1): ";
    string bits;
    cin >> bits;
    int len = bits.length();
    bool* arr = new bool[len];
    for (int i = 0; i < len; i++) {
        arr[i] = (bits[i] == '1');
    }
    MutableBitSequence other(arr, len);
    delete[] arr;
    try {
        BitSequence* result = currentBitSeq->BitwiseAnd(&other);
        cout << "AND: ";
        result->Print();
        cout << endl;
        delete result;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitOr() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    cout << "Введите вторую BitSequence (строка из 0 и 1): ";
    string bits;
    cin >> bits;
    int len = bits.length();
    bool* arr = new bool[len];
    for (int i = 0; i < len; i++) {
        arr[i] = (bits[i] == '1');
    }
    MutableBitSequence other(arr, len);
    delete[] arr;
    try {
        BitSequence* result = currentBitSeq->BitwiseOr(&other);
        cout << "OR: ";
        result->Print();
        cout << endl;
        delete result;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitXor() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    cout << "Введите вторую BitSequence (строка из 0 и 1): ";
    string bits;
    cin >> bits;
    int len = bits.length();
    bool* arr = new bool[len];
    for (int i = 0; i < len; i++) {
        arr[i] = (bits[i] == '1');
    }
    MutableBitSequence other(arr, len);
    delete[] arr;
    try {
        BitSequence* result = currentBitSeq->BitwiseXor(&other);
        cout << "XOR: ";
        result->Print();
        cout << endl;
        delete result;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void bitNot() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    BitSequence* result = currentBitSeq->BitwiseNot();
    cout << "NOT: ";
    result->Print();
    cout << endl;
    delete result;
}

void bitLength() {
    if (currentBitSeq == nullptr) {
        cout << "BitSequence не создана.\n";
        return;
    }
    cout << "Длина BitSequence: " << currentBitSeq->GetLength() << endl;
}


void mapReduceTasks() {
    if (isStackMode) {
        if (currentStack == nullptr) {
            cout << "Stack не создан.\n";
            return;
        }

        cout << "\n--- Map-Reduce задачи для Stack ---\n";
        cout << "1. (min, max, avg) за 1 проход\n";
        cout << "2. Медиана\n";
        cout << "3. Список всех префиксов\n";
        cout << "4. Список всех постфиксов\n";
        cout << "5. Поэлементная сумма с отражением\n";
        cout << "Выберите задачу: ";

        int choice;
        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    Sequence<int>* seq = currentStack->GetSubsequence(0, currentStack->GetSize() - 1);
                    auto result = computeMinMaxAvg(seq);
                    cout << "min = " << get<0>(result)
                         << ", max = " << get<1>(result)
                         << ", avg = " << get<2>(result) << endl;
                    delete seq;
                    break;
                }
                case 2: {
                    Sequence<int>* seq = currentStack->GetSubsequence(0, currentStack->GetSize() - 1);
                    double median = computeMedian(seq);
                    cout << "Медиана = " << median << endl;
                    delete seq;
                    break;
                }
                case 3: {
                    Sequence<int>* seq = currentStack->GetSubsequence(0, currentStack->GetSize() - 1);
                    Sequence<Sequence<int>*>* prefixes = computePrefixes(seq);
                    cout << "Префиксы:\n";
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        cout << "  " << *(prefixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < prefixes->GetLength(); i++) {
                        delete prefixes->Get(i);
                    }
                    delete prefixes;
                    delete seq;
                    break;
                }
                case 4: {
                    Sequence<int>* seq = currentStack->GetSubsequence(0, currentStack->GetSize() - 1);
                    Sequence<Sequence<int>*>* suffixes = computeSuffixes(seq);
                    cout << "Постфиксы:\n";
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        cout << "  " << *(suffixes->Get(i)) << endl;
                    }
                    for (int i = 0; i < suffixes->GetLength(); i++) {
                        delete suffixes->Get(i);
                    }
                    delete suffixes;
                    delete seq;
                    break;
                }
                case 5: {
                    Sequence<int>* seq = currentStack->GetSubsequence(0, currentStack->GetSize() - 1);
                    Sequence<int>* result = computeMirrorSum(seq);
                    cout << "Зеркальная сумма: " << *result << endl;
                    delete result;
                    delete seq;
                    break;
                }
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
        return;
    }

    if (isBitMode) {
        cout << "Map-Reduce задачи только для int-последовательностей.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        cout << "Последовательность не создана. Сначала создайте последовательность.\n";
        return;
    }

    cout << "\n--- Map-Reduce задачи (П-задачи) ---\n";
    cout << "1. (min, max, avg) за 1 проход\n";
    cout << "2. Медиана\n";
    cout << "3. Список всех префиксов\n";
    cout << "4. Список всех постфиксов\n";
    cout << "5. Поэлементная сумма с отражением\n";
    cout << "Выберите задачу: ";

    int choice;
    cin >> choice;

    try {
        switch (choice) {
            case 1: {
                auto result = computeMinMaxAvg(currentIntSeq);
                cout << "min = " << get<0>(result)
                     << ", max = " << get<1>(result)
                     << ", avg = " << get<2>(result) << endl;
                break;
            }
            case 2: {
                double median = computeMedian(currentIntSeq);
                cout << "Медиана = " << median << endl;
                break;
            }
            case 3: {
                Sequence<Sequence<int>*>* prefixes = computePrefixes(currentIntSeq);
                cout << "Префиксы:\n";
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    cout << "  " << *(prefixes->Get(i)) << endl;
                }
                for (int i = 0; i < prefixes->GetLength(); i++) {
                    delete prefixes->Get(i);
                }
                delete prefixes;
                break;
            }
            case 4: {
                Sequence<Sequence<int>*>* suffixes = computeSuffixes(currentIntSeq);
                cout << "Постфиксы:\n";
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    cout << "  " << *(suffixes->Get(i)) << endl;
                }
                for (int i = 0; i < suffixes->GetLength(); i++) {
                    delete suffixes->Get(i);
                }
                delete suffixes;
                break;
            }
            case 5: {
                Sequence<int>* result = computeMirrorSum(currentIntSeq);
                cout << "Зеркальная сумма: " << *result << endl;
                delete result;
                break;
            }
            default:
                cout << "Неверный выбор!\n";
        }
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void switchToBitSequence() {
    isBitMode = true;
    isStackMode = false;
    currentSeqType = BIT_SEQUENCE;
    if (currentBitSeq == nullptr) {
        currentBitSeq = new MutableBitSequence();
    }
    cout << "\nПереключено на BitSequence\n";
}

void switchToStack() {
    isStackMode = true;
    isBitMode = false;
    currentSeqType = STACK;
    if (currentStack == nullptr) {
        currentStack = new Stack<int>();
    }
    cout << "\nПереключено на Stack\n";
}

void runTests() {
    cout << "\n--- Запуск всех тестов ---\n";
    runAllTests();
}

int main() {
    cout << "========================================\n";
    cout << "   ЛР №3\n";
    cout << "========================================\n";

    selectInitialType();

    int choice;
    do {
        printMenu();
        cin >> choice;

        if (isStackMode) {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: stackPush(); break;
                case 4: stackPop(); break;
                case 5: stackTop(); break;
                case 6: stackIsEmpty(); break;
                case 7: stackGetSize(); break;
                case 8: stackIndexOf(); break;
                case 9: stackContains(); break;
                case 10: stackFindAllOccurrences(); break;
                case 11: stackConcat(); break;
                case 12: stackMap(); break;
                case 13: stackWhere(); break;
                case 14: stackReduce(); break;
                case 15: stackZip(); break;
                case 16: stackSkip(); break;
                case 17: stackTake(); break;
                case 18: mapReduceTasks(); break;
                case 19: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
        else if (isBitMode) {
            switch (choice) {
                case 1: bitCreate(); break;
                case 2: bitShow(); break;
                case 3: bitAppend(); break;
                case 4: bitPrepend(); break;
                case 5: bitInsertAt(); break;
                case 6: bitGet(); break;
                case 7: bitGetSubsequence(); break;
                case 8: bitAnd(); break;
                case 9: bitOr(); break;
                case 10: bitXor(); break;
                case 11: bitNot(); break;
                case 12: bitLength(); break;
                case 13: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
        else {
            switch (choice) {
                case 1: createSequence(); break;
                case 2: showSequence(); break;
                case 3: appendElement(); break;
                case 4: prependElement(); break;
                case 5: insertAt(); break;
                case 6: getElement(); break;
                case 7: getSubsequence(); break;
                case 8: concatSequence(); break;
                case 9: mapOperation(); break;
                case 10: whereOperation(); break;
                case 11: reduceOperation(); break;
                case 12: zipOperation(); break;
                case 13: skipOperation(); break;
                case 14: takeOperation(); break;
                case 15: switchToBitSequence(); break;
                case 16: switchToStack(); break;
                case 17: mapReduceTasks(); break;
                case 18: runTests(); break;
                case 0:
                    cout << "ЗАВЕРШЕНИЕ РАБОТЫ\n";
                    break;
                default:
                    cout << "Неверный выбор\n";
            }
        }
    } while (choice != 0);

    if (currentIntSeq != nullptr) delete currentIntSeq;
    if (currentBitSeq != nullptr) delete currentBitSeq;
    if (currentStack != nullptr) delete currentStack;

    return 0;
}