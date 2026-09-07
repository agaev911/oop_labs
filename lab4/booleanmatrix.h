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

private:

    DynamicArray<BooleanVector> matrixData_;
};

//ввод / вывод в консоль(потоковый);
std::ostream& operator<<(std::ostream&, const BooleanMatrix&); //вывод