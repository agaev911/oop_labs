#include <stdint.h>
#include <iostream>
using namespace std;

class BooleanVector
{
private:

    class BitReference;

public:

    BooleanVector() = default; //конструктор по умолчанию
    BooleanVector(const uint32_t, const bool); //конструктор с параметрами (размер и значение - одно и то же для всех разрядов)
    BooleanVector(const char*);

    ~BooleanVector();//деструктор

    BooleanVector(const BooleanVector&);
    BooleanVector(BooleanVector&&);

    BooleanVector& operator=(const BooleanVector&);
    BooleanVector& operator=(BooleanVector&&);

    // простой вариант, но не позволяет установить значение конкретного бита с помощью присваивания
#if 0
    bool operator[](const uint32_t) const;
#endif
    // позволяет установить значение конкретного бита с помощью присваивания, но более сложный и требует вспомогательного класса
    BitReference operator[](const uint32_t) const;

    uint32_t getLength() const { return numBits_; } //длина (количество бит) вектора

    uint32_t getWeight() const; //вес вектора (количество единичных компонент)
    
    
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


//конструктор с параметрами(размер и значение - одно и то же для всех разрядов)
BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
    : numBits_(numBits)
{
#if 0
    uint32_t numBytes = (numBits + (8 * sizeof(uint8_t) - 1)) / (8 * sizeof(uint8_t));
#endif

    uint32_t numBytes = numBits / (8 * sizeof(uint8_t));

    if (numBits % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    vectorData_ = new uint8_t[numBytes];

    uint8_t localInitialValue = initialValue ? 255 : 0;

    for (uint32_t byteIndex = 0; byteIndex < numBytes; byteIndex++)
    {
        vectorData_[byteIndex] = localInitialValue;
    }
}

//деструктор
BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
}

// простой вариант, но не позволяет установить значение конкретного бита с помощью присваивания
#if 0
bool BooleanVector::operator[](const uint32_t index) const
{
    // TODO: добавить проверку на выход за границы вектора
    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));

    return vectorData_[byteIndex] & (1 << bitIndex);
}
#endif
// позволяет установить значение конкретного бита с помощью присваивания, но более сложный и требует вспомогательного класса
BooleanVector::BitReference BooleanVector::operator[](const uint32_t index) const
{
    // TODO: добавить проверку на выход за границы вектора
    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));

    return BooleanVector::BitReference(&vectorData_[byteIndex], bitIndex);
}

//вес вектора (количество единичных компонент)
uint32_t BooleanVector::getWeight() const

{
    uint32_t weight = 0;

    for (uint32_t bit = 0; bit < numBits_; bit++)
    {
        uint32_t byteIndex = bit / (8 * sizeof(uint8_t));
        uint32_t bitIndex = bit % (8 * sizeof(uint8_t));

        if (vectorData_[byteIndex] & (1 << bitIndex))
            weight++;
    }

    return weight;
}



BooleanVector::BitReference::BitReference(uint8_t* const bytePtr, const uint8_t bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex) {
}

BooleanVector::BitReference::operator bool()
{
    return *bytePtr_ & (1 << bitIndex_);
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const bool NewValue)
{
    uint8_t mask = 1 << bitIndex_;

    if (NewValue)
    {
        *bytePtr_ |= mask;
    }
    else
    {
        *bytePtr_ &= ~mask;
    }

    return *this;
}



int main()
{
    BooleanVector a(8, true);
    cout <<a[3];

    return 0;
}