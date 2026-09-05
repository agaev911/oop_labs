#pragma once

#include <stdint.h>
#include <assert.h>
#include <iostream>

using namespace std;

class BooleanVector
{
private:

    class BitReference;

public:

    BooleanVector() = default; //конструктор по умолчанию
    BooleanVector(const uint32_t, const bool); //конструктор с параметрами (размер и значение - одно и то же для всех разрядов)
    BooleanVector(const char*); //конструктор из массива const char *

    ~BooleanVector();//деструктор

    BooleanVector(const BooleanVector&); //конструктор копирования
    BooleanVector(BooleanVector&&); //перемещающий конструктор

    BooleanVector& operator=(const BooleanVector&); //присваивание(= )
    BooleanVector& operator=(BooleanVector&&); //перемещающее присваивание

    bool SwapBV(BooleanVector&); //обмен содержимого с другим вектором(swap)
    bool InvertBV(); //инверсия всех компонент вектора
    bool InvertInd(uint32_t); //инверсия i-ой компоненты
    bool SetBit(uint32_t, bool); //инверсия i-ой компоненты
    bool SetBits(uint32_t, uint32_t, bool); //установка в 0 / 1 k компонент, начиная с i - ой
    bool SetAllBits(bool); //установка в 0 / 1 всех компонент вектора

    //побитовое умножение (&, &=)
    BooleanVector operator&(const BooleanVector& other) const;
    BooleanVector& operator&=(const BooleanVector& other);

    //побитовое сложение(| , |=)
    BooleanVector operator|(const BooleanVector& other) const;
    BooleanVector& operator|=(const BooleanVector& other);

    //побитовое исключающее ИЛИ(^, ^=);
    BooleanVector operator^(const BooleanVector& other) const;
    BooleanVector& operator^=(const BooleanVector& other);

    //побитовые сдвиги(<< , >> , <<=, >>=)
    BooleanVector operator<<(uint32_t sdvig) const;
    BooleanVector operator>>(uint32_t sdvig) const;
    BooleanVector& operator<<=(uint32_t sdvig);
    BooleanVector& operator>>=(uint32_t sdvig);

    //побитовая инверсия(~)
    BooleanVector operator~() const;

    //ввод / вывод в консоль(потоковый)
    friend ostream& operator <<(ostream& r, BooleanVector& s) //потоковый вывод
    {
        for (uint32_t index = 0; index < s.numBits_; index++)
        {
            uint32_t byteIndex = index / (8 * sizeof(uint8_t));
            uint32_t bitIndex = index % (8 * sizeof(uint8_t));

            bool bitValue = s.vectorData_[byteIndex] & (1 << bitIndex);
            r << (bitValue ? '1' : '0');
        }
        return r;
    }
    friend istream& operator>>(istream& r, BooleanVector& s) //потоковый ввод
    {
        cout << "Введите количество битов: ";
        r >> s.numBits_;

        uint32_t numBytes = s.numBits_ / (8 * sizeof(uint8_t));
        if (s.numBits_ % (8 * sizeof(uint8_t)) > 0)
        {
            numBytes += 1;
        }

        s.vectorData_ = new uint8_t[numBytes]; //выделяем место

        // Обнуляем все байты
        for (uint32_t i = 0; i < numBytes; i++)
        {
            s.vectorData_[i] = 0;
        }

        cout << "Введите биты (0 или 1 через пробел): " << endl;
        // Устанавливаем биты из строки
        for (uint32_t index = 0; index < s.numBits_; index++)
        {
            bool value;
            r >> value;  // Читаем 0 или 1

            if (value)
            {
                uint32_t byteIndex = index / (8 * sizeof(uint8_t)); //адрес байта
                uint32_t bitIndex = index % (8 * sizeof(uint8_t));  //адрес бита
                s.vectorData_[byteIndex] |= (1 << bitIndex);
            }
        }
        return r;
    }

    // простой вариант, но не позволяет установить значение конкретного бита с помощью присваивания
#if 0
    bool operator[](const uint32_t) const;
#endif
    // позволяет установить значение конкретного бита с помощью присваивания, но более сложный и требует вспомогательного класса
    BitReference operator[](const uint32_t) const;

    uint32_t getLength() const { return numBits_; } //длина (количество бит) вектора

    uint32_t getWeight() const; //вес вектора (количество единичных компонент)

    bool operator==(const BooleanVector& other) const;

private:

    uint8_t* vectorData_ = nullptr;
    uint32_t numBits_ = 0;
};

class BooleanVector::BitReference
{
public:

    BitReference(uint8_t* const, const uint8_t);

    operator bool();

    BitReference& operator=(const bool NewValue);

private:

    uint8_t* bytePtr_;
    uint8_t bitIndex_;
};