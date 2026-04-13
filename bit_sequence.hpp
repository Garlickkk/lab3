#ifndef BIT_SEQUENCE_HPP
#define BIT_SEQUENCE_HPP

#include "sequence.hpp"
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include <iostream>

class MutableBitSequence;
class ImmutableBitSequence;


class BitSequence : public Sequence<bool> {
protected:
    DynamicArray<unsigned char> *data; // указатель на массив байтов
    int length; // кол-во бит

    void setBit(int index, bool value) { // Установка
        int byteIdx = index / 8; // индекс байта
        int bitIdx = index % 8; // позиция бита
        if (value)
            data->Set(byteIdx, data->Get(byteIdx) | (1 << bitIdx)); // or бит в 1
        else
            data->Set(byteIdx, data->Get(byteIdx) & ~(1 << bitIdx)); // and бит в 0
    }

    bool getBit(int index) const { // получение
        int byteIdx = index / 8;
        int bitIdx = index % 8;
        return (data->Get(byteIdx) >> bitIdx) & 1;
    }

    int bytesNeeded(int bits) const { // кол-во байт для хранения битов
        return (bits + 7) / 8;
    }

    // mutable возв this, а immutable  копию
    virtual BitSequence *Instance() = 0;

    void AppendInternal(bool item) { // добавление бита в конец
        int newLen = length + 1;
        if (bytesNeeded(newLen) > data->GetSize()) {
            data->Resize(bytesNeeded(newLen));
            if (data->GetSize() > 0) {
                data->Set(data->GetSize() - 1, 0);
            }
        }
        length = newLen;
        setBit(length - 1, item);
    }

    void PrependInternal(bool item) { // добавление бита в начало
        InsertAtInternal(item, 0);
    }

    void InsertAtInternal(bool item, int index) { // вставка по индексу
        if (index < 0 || index > length)
            throw IndexOutOfRangeException(index, length);

        int oldLen = length;
        bool *temp = new bool[oldLen > 0 ? oldLen : 1];
        for (int i = 0; i < oldLen; i++)
            temp[i] = getBit(i);

        int newLen = oldLen + 1;
        data->Resize(bytesNeeded(newLen));
        for (int i = 0; i < data->GetSize(); i++) // перезаписываем старые значения
            data->Set(i, 0);
        length = newLen;

        for (int i = 0; i < index; i++) // копия до вставки
            setBit(i, temp[i]);
        setBit(index, item); // вставляем новый
        for (int i = index; i < oldLen; i++) // копируем оставшиеся
            setBit(i + 1, temp[i]);

        delete[] temp;
    }

public:
    BitSequence() : data(new DynamicArray<unsigned char>(0)), length(0) {
    }

    BitSequence(bool *items, int count) : length(count) {
        data = new DynamicArray<unsigned char>(bytesNeeded(count));
        for (int i = 0; i < data->GetSize(); i++)
            data->Set(i, 0);
        for (int i = 0; i < count; i++)
            setBit(i, items[i]);
    }

    BitSequence(const BitSequence &other) // копирующий конструктор
        : data(new DynamicArray<unsigned char>(*other.data)), length(other.length) {
    }

    virtual ~BitSequence() override { delete data; }


    bool GetFirst() const override {
        if (length == 0) throw IndexOutOfRangeException("BitSequence пуст");
        return getBit(0);
    }

    bool GetLast() const override {
        if (length == 0) throw IndexOutOfRangeException("BitSequence пуст");
        return getBit(length - 1);
    }

    bool Get(int index) const override { // бит по индексу
        if (index < 0 || index >= length)
            throw IndexOutOfRangeException(index, length);
        return getBit(index);
    }

    int GetLength() const override { return length; }


    Sequence<bool> *GetSubsequence(int startIndex, int endIndex) const override;

    Sequence<bool> *Empty() const override;


    Sequence<bool> *Append(bool item) override {
        BitSequence *inst = Instance();
        inst->AppendInternal(item);
        return inst;
    }

    Sequence<bool> *Prepend(bool item) override {
        BitSequence *inst = Instance();
        inst->PrependInternal(item);
        return inst;
    }

    Sequence<bool> *InsertAt(bool item, int index) override {
        BitSequence *inst = Instance();
        inst->InsertAtInternal(item, index);
        return inst;
    }

    Sequence<bool> *Concat(Sequence<bool> *other) override { //  // Объединить с другой последовательностью
        BitSequence *inst = Instance();
        for (int i = 0; i < other->GetLength(); i++) {
            inst->AppendInternal(other->Get(i));
        }
        return inst;
    }


    BitSequence *BitwiseAnd(BitSequence *other);

    BitSequence *BitwiseOr(BitSequence *other);

    BitSequence *BitwiseXor(BitSequence *other);

    BitSequence *BitwiseNot();

    void Print(std::ostream &os = std::cout) const {
        for (int i = 0; i < length; i++) {
            os << (getBit(i) ? '1' : '0');
        }
    }
};

//Mutable
class MutableBitSequence : public BitSequence {
protected:
    BitSequence *Instance() override {
        return this;
    }

public:
    MutableBitSequence() : BitSequence() {
    }

    MutableBitSequence(bool *items, int count) : BitSequence(items, count) {
    }

    MutableBitSequence(const BitSequence &other) : BitSequence(other) {
    }

    ~MutableBitSequence() override = default;
};

//Immutable
class ImmutableBitSequence : public BitSequence {
protected:
    BitSequence *Instance() override {
        return new MutableBitSequence(*this);
    }

public:
    ImmutableBitSequence() : BitSequence() {
    }

    ImmutableBitSequence(bool *items, int count) : BitSequence(items, count) {
    }

    ImmutableBitSequence(const BitSequence &other) : BitSequence(other) {
    }

    ~ImmutableBitSequence() override = default;
};

//методы BitSequence для Mutable
inline Sequence<bool> *BitSequence::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || startIndex >= length)
        throw IndexOutOfRangeException(startIndex, length);
    if (endIndex < 0 || endIndex >= length)
        throw IndexOutOfRangeException(endIndex, length);
    if (endIndex < startIndex)
        throw IndexOutOfRangeException("startIndex > endIndex");

    int count = endIndex - startIndex + 1;
    bool *buf = new bool[count];
    for (int i = 0; i < count; i++) {
        buf[i] = getBit(startIndex + i);
    }
    BitSequence *result = new MutableBitSequence(buf, count);
    delete[] buf;
    return result;
}

inline Sequence<bool> *BitSequence::Empty() const {
    return new MutableBitSequence();
}

inline BitSequence *BitSequence::BitwiseAnd(BitSequence *other) {
    if (length != other->length)
        throw InvalidArgumentException("Длины BitSequence должны совпадать");
    MutableBitSequence *result = new MutableBitSequence();
    result->data->Resize(data->GetSize());
    for (int i = 0; i < data->GetSize(); i++) {
        result->data->Set(i, data->Get(i) & other->data->Get(i));
    }
    result->length = length;
    return result;
}

inline BitSequence *BitSequence::BitwiseOr(BitSequence *other) {
    if (length != other->length)
        throw InvalidArgumentException("Длины BitSequence должны совпадать");
    MutableBitSequence *result = new MutableBitSequence();
    result->data->Resize(data->GetSize());
    for (int i = 0; i < data->GetSize(); i++) {
        result->data->Set(i, data->Get(i) | other->data->Get(i));
    }
    result->length = length;
    return result;
}

inline BitSequence *BitSequence::BitwiseXor(BitSequence *other) {
    if (length != other->length)
        throw InvalidArgumentException("Длины BitSequence должны совпадать");
    MutableBitSequence *result = new MutableBitSequence();
    result->data->Resize(data->GetSize());
    for (int i = 0; i < data->GetSize(); i++) {
        result->data->Set(i, data->Get(i) ^ other->data->Get(i));
    }
    result->length = length;
    return result;
}

inline BitSequence *BitSequence::BitwiseNot() {
    MutableBitSequence *result = new MutableBitSequence();
    result->data->Resize(data->GetSize());
    for (int i = 0; i < data->GetSize(); i++) {
        result->data->Set(i, ~data->Get(i));
    }
    result->length = length;
    return result;
}

#endif // BIT_SEQUENCE_HPP