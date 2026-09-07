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

