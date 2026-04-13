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

using namespace std;


void runAllTests();

Sequence<int>* currentIntSeq = nullptr;
MutableBitSequence* currentBitSeq = nullptr;
Stack<int>* currentStack = nullptr;

enum SeqType {
    ARRAY_MUTABLE,
    ARRAY_IMMUTABLE,
    LIST_MUTABLE,
    LIST_IMMUTABLE,
    BIT_SEQUENCE
};

SeqType currentSeqType = ARRAY_MUTABLE;
bool isBitMode = false;

void selectInitialType() {
    cout << "\n========================================\n";
    cout << "   ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ\n";
    cout << "========================================\n";
    cout << "1. MutableArraySequence   (изменяемый массив)\n";
    cout << "2. ImmutableArraySequence (неизменяемый массив)\n";
    cout << "3. MutableListSequence    (изменяемый список)\n";
    cout << "4. ImmutableListSequence  (неизменяемый список)\n";
    cout << "5. BitSequence            (битовая последовательность)\n";
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

    switch (choice) {
        case 1:
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableArraySequence<int>();
            cout << "\nСоздана пустая MutableArraySequence<int>\n";
            break;
        case 2:
            currentSeqType = ARRAY_IMMUTABLE;
            isBitMode = false;
            currentIntSeq = new ImmutableArraySequence<int>();
            cout << "\nСоздана пустая ImmutableArraySequence<int>\n";
            break;
        case 3:
            currentSeqType = LIST_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableListSequence<int>();
            cout << "\nСоздана пустая MutableListSequence<int>\n";
            break;
        case 4:
            currentSeqType = LIST_IMMUTABLE;
            isBitMode = false;
            currentIntSeq = new ImmutableListSequence<int>();
            cout << "\nСоздана пустая ImmutableArraySequence<int>\n";
            break;
        case 5:
            currentSeqType = BIT_SEQUENCE;
            isBitMode = true;
            currentBitSeq = new MutableBitSequence();
            cout << "\nСоздана пустая MutableBitSequence\n";
            break;
        default:
            cout << "\nНеверный выбор! Создана последовательность по умолчанию.\n";
            currentSeqType = ARRAY_MUTABLE;
            isBitMode = false;
            currentIntSeq = new MutableArraySequence<int>();
    }
}

void printMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Создать новую последовательность (int)\n";
    cout << "2. Показать текущую последовательность\n";
    cout << "3. Добавить элемент в конец (Append)\n";
    cout << "4. Добавить элемент в начало (Prepend)\n";
    cout << "5. Вставить элемент по индексу (InsertAt)\n";
    cout << "6. Получить элемент по индексу (Get)\n";
    cout << "7. Получить подпоследовательность (GetSubsequence)\n";
    cout << "8. Объединить с другой последовательностью (Concat)\n";
    cout << "9. Map (применить функцию ко всем элементам)\n";
    cout << "10. Where (фильтрация)\n";
    cout << "11. Reduce (свёртка)\n";
    cout << "12. Zip (поэлементная операция с другой последовательностью)\n";
    cout << "13. Skip (пропустить N элементов)\n";
    cout << "14. Take (взять N элементов)\n";
    cout << "15. Работа с BitSequence\n";
    cout << "16. Map-Reduce задачи (П-задачи)\n";
    cout << "17. Запустить все тесты\n";
    cout << "18. Работа со Стеком \n";
    cout << "0. Выход\n";
    cout << "==========================\n";
    cout << "Текущий тип: ";
    switch (currentSeqType) {
        case ARRAY_MUTABLE:   cout << "MutableArraySequence"; break;
        case ARRAY_IMMUTABLE: cout << "ImmutableArraySequence"; break;
        case LIST_MUTABLE:    cout << "MutableListSequence"; break;
        case LIST_IMMUTABLE:  cout << "ImmutableListSequence"; break;
        case BIT_SEQUENCE:    cout << "BitSequence"; break;
    }
    cout << "\n==========================\n";
    cout << "Выберите действие: ";
}

void printBitMenu() {
    cout << "\n========== BitSequence ==========\n";
    cout << "1. Создать BitSequence из строки (например: 10110)\n";
    cout << "2. Показать текущую BitSequence\n";
    cout << "3. Append бит\n";
    cout << "4. Prepend бит\n";
    cout << "5. InsertAt бит\n";
    cout << "6. Get бит по индексу\n";
    cout << "7. Побитовое AND с другой BitSequence\n";
    cout << "8. Побитовое OR с другой BitSequence\n";
    cout << "9. Побитовое XOR с другой BitSequence\n";
    cout << "10. Побитовое NOT\n";
    cout << "11. Получить длину\n";
    cout << "0. Вернуться в главное меню\n";
    cout << "=================================\n";
    cout << "Выберите действие: ";
}

void createSequence() {
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
            isBitMode = false;
            cout << "Создана MutableArraySequence\n";
            break;
        case 2:
            if (items.empty()) {
                currentIntSeq = new ImmutableArraySequence<int>();
            } else {
                currentIntSeq = new ImmutableArraySequence<int>(items.data(), items.size());
            }
            currentSeqType = ARRAY_IMMUTABLE;
            isBitMode = false;
            cout << "Создана ImmutableArraySequence\n";
            break;
        case 3:
            if (items.empty()) {
                currentIntSeq = new MutableListSequence<int>();
            } else {
                currentIntSeq = new MutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_MUTABLE;
            isBitMode = false;
            cout << "Создана MutableListSequence\n";
            break;
        case 4:
            if (items.empty()) {
                currentIntSeq = new ImmutableListSequence<int>();
            } else {
                currentIntSeq = new ImmutableListSequence<int>(items.data(), items.size());
            }
            currentSeqType = LIST_IMMUTABLE;
            isBitMode = false;
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
    if (isBitMode) {
        if (currentBitSeq == nullptr) {
            cout << "BitSequence не создана. Сначала выполните пункт 1 в меню BitSequence.\n";
            return;
        }
        cout << "Текущая BitSequence: ";
        currentBitSeq->Print();
        cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
    } else {
        if (currentIntSeq == nullptr) {
            cout << "Последовательность не создана. Сначала выполните пункт 1.\n";
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
    if (isBitMode) {
        cout << "Concat для BitSequence не реализован.\n";
        return;
    }

    if (currentIntSeq == nullptr) {
        cout << "Текущая последовательность не создана.\n";
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
    if (isBitMode) {
        cout << "Map для BitSequence не реализован.\n";
        return;
    }

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
    if (isBitMode) {
        cout << "Where для BitSequence не реализован.\n";
        return;
    }

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
    if (isBitMode) {
        cout << "Reduce для BitSequence не реализован.\n";
        return;
    }

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
    if (isBitMode) {
        cout << "Zip для BitSequence не реализован.\n";
        return;
    }

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
    if (isBitMode) {
        cout << "Skip для BitSequence не реализован.\n";
        return;
    }

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
    if (isBitMode) {
        cout << "Take для BitSequence не реализован.\n";
        return;
    }

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

void bitSequenceMenu() {
    if (!isBitMode) {
        cout << "Вы не в режиме BitSequence. Используйте пункт 1 главного меню для создания int-последовательности,\n";
        cout << "или перезапустите программу и выберите BitSequence в начальном меню.\n";
        return;
    }

    int choice;
    do {
        printBitMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
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
                break;
            }
            case 2:
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                } else {
                    cout << "Текущая BitSequence: ";
                    currentBitSeq->Print();
                    cout << " (длина: " << currentBitSeq->GetLength() << ")\n";
                }
                break;
            case 3: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
                }
                int bit;
                cout << "Введите бит (0 или 1): ";
                cin >> bit;
                currentBitSeq->Append(bit != 0);
                cout << "Результат: ";
                currentBitSeq->Print();
                cout << endl;
                break;
            }
            case 4: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
                }
                int bit;
                cout << "Введите бит (0 или 1): ";
                cin >> bit;
                currentBitSeq->Prepend(bit != 0);
                cout << "Результат: ";
                currentBitSeq->Print();
                cout << endl;
                break;
            }
            case 5: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
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
                break;
            }
            case 6: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
                }
                int index;
                cout << "Введите индекс: ";
                cin >> index;
                try {
                    cout << "Бит[" << index << "] = " << currentBitSeq->Get(index) << endl;
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 7: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
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
                break;
            }
            case 8: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
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
                break;
            }
            case 9: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
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
                break;
            }
            case 10: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
                }
                BitSequence* result = currentBitSeq->BitwiseNot();
                cout << "NOT: ";
                result->Print();
                cout << endl;
                delete result;
                break;
            }
            case 11: {
                if (currentBitSeq == nullptr) {
                    cout << "BitSequence не создана.\n";
                    break;
                }
                cout << "Длина BitSequence: " << currentBitSeq->GetLength() << endl;
                break;
            }
            case 0:
                cout << "Возврат в главное меню.\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
}

void mapReduceTasks() {
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
                std::tuple<double, double, double> result = computeMinMaxAvg(currentIntSeq);
                cout << "min = " << std::get<0>(result)
                     << ", max = " << std::get<1>(result)
                     << ", avg = " << std::get<2>(result) << endl;
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

void stackMenu() {
    if (currentStack == nullptr) {
        currentStack = new Stack<int>();
        cout << "Создан новый пустой стек\n";
    }

    int choice;
    do {
        cout << "\n========== МЕНЮ СТЕКА ==========\n";
        cout << "1. Push (добавить элемент на вершину)\n";
        cout << "2. Pop (удалить верхний элемент)\n";
        cout << "3. Top (посмотреть верхний элемент)\n";
        cout << "4. Показать весь стек\n";
        cout << "5. Map (применить функцию ко всем элементам)\n";
        cout << "6. Where (фильтрация)\n";
        cout << "7. Reduce (свёртка)\n";
        cout << "8. Sort (сортировка)\n";
        cout << "9. Получить размер стека\n";
        cout << "10. Проверить, пуст ли стек\n";
        cout << "11. Создать новый пустой стек\n";
        cout << "0. Назад\n";
        cout << "======================================\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Введите значение: ";
                cin >> val;
                currentStack->Push(val);
                cout << "Добавлено. Текущий стек: " << *currentStack << endl;
                break;
            }
            case 2: {
                try {
                    int val = currentStack->Pop();
                    cout << "Удалён элемент: " << val << endl;
                    cout << "Стек после удаления: " << *currentStack << endl;
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                try {
                    cout << "Верхний элемент: " << currentStack->Top() << endl;
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 4:
                cout << *currentStack << endl;
                break;
            case 5: {
                int arg;
                cout << "Введите множитель для x*N: ";
                cin >> arg;
                Sequence<int>* mapped = currentStack->Map([arg](int x) { return x * arg; });
                cout << "Результат Map: " << *mapped << endl;
                delete mapped;
                break;
            }
            case 6: {
                int threshold;
                cout << "Фильтр > N. Введите N: ";
                cin >> threshold;
                Sequence<int>* filtered = currentStack->Where([threshold](int x) { return x > threshold; });
                cout << "Результат Where: " << *filtered << endl;
                delete filtered;
                break;
            }
            case 7: {
                int sum = currentStack->Reduce([](int a, int b) { return a + b; }, 0);
                cout << "Сумма элементов: " << sum << endl;
                break;
            }
            case 8: {
                Stack<int>* sorted = currentStack->Sort();
                cout << "Отсортированный стек: " << *sorted << endl;
                delete sorted;
                break;
            }
            case 9:
                cout << "Размер стека: " << currentStack->GetSize() << endl;
                break;
            case 10:
                cout << (currentStack->IsEmpty() ? "Стек пуст" : "Стек не пуст") << endl;
                break;
            case 11:
                delete currentStack;
                currentStack = new Stack<int>();
                cout << "Создан новый пустой стек\n";
                break;
            case 0:
                cout << "Возврат в главное меню\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);
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
            case 15: bitSequenceMenu(); break;
            case 16: mapReduceTasks(); break;
            case 17: runTests(); break;
            case 18: stackMenu(); break;
            case 0:
                cout << "ЗАВЕРШЕНИЕ РАБОТЫ \n";
                break;
            default:
                cout << "Неверный выбор\n";
        }
    } while (choice != 0);

    if (currentIntSeq != nullptr) delete currentIntSeq;
    if (currentBitSeq != nullptr) delete currentBitSeq;
    if (currentStack != nullptr) delete currentStack;

    return 0;
}