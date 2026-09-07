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

//получение числа строк и столбцов матрицы
uint32_t BooleanMatrix::numRows() const
{
    return matrixData_.getLength();
}
uint32_t BooleanMatrix::numColumns() const
{
    return matrixData_.getLength() > 0 ? matrixData_[0].getLength() : 0;
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

//ввод / вывод в консоль(потоковый)
std::ostream& operator<<(std::ostream& outputStream, const BooleanMatrix& booleanMatrix) //вывод
{
    uint32_t numRows = booleanMatrix.numRows();

    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        outputStream << booleanMatrix[rowIndex] << std::endl;
    }

    return outputStream;
}
istream& operator>>(istream& r, BooleanMatrix& matrix) //ввод
{
    uint32_t numRows, numColumns;

    cout << "Введите количество строк, столбцов и значения разрядов: /n";
    r >> numRows >> numColumns;

    matrix = BooleanMatrix(numRows, numColumns, false);

    for (uint32_t i = 0; i < numRows; ++i)
    {
        r >> matrix[i];
    }

    return r;
}


//обмен содержимого с другой матрицей(swap)
void BooleanMatrix::swapMatrix(BooleanMatrix& other)
{
    matrixData_.swapArrays(other.matrixData_);
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

//вес j - ой строки
uint32_t BooleanMatrix::rowWeight(uint32_t rowIndex) const
{
    if (rowIndex >= numRows()) return 0;
    return matrixData_[rowIndex].getWeight();
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