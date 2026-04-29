#include <iostream>
#include <cassert>
#include <string>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "bit_sequence.hpp"
#include "map_reduce_tasks.hpp"
#include "stack.hpp"

int passed = 0;
int failed = 0;

void runTest(void (*test)(), const std::string& name) {
    try {
        test();
        passed++;
        std::cout << "  [OK] " << name << std::endl;
    } catch (const std::exception& e) {
        failed++;
        std::cout << "  [НЕУДАЧА] " << name << ": " << e.what() << std::endl;
    }
}

// DynamicArray
void test_da() {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    assert(a.GetSize() == 3);
    assert(a.Get(0) == 1);
    assert(a.Get(2) == 3);

    a.Set(1, 99);
    assert(a.Get(1) == 99);

    a.Resize(5);
    assert(a.GetSize() == 5);
}

// LinkedList
void test_ll() {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 1);
    assert(list.GetLast() == 3);

    list.Append(4);
    assert(list.GetLength() == 4);
    assert(list.GetLast() == 4);

    list.Prepend(0);
    assert(list.GetFirst() == 0);

    list.InsertAt(99, 2);
    assert(list.Get(2) == 99);
}

// MutableArraySequence
void test_mas() {
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLength() == 4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);

    seq.InsertAt(99, 2);
    assert(seq.Get(2) == 99);
}

// ImmutableArraySequence
void test_ias() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);
    assert(newSeq != &seq);

    delete newSeq;
}

// MutableListSequence
void test_mls() {
    int items[] = {1, 2, 3};
    MutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);
}

// ImmutableListSequence
void test_ils() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);

    delete newSeq;
}

// Map/Reduce для Sequence
void test_map_reduce_sequence() {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(items, 5);

    Sequence<int>* mapped = seq.Map([](int x) { return x * 2; });
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);
    delete mapped;

    Sequence<int>* filtered = seq.Where([](int x) { return x > 3; });
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 4);
    delete filtered;

    int sum = seq.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 15);
}

//Stack

void test_stack_basic() {
    Stack<int> s;
    assert(s.IsEmpty());
    assert(s.GetSize() == 0);

    s.Push(1);
    s.Push(2);
    s.Push(3);

    assert(!s.IsEmpty());
    assert(s.GetSize() == 3);
    assert(s.Top() == 3);

    int val = s.Pop();
    assert(val == 3);
    assert(s.GetSize() == 2);
    assert(s.Top() == 2);

    val = s.Pop();
    assert(val == 2);
    val = s.Pop();
    assert(val == 1);
    assert(s.IsEmpty());
}

void test_stack_copy() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2(s1);

    assert(s2.GetSize() == 3);
    assert(s2.Top() == 3);
    assert(s1.GetSize() == 3);

    assert(s2.Pop() == 3);
    assert(s2.Pop() == 2);
    assert(s2.Pop() == 1);
    assert(s2.IsEmpty());

    assert(s1.GetSize() == 3);
    assert(s1.Top() == 3);
}

void test_stack_from_array() {
    int items[] = {10, 20, 30};
    Stack<int> s(items, 3);

    assert(s.GetSize() == 3);
    assert(s.Top() == 30);

    assert(s.Pop() == 30);
    assert(s.Pop() == 20);
    assert(s.Pop() == 10);
    assert(s.IsEmpty());
}

void test_stack_map() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int>* mapped = s.Map([](int x) { return x * 2; });
    assert(mapped->GetSize() == 3);

    assert(mapped->Pop() == 6);
    assert(mapped->Pop() == 4);
    assert(mapped->Pop() == 2);
    assert(mapped->IsEmpty());

    delete mapped;
}

void test_stack_map_index() {
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    s.Push(30);

    Stack<int>* mapped = s.Map([](int x, int i) { return x + i; });

    assert(mapped->GetSize() == 3);
    assert(mapped->Pop() == 32);
    assert(mapped->Pop() == 21);
    assert(mapped->Pop() == 10);

    delete mapped;
}

void test_stack_where() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);

    Stack<int>* filtered = s.Where([](int x) { return x > 3; });
    assert(filtered->GetSize() == 2);

    assert(filtered->Pop() == 5);
    assert(filtered->Pop() == 4);
    assert(filtered->IsEmpty());

    delete filtered;
}

void test_stack_reduce() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    int sum = s.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 10);

    int product = s.Reduce([](int a, int b) { return a * b; }, 1);
    assert(product == 24);
}

void test_stack_indexof() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int> sub;
    sub.Push(1);
    sub.Push(2);

    int idx = s.IndexOf(sub);
    assert(idx == 0);

    Stack<int> sub2;
    sub2.Push(2);
    sub2.Push(3);

    idx = s.IndexOf(sub2);
    assert(idx == 1);

    Stack<int> sub3;
    sub3.Push(9);
    sub3.Push(9);
    idx = s.IndexOf(sub3);
    assert(idx == -1);
}

void test_stack_indexof_empty() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);

    Stack<int> empty;
    int idx = s.IndexOf(empty);
    assert(idx == 0);
}

void test_stack_contains() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int> sub;
    sub.Push(2);
    sub.Push(3);

    assert(s.Contains(sub));

    Stack<int> sub2;
    sub2.Push(3);
    sub2.Push(4);

    assert(!s.Contains(sub2));
}

void test_stack_concat() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);

    Stack<int> s2;
    s2.Push(3);
    s2.Push(4);

    Stack<int>* result = s1.Concat(&s2);
    assert(result->GetSize() == 4);

    assert(result->Pop() == 4);
    assert(result->Pop() == 3);
    assert(result->Pop() == 2);
    assert(result->Pop() == 1);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_find_all_occurrences() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(1);
    s.Push(2);

    Stack<int> sub;
    sub.Push(1);
    sub.Push(2);

    Stack<int>* result = s.FindAllOccurrences(sub);
    assert(result->GetSize() == 3);

    assert(result->Pop() == 6);
    assert(result->Pop() == 3);
    assert(result->Pop() == 0);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_find_all_occurrences_none() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);

    Stack<int> sub;
    sub.Push(9);

    Stack<int>* result = s.FindAllOccurrences(sub);
    assert(result->GetSize() == 0);
    assert(result->IsEmpty());

    delete result;
}

void test_stack_zip() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2;
    s2.Push(10);
    s2.Push(20);
    s2.Push(30);
    s2.Push(40);

    Stack<int>* zipped = s1.Zip(&s2, [](int a, int b) { return a + b; });
    assert(zipped->GetSize() == 3);

    assert(zipped->Pop() == 33);
    assert(zipped->Pop() == 22);
    assert(zipped->Pop() == 11);
    assert(zipped->IsEmpty());

    delete zipped;
}

void test_stack_exceptions() {
    Stack<int> s;

    try {
        s.Pop();
        assert(false);
    } catch (const EmptyContainerException&) {
    } catch (...) {
        assert(false);
    }

    try {
        s.Top();
        assert(false);
    } catch (const EmptyContainerException&) {
    }
}

void test_stack_large_data() {
    Stack<int> s;
    const int N = 1000;

    for (int i = 0; i < N; i++) {
        s.Push(i);
    }

    assert(s.GetSize() == N);
    assert(s.Top() == N - 1);

    int sum = s.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == N * (N - 1) / 2);

    Stack<int>* doubled = s.Map([](int x) { return x * 2; });
    assert(doubled->GetSize() == N);

    Stack<int> tempCopy(*doubled);
    while (!tempCopy.IsEmpty()) {
        int val = tempCopy.Pop();
        assert(val % 2 == 0);
        assert(val >= 0 && val <= 2 * (N - 1));
    }
    delete doubled;

    for (int i = N - 1; i >= 0; i--) {
        assert(s.Pop() == i);
    }
    assert(s.IsEmpty());
}

void test_stack_string() {
    Stack<std::string> s;
    s.Push("hello");
    s.Push("world");

    assert(s.GetSize() == 2);
    assert(s.Top() == "world");

    assert(s.Pop() == "world");
    assert(s.Pop() == "hello");
    assert(s.IsEmpty());
}

//BitSequence

void test_mutable_bit() {
    bool items[] = {true, false, true, true};
    MutableBitSequence bs(items, 4);
    assert(bs.GetLength() == 4);
    assert(bs.Get(0) == true);
    assert(bs.Get(1) == false);

    bs.Append(false);
    assert(bs.GetLength() == 5);
    assert(bs.Get(4) == false);
}

void test_immutable_bit() {
    bool items[] = {true, false, true};
    ImmutableBitSequence seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<bool>* newSeq = seq.Append(false);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);

    delete newSeq;
}

//П-задачи

void test_tasks() {
    int items[] = {3, 1, 4, 1, 5, 9};
    MutableArraySequence<int> seq(items, 6);

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);

    int items2[] = {3, 1, 4, 1, 5};
    MutableArraySequence<int> seq2(items2, 5);
    assert(computeMedian(&seq2) == 3.0);

    int items3[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq3(items3, 5);
    Sequence<int>* mirror = computeMirrorSum(&seq3);
    assert(mirror->Get(0) == 6);
    assert(mirror->Get(2) == 6);
    delete mirror;
}

void test_stack_tasks() {
    Stack<int> s;
    s.Push(3);
    s.Push(1);
    s.Push(4);
    s.Push(1);
    s.Push(5);
    s.Push(9);

    MutableArraySequence<int> seq;
    Stack<int> tempCopy(s);
    Stack<int> reversed;
    while (!tempCopy.IsEmpty()) reversed.Push(tempCopy.Pop());
    while (!reversed.IsEmpty()) seq.Append(reversed.Pop());

    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);
    assert(std::get<1>(result) == 9.0);
}


void runAllTests() {
    passed = 0;
    failed = 0;

    std::cout << "\nЗапуск тестов\n" << std::endl;

    runTest(test_da, "DynamicArray");
    runTest(test_ll, "LinkedList");
    runTest(test_mas, "MutableArraySequence");
    runTest(test_ias, "ImmutableArraySequence");
    runTest(test_mls, "MutableListSequence");
    runTest(test_ils, "ImmutableListSequence");
    runTest(test_map_reduce_sequence, "Map/Reduce/Where для Sequence");

    runTest(test_mutable_bit, "MutableBitSequence");
    runTest(test_immutable_bit, "ImmutableBitSequence");

    runTest(test_stack_basic, "Stack: Push/Pop/Top/IsEmpty");
    runTest(test_stack_copy, "Stack: копирующий конструктор");
    runTest(test_stack_from_array, "Stack: конструктор из массива");
    runTest(test_stack_map, "Stack: Map");
    runTest(test_stack_map_index, "Stack: Map с индексом");
    runTest(test_stack_where, "Stack: Where");
    runTest(test_stack_reduce, "Stack: Reduce");
    runTest(test_stack_indexof, "Stack: IndexOf");
    runTest(test_stack_indexof_empty, "Stack: IndexOf (пустая подпоследовательность)");
    runTest(test_stack_contains, "Stack: Contains");
    runTest(test_stack_concat, "Stack: Concat");
    runTest(test_stack_find_all_occurrences, "Stack: FindAllOccurrences");
    runTest(test_stack_find_all_occurrences_none, "Stack: FindAllOccurrences (ничего не найдено)");
    runTest(test_stack_zip, "Stack: Zip");
    runTest(test_stack_exceptions, "Stack: обработка исключений");
    runTest(test_stack_large_data, "Stack: большой объем данных");
    runTest(test_stack_string, "Stack: строки (шаблонность)");

    runTest(test_tasks, "П-задачи на Sequence");
    runTest(test_stack_tasks, "П-задачи через Stack");

    std::cout << "\n--------------------------------------" << std::endl;
    std::cout << "ИТОГО: Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}