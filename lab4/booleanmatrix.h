#pragma once

#include <stdint.h>

#include <iostream>

#include "dynamicarray.h"
#include "booleanvector.h"

class BooleanMatrix
{
public:

    BooleanMatrix() = default; //конструктор по умолчанию
    BooleanMatrix(const uint32_t, const uint32_t, const bool); //с параметрами (количество строк/столбцов и значения разрядов)
    BooleanMatrix(const BooleanMatrix&) = default; //конструктор копирования
    ~BooleanMatrix() = default; //деструктор

    //получение числа строк и столбцов матрицы
    uint32_t numRows() const;
    uint32_t numColumns() const;

    //получение строки([]);
    BooleanVector& operator[](const uint32_t);
    const BooleanVector& operator[](const uint32_t) const;

    void swapMatrix(BooleanMatrix& other);//обмен содержимого с другой матрицей (swap)

    uint32_t getWeight() const; //вес матрицы(количество единичных компонент)

    uint32_t rowWeight(uint32_t rowIndex) const; //вес j - ой строки

    BooleanVector conjunctionRows() const; //конъюнкция всех строк(возвращает булев вектор)
    BooleanVector disjunctionRows() const; //дизъюнкция всех строк(возвращает булев вектор)

    void invertRowBit(uint32_t rowIndex, uint32_t colIndex); //инверсия в i - ой компоненты j - ой строки
    void invertRowBits(uint32_t rowIndex, uint32_t startCol, uint32_t count); //инверсия k компонент j - ой строки, начиная с i - ой компоненты

    void setRowBit(uint32_t rowIndex, uint32_t colIndex, bool value); //установка в 0 / 1 i - ой компоненты j - ой строки
    void setRowBits(uint32_t rowIndex, uint32_t startCol, uint32_t count, bool value); //установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты


private:

    DynamicArray<BooleanVector> matrixData_;
};

//ввод / вывод в консоль(потоковый);
std::ostream& operator<<(std::ostream&, const BooleanMatrix&); //вывод