#include "booleanvector.h"

//конструктор с параметрами(размер и значение - одно и то же дл€ всех разр€дов)
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

//конструктор из массива const char*
BooleanVector::BooleanVector(const char* s)
    : numBits_(strlen(s))
{
    if (numBits_ == 0)
    {
        vectorData_ = nullptr;
        return;
    }

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    vectorData_ = new uint8_t[numBytes]; //выдел€ем место

    // ќбнул€ем все байты
    for (uint32_t i = 0; i < numBytes; i++)
    {
        vectorData_[i] = 0;
    }

    // ”станавливаем биты из строки
    for (uint32_t index = 0; index < numBits_; index++)
    {
        if (s[index] == '1') {
            uint32_t byteIndex = index / (8 * sizeof(uint8_t)); //адрес байта
            uint32_t bitIndex = index % (8 * sizeof(uint8_t));  //адрес бита
            vectorData_[byteIndex] |= (1 << bitIndex);
        }
    }
}

//деструктор
BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
    vectorData_ = nullptr;
}

//конструктор копировани€
BooleanVector::BooleanVector(const BooleanVector& v)
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

//перемещающий конструктор
BooleanVector::BooleanVector(BooleanVector&& other)
    : vectorData_(other.vectorData_), numBits_(other.numBits_)
{
    other.vectorData_ = nullptr;
    other.numBits_ = 0;
}

//присваивание(= )
BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other)
    {
        delete[] vectorData_;  // ќсвобождаем старую пам€ть

        numBits_ = other.numBits_;

        if (numBits_ == 0) {
            vectorData_ = nullptr;
        }
        else {
            uint32_t numBytes = (numBits_ + 7) / 8;
            vectorData_ = new uint8_t[numBytes];

            for (uint32_t i = 0; i < numBytes; i++) {
                vectorData_[i] = other.vectorData_[i];
            }
        }
    }

    return *this;
}

BooleanVector& BooleanVector::operator=(BooleanVector&& other)
{
    if (this != &other)
    {
        delete[] vectorData_;  // ќсвобождаем старую пам€ть

        // «абираем данные у other
        vectorData_ = other.vectorData_;
        numBits_ = other.numBits_;

        // ќставл€ем other в пустом состо€нии
        other.vectorData_ = nullptr;
        other.numBits_ = 0;
    }

    return *this;
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

//инверси€ всех компонент вектора
bool BooleanVector::InvertBV()
{
    for (uint32_t bit = 0; bit < numBits_; bit++)
    {
        uint32_t byteIndex = bit / (8 * sizeof(uint8_t));
        uint32_t bitIndex = bit % (8 * sizeof(uint8_t));

        vectorData_[byteIndex] ^= (1 << bitIndex);
    }
    return true;
}

//инверси€ i-ой компоненты
bool BooleanVector::InvertInd(uint32_t i)
{
    if (i >= numBits_) return false;

    uint32_t byteIndex = i / (8 * sizeof(uint8_t));
    uint32_t bitIndex = i % (8 * sizeof(uint8_t));

    vectorData_[byteIndex] ^= (1 << bitIndex);

    return true;
}

//установка в 0 / 1 i - ой компоненты
bool BooleanVector::SetBit(uint32_t i, bool value)
{
    if (i >= numBits_) return false;

    uint32_t byteIndex = i / (8 * sizeof(uint8_t));
    uint32_t bitIndex = i % (8 * sizeof(uint8_t));

    if (value) vectorData_[byteIndex] |= (1 << bitIndex);
    else vectorData_[byteIndex] &= ~(1 << bitIndex);

    return true;
}

//установка в 0 / 1 k компонент, начина€ с i - ой
bool BooleanVector::SetBits(uint32_t i, uint32_t k, bool value)
{
    if (i >= numBits_) return false;

    if (k == 0) return true;

    uint32_t finish = i + k;
    if (finish > numBits_) return false;

    for (; i < finish; i++)
    {
        uint32_t byteIndex = i / (8 * sizeof(uint8_t));
        uint32_t bitIndex = i % (8 * sizeof(uint8_t));

        if (value) vectorData_[byteIndex] |= (1 << bitIndex);
        else vectorData_[byteIndex] &= ~(1 << bitIndex);
    }

    return true;
}

//установка в 0 / 1 всех компонент вектора
bool BooleanVector::SetAllBits(bool value)
{
    for (uint32_t i = 0; i < numBits_; i++)
    {
        uint32_t byteIndex = i / (8 * sizeof(uint8_t));
        uint32_t bitIndex = i % (8 * sizeof(uint8_t));

        if (value) vectorData_[byteIndex] |= (1 << bitIndex);
        else vectorData_[byteIndex] &= ~(1 << bitIndex);
    }

    return true;
}

//побитовое умножение (&, &=)
BooleanVector BooleanVector::operator&(const BooleanVector& other) const
{
    //длины должны совпадать
    assert(numBits_ == other.numBits_ && "Index is out of range.");

    BooleanVector result(numBits_, false);

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        result.vectorData_[i] = vectorData_[i] & other.vectorData_[i];
    }

    return result;
}
BooleanVector& BooleanVector::operator&=(const BooleanVector& other)
{
    assert(numBits_ == other.numBits_ && "Index is out of range");

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        vectorData_[i] &= other.vectorData_[i];
    }

    return *this;
}

//побитовое сложение(| , |=)
BooleanVector BooleanVector::operator|(const BooleanVector& other) const
{
    assert(numBits_ == other.numBits_ && "Index is out of range");

    BooleanVector result(numBits_, false);

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        result.vectorData_[i] = vectorData_[i] | other.vectorData_[i];
    }

    return result;
}
BooleanVector& BooleanVector::operator|=(const BooleanVector& other)
{
    assert(numBits_ == other.numBits_ && "Index is out of range");

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        vectorData_[i] |= other.vectorData_[i];
    }

    return *this;
}

//побитовое исключающее »Ћ» (^, ^=)
BooleanVector BooleanVector::operator^(const BooleanVector& other) const
{
    assert(numBits_ == other.numBits_ && "Index is out of range");

    BooleanVector result(numBits_, false);

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        result.vectorData_[i] = vectorData_[i] ^ other.vectorData_[i];
    }

    return result;
}
BooleanVector& BooleanVector::operator^=(const BooleanVector& other)
{
    assert(numBits_ == other.numBits_ && "Index is out of range");

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        vectorData_[i] ^= other.vectorData_[i];
    }

    return *this;
}

//побитовые сдвиги(<< , >> , <<=, >>=)
BooleanVector BooleanVector::operator<<(uint32_t sdvig) const
{
    if (sdvig == 0) return *this;
    if (sdvig >= numBits_) return BooleanVector(numBits_, false);

    BooleanVector result(numBits_, false);

    for (uint32_t i = 0; i < numBits_ - sdvig; i++)
    {
        if ((*this)[i]) result.SetBit(i + sdvig, true);
    }

    return result;
}
BooleanVector BooleanVector::operator>>(uint32_t sdvig) const
{
    if (sdvig == 0) return *this;
    if (sdvig >= numBits_) return BooleanVector(numBits_, false);

    BooleanVector result(numBits_, false);

    for (uint32_t i = sdvig; i < numBits_; i++) {
        if ((*this)[i]) result.SetBit(i - sdvig, true);
    }

    return result;
}
BooleanVector& BooleanVector::operator<<=(uint32_t sdvig)
{
    if (sdvig == 0) return *this;
    if (sdvig >= numBits_) {
        SetAllBits(false);
        return *this;
    }

    //  опируем биты в новый массив
    BooleanVector temp = *this;
    SetAllBits(false);

    for (uint32_t i = 0; i < numBits_ - sdvig; i++) {
        if (temp[i]) SetBit(i + sdvig, true);
    }

    return *this;
}
BooleanVector& BooleanVector::operator>>=(uint32_t sdvig)
{
    if (sdvig == 0) return *this;
    if (sdvig >= numBits_) {
        SetAllBits(false);
        return *this;
    }

    BooleanVector temp = *this;
    SetAllBits(false);

    for (uint32_t i = sdvig; i < numBits_; i++) {
        if (temp[i]) SetBit(i - sdvig, true);
    }

    return *this;
}

//побитова€ инверси€(~)
BooleanVector BooleanVector::operator~() const
{
    BooleanVector result(numBits_, false);

    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8 * sizeof(uint8_t)) > 0)
    {
        numBytes += 1;
    }

    for (uint32_t i = 0; i < numBytes; i++) {
        result.vectorData_[i] = ~vectorData_[i];
    }

    // ћаскировка лишних битов в последнем байте
    if (numBits_ % 8 != 0) {
        uint32_t lastByteIndex = numBytes - 1;
        uint8_t mask = (1 << (numBits_ % 8)) - 1;
        result.vectorData_[lastByteIndex] &= mask;
    }

    return result;
}


#if 0
// простой вариант, но не позвол€ет установить значение конкретного бита с помощью присваивани€
bool BooleanVector::operator[](const uint32_t index) const
{
    if (index >= numBits_)
        throw std::runtime_error("Index is out of bounds.");

    uint32_t byteIndex = index / (8 * sizeof(uint8_t));
    uint32_t bitIndex = index % (8 * sizeof(uint8_t));

    return vectorData_[byteIndex] & (1 << bitIndex);
}
#endif

// позвол€ет установить значение конкретного бита с помощью присваивани€, но более сложный и требует вспомогательного класса
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

    // ѕодумайте над тем, как заменить этот цикл одним сравнением
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