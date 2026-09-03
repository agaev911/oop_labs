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

    BooleanVector(const BooleanVector&); //конструктор копирования
    BooleanVector(BooleanVector&&);

    BooleanVector& operator=(const BooleanVector&);
    BooleanVector& operator=(BooleanVector&&);

    bool SwapBV(BooleanVector&); //обмен содержимого с другим вектором(swap)

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
    vectorData_ = nullptr;
}

//конструктор копирования
BooleanVector::BooleanVector(const BooleanVector&v)
    :numBits_(v.numBits_)
{
    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));

    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    vectorData_ = new uint8_t[numBytes];

    for (uint32_t i = 0; i < numBytes; i++)
    {
        vectorData_[i] = v.vectorData_[i];
    }
}

//обмен содержимого с другим вектором(swap)
bool BooleanVector::SwapBV(BooleanVector& b)
{
    if (this == &b) return true;

    uint8_t* tempData = vectorData_;
    uint32_t tempBits = numBits_;

    vectorData_ = b.vectorData_;
    numBits_ = b.numBits_;

    b.vectorData_ = tempData;
    b.numBits_ = tempBits;

    return true;
}

#if 0
// простой вариант, но не позволяет установить значение конкретного бита с помощью присваивания
bool BooleanVector::operator[](const uint32_t index) const
{
    if (index >= numBits_)
        throw std::runtime_error("Index is out of bounds.");

    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));

    return vectorData_[byteIndex] & (1 << bitIndex);
}
#endif

// позволяет установить значение конкретного бита с помощью присваивания, но более сложный и требует вспомогательного класса
BooleanVector::BitReference BooleanVector::operator[](const uint32_t index) const
{
    if (index >= numBits_)
        throw std::runtime_error("Index is out of bounds.");

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

bool BooleanVector::operator==(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) return false;

    uint32_t numBytes = (numBits_ + (8 * sizeof(uint8_t) - 1)) / (8 * sizeof(uint8_t));

    for (uint32_t byteIndex = 0; byteIndex < numBytes - ((numBits_ % 8 == 0) ? 0 : 1); byteIndex++)
    {
        if (vectorData_[byteIndex] != other.vectorData_[byteIndex]) return false;
    }

	// Подумайте над тем, как заменить этот цикл одним сравнением
    for (uint32_t bitIndex = 0; bitIndex < numBits_ % 8; bitIndex++)
    {
        if ((vectorData_[numBytes - 1] & (1 << bitIndex)) != (other.vectorData_[numBytes - 1] & (1 << bitIndex))) return false;
    }

    return true;
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
    BooleanVector a(16, 1);
    a[0] = 0;
    a[2] = 0;
    a[4] = 0;
    a[6] = 0;
    a[8] = 0;

    cout << a;
    
    return 0;
}