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

// Stack тесты
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

void test_stack_move() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2(std::move(s1));
    assert(s2.GetSize() == 3);
    assert(s2.Top() == 3);
    assert(s1.IsEmpty());
    assert(s1.GetSize() == 0);


    assert(s2.Pop() == 3);
    assert(s2.Pop() == 2);
    assert(s2.Pop() == 1);
    assert(s2.IsEmpty());
}


void test_stack_move_assignment() {
    Stack<int> s1;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);

    Stack<int> s2;
    s2.Push(99);


    s2 = std::move(s1);

    assert(s2.GetSize() == 3);
    assert(s2.Top() == 3);
    assert(s1.IsEmpty());


    assert(s2.Pop() == 3);
    assert(s2.Pop() == 2);
    assert(s2.Pop() == 1);
    assert(s2.IsEmpty());
}

void test_stack_map() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);

    Stack<int>* mapped = s.Map([](int x) { return x * 2; });
    assert(mapped->GetSize() == 3);

    Sequence<int>* seq = mapped->GetSubsequence(0, mapped->GetSize() - 1);
    assert(seq->Get(0) == 2);
    assert(seq->Get(1) == 4);
    assert(seq->Get(2) == 6);

    delete seq;
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

    Sequence<int>* seq = filtered->GetSubsequence(0, filtered->GetSize() - 1);
    assert(seq->Get(0) == 4);
    assert(seq->Get(1) == 5);

    delete seq;
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

    Sequence<int>* seq = result->GetSubsequence(0, 3);
    assert(seq->Get(0) == 1);
    assert(seq->Get(1) == 2);
    assert(seq->Get(2) == 3);
    assert(seq->Get(3) == 4);

    delete seq;
    delete result;
}

void test_stack_getsubsequence() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);

    Sequence<int>* sub = s.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);
    assert(sub->Get(2) == 4);

    delete sub;
}

void test_stack_skip_take() {
    Stack<int> s;
    s.Push(1);
    s.Push(2);
    s.Push(3);
    s.Push(4);
    s.Push(5);

    Stack<int>* skipped = s.Skip(2);
    assert(skipped->GetSize() == 3);
    Sequence<int>* seq1 = skipped->GetSubsequence(0, 2);
    assert(seq1->Get(0) == 3);
    assert(seq1->Get(1) == 4);
    assert(seq1->Get(2) == 5);
    delete seq1;
    delete skipped;

    Stack<int>* taken = s.Take(3);
    assert(taken->GetSize() == 3);
    Sequence<int>* seq2 = taken->GetSubsequence(0, 2);
    assert(seq2->Get(0) == 1);
    assert(seq2->Get(1) == 2);
    assert(seq2->Get(2) == 3);
    delete seq2;
    delete taken;
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

    Sequence<int>* seq = result->GetSubsequence(0, result->GetSize() - 1);
    assert(seq->Get(0) == 0);
    assert(seq->Get(1) == 3);
    assert(seq->Get(2) == 6);

    delete seq;
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

    Sequence<int>* seq = zipped->GetSubsequence(0, 2);
    assert(seq->Get(0) == 11);
    assert(seq->Get(1) == 22);
    assert(seq->Get(2) == 33);

    delete seq;
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

    s.Push(1);
    s.Push(2);

    try {
        s.GetSubsequence(5, 10);
        assert(false);
    } catch (const IndexOutOfRangeException&) {
    }

    try {
        s.Skip(-1);
        assert(false);
    } catch (const InvalidArgumentException&) {
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

    Sequence<int>* seq = doubled->GetSubsequence(N - 1, N - 1);
    assert(seq->Get(0) == 2 * (N - 1));

    delete seq;
    delete doubled;

    for (int i = N - 1; i >= 0; i--) {
        assert(s.Pop() == i);
    }
    assert(s.IsEmpty());
}

// BitSequence тесты
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

// П-задачи
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
    runTest(test_tasks, "П-задачи");

    runTest(test_stack_basic, "Stack: Push/Pop/Top/IsEmpty");
    runTest(test_stack_move, "Stack: перемещающий конструктор");
    runTest(test_stack_move_assignment, "Stack: перемещающее присваивание");
    runTest(test_stack_map, "Stack: Map");
    runTest(test_stack_where, "Stack: Where");
    runTest(test_stack_reduce, "Stack: Reduce");
    runTest(test_stack_indexof, "Stack: IndexOf");
    runTest(test_stack_contains, "Stack: Contains");
    runTest(test_stack_concat, "Stack: Concat");
    runTest(test_stack_getsubsequence, "Stack: GetSubsequence");
    runTest(test_stack_skip_take, "Stack: Skip/Take");
    runTest(test_stack_find_all_occurrences, "Stack: FindAllOccurrences");
    runTest(test_stack_zip, "Stack: Zip");
    runTest(test_stack_exceptions, "Stack: обработка исключений");
    runTest(test_stack_large_data, "Stack: большой объем данных");

    std::cout << "\n--------------------------------------" << std::endl;
    std::cout << "ИТОГО: Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}