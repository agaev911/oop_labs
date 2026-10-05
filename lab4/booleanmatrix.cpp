#include "booleanvector.h"
#include "booleanmatrix.h"

//с параметрами(количество строк / столбцов и значения разрядов)
BooleanMatrix::BooleanMatrix(const uint32_t numRows, const uint32_t numColumns, const bool initialValue)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_ += BooleanVector(numColumns, initialValue);
    }
}

//конструктор из матрицы char
BooleanMatrix::BooleanMatrix(const char** charMatrix, uint32_t numRows, uint32_t numColumns)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        // Создаём строку из numColumns битов, все = false
        BooleanVector row(numColumns, false);

        for (uint32_t colIndex = 0; colIndex < numColumns; ++colIndex)
        {
            if (charMatrix[rowIndex][colIndex] == '1')
            {
                row.SetBit(colIndex, true);
            }
            // Если '0' — оставляем false
        }

        // Добавляем строку в матрицу
        matrixData_ += row;
    }
}

//получение числа строк и столбцов матрицы
uint32_t BooleanMatrix::numRows() const
{
    return matrixData_.arrayLength();
}
uint32_t BooleanMatrix::numColumns() const
{
    return matrixData_.arrayLength() > 0 ? matrixData_[0].getLength() : 0;
}

//обмен содержимого с другой матрицей(swap)
void BooleanMatrix::swapMatrix(BooleanMatrix& other)
{
    matrixData_.swapArrays(other.matrixData_);
}


//ввод / вывод в консоль(потоковый)
ostream& operator<<(ostream& r, const BooleanMatrix& booleanMatrix) //вывод
{
    uint32_t numRows = booleanMatrix.numRows();

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        r << booleanMatrix[rowIndex] << endl;
    }

    return r;
}
istream& operator>>(istream& r, BooleanMatrix& matrix) //ввод
{
    uint32_t numRows, numColumns;

    cout << "Введите количество строк, столбцов и значения разрядов: \n";
    r >> numRows >> numColumns;

    matrix = BooleanMatrix(numRows, numColumns, false);

    for (uint32_t i = 0; i < numRows; ++i)
    {
        r >> matrix[i];
    }

    return r;
}

//вес матрицы(количество единичных компонент)
uint32_t BooleanMatrix::getWeight() const
{
    uint32_t weight = 0;
    for (uint32_t i = 0; i < numRows(); ++i)
    {
        weight += matrixData_[i].getWeight();
    }
    return weight;
}

//конъюнкция всех строк(возвращает булев вектор)
BooleanVector BooleanMatrix::conjunctionRows() const
{
    BooleanVector result = matrixData_[0];  // Начинаем с первой строки

    for (uint32_t i = 1; i < numRows(); ++i)
    {
        result &= matrixData_[i];  // Построчное И
    }

    return result;
}
//дизъюнкция всех строк(возвращает булев вектор)
BooleanVector BooleanMatrix::disjunctionRows() const
{
    BooleanVector result = matrixData_[0];  // Начинаем с первой строки

    for (uint32_t i = 1; i < numRows(); ++i)
    {
        result |= matrixData_[i];  // Построчное ИЛИ
    }

    return result;
}

//вес j - ой строки
uint32_t BooleanMatrix::rowWeight(uint32_t rowIndex) const
{
    if (rowIndex >= numRows()) return 0;
    return matrixData_[rowIndex].getWeight();
}

//инверсия в i - ой компоненты j - ой строки
void BooleanMatrix::invertRowBit(uint32_t rowIndex, uint32_t colIndex)
{
    if (rowIndex < numRows())
    {
        matrixData_[rowIndex].InvertInd(colIndex);
    }
}
//инверсия k компонент j - ой строки, начиная с i - ой компоненты
void BooleanMatrix::invertRowBits(uint32_t rowIndex, uint32_t startCol, uint32_t count)
{
    if (rowIndex < numRows())
    {
        for (uint32_t i = 0; i < count; ++i)
        {
            matrixData_[rowIndex].InvertInd(startCol + i);
        }
    }
}

//установка в 0 / 1 i - ой компоненты j - ой строки
void BooleanMatrix::setRowBit(uint32_t rowIndex, uint32_t colIndex, bool value)
{
    if (rowIndex < numRows())
    {
        matrixData_[rowIndex].SetBit(colIndex, value);
    }
}
//установка в 0 / 1 k компонент j - ой строки, начиная с i - ой компоненты
void BooleanMatrix::setRowBits(uint32_t rowIndex, uint32_t startCol, uint32_t count, bool value)
{
    if (rowIndex < numRows())
    {
        for (uint32_t i = 0; i < count; ++i)
        {
            matrixData_[rowIndex].SetBit(startCol + i, value);
        }
    }
}

//присваивание(= )
BooleanMatrix& BooleanMatrix::operator=(const BooleanMatrix& other)
{
    if (this != &other)
    {
        matrixData_ = other.matrixData_;
    }
    return *this;
}

// получение строки([]);
BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex)
{
    return matrixData_[rowIndex];
}
const BooleanVector& BooleanMatrix::operator[](const uint32_t rowIndex) const
{
    return matrixData_[rowIndex];
}

//построчное побитовое умножение(&, &=)
BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix& other) const
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    BooleanMatrix result(numRows(), numColumns(), false);

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        result.matrixData_[i] = matrixData_[i] & other.matrixData_[i];
    }

    return result;
}
BooleanMatrix& BooleanMatrix::operator&=(const BooleanMatrix& other)
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        matrixData_[i] &= other.matrixData_[i];
    }

    return *this;
}

//построчное побитовое сложение(| , |=)
BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix& other) const
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    BooleanMatrix result(numRows(), numColumns(), false);

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        result.matrixData_[i] = matrixData_[i] | other.matrixData_[i];
    }

    return result;
}
BooleanMatrix& BooleanMatrix::operator|=(const BooleanMatrix& other)
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        matrixData_[i] |= other.matrixData_[i];
    }

    return *this;
}

//построчное побитовое исключающее ИЛИ(^, ^=)
BooleanMatrix BooleanMatrix::operator^(const BooleanMatrix& other) const
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    BooleanMatrix result(numRows(), numColumns(), false);

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        result.matrixData_[i] = matrixData_[i] ^ other.matrixData_[i];
    }

    return result;
}
BooleanMatrix& BooleanMatrix::operator^=(const BooleanMatrix& other)
{
    assert(numRows() == other.numRows() && numColumns() == other.numColumns()
        && "Index is out of range.");

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        matrixData_[i] ^= other.matrixData_[i];
    }

    return *this;
}

//построчная побитовая инверсия (~)
BooleanMatrix BooleanMatrix::operator~() const
{
    BooleanMatrix result(numRows(), numColumns(), false);

    for (uint32_t i = 0; i < numRows(); ++i)
    {
        result.matrixData_[i] = ~matrixData_[i];
    }

    return result;
}