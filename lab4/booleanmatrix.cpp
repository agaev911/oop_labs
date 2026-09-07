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



