#include <stdint.h>
#include <iostream>
#include <assert.h>
using namespace std;
#define rus setlocale(LC_ALL, "rus");

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

    vectorData_ = new uint8_t[numBytes]; //выделяем место

    // Обнуляем все байты
    for (uint32_t i = 0; i < numBytes; i++)
    {
        vectorData_[i] = 0;
    }

    // Устанавливаем биты из строки
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

//конструктор копирования
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
        delete[] vectorData_;  // Освобождаем старую память

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
        delete[] vectorData_;  // Освобождаем старую память

        // Забираем данные у other
        vectorData_ = other.vectorData_;
        numBits_ = other.numBits_;

        // Оставляем other в пустом состоянии
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

//инверсия всех компонент вектора
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

//инверсия i-ой компоненты
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

//установка в 0 / 1 k компонент, начиная с i - ой
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

//побитовое исключающее ИЛИ (^, ^=)
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

    // Копируем биты в новый массив
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

//побитовая инверсия(~)
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

    // Маскировка лишних битов в последнем байте
    if (numBits_ % 8 != 0) {
        uint32_t lastByteIndex = numBytes - 1;
        uint8_t mask = (1 << (numBits_ % 8)) - 1;
        result.vectorData_[lastByteIndex] &= mask;
    }

    return result;
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

#include <memory>
#include <fstream>


// Класс, реализующий автоматический указатель и предназначенный для демонстрации RAII
template<typename Type>
class Pointer
{
public:

    Pointer(Type* pointer) : pointer_(pointer)
    {

    }

    ~Pointer()
    {
        delete pointer_;
    }

private:

    Type* pointer_;
};

// Частичная специализация шаблонного класса, определённого выше, для массивов
template<typename Type>
class Pointer<Type[]>
{
public:

    Pointer(Type* pointer) : pointer_(pointer)
    {

    }

    ~Pointer()
    {
        delete[] pointer_;
    }

private:

    Type* pointer_;
};

// Класс, предназначенный для отладочного вывода на консоль при работе специальных методов
class TestClass1
{
public:

    TestClass1()
    {
        std::cout << "TestClass1::TestClass1() was called." << std::endl;
    }

    ~TestClass1()
    {
        std::cout << "TestClass1::~TestClass1() was called." << std::endl;
    }
};

// RAII-обёртка над файлами CRT.
class FileRAIIWrapper
{
public:

    FileRAIIWrapper(const char* FileName, const char* FileOpenMode)
    {
        //filePtr_ = fopen(FileName, FileOpenMode);
    }

    ~FileRAIIWrapper()
    {
        fclose(filePtr_);
    }

private:

    FILE* filePtr_;
};

// Функция, демонстрирующая важность использования RAII и деструктуров для освобождения ресурсов при наличии исключений.
int testFunc1(const int a, const int b)
{
    // Возможна утечка памяти, если будет выброшено исключение
    //TestClass1 *testClass1 = new TestClass1();
    // Деструктор будет вызван независимо от того, будет ли возбуждено исключение => динамически выделенная память будет освобождена в любом случае
    Pointer<TestClass1> testClass1(new TestClass1());
    Pointer<TestClass1[]> testClass1Array(new TestClass1[7]);

    // Возможна утечка файлового хендла, если будет выброшено исключение
    //FILE *file1 = fopen("test.txt", "r");
    // Деструктор будет вызван независимо от того, будет ли возбуждено исключение => файл будет закрыт в любом случае
    FileRAIIWrapper File1("test.txt", "r");

    // В C++ есть большое количество классов, реализующих идиому RAII и облегчающих написание Exception Safe-кода.
    //std::unique_ptr<TestClass1> ptr(new TestClass1());
    //std::unique_ptr<TestClass1[]> ptr2(new TestClass1[12]);
    //std::fstream fileStream("test.txt", std::ios::in);

    std::cout << "Entering testFunc1..." << std::endl;

    int c = a + b;

    throw std::runtime_error("Test exception 3.");

    std::cout << "Leaving testFunc1..." << std::endl;

    // При выбросе исключения эти операторы не будут вызваны => утечка ресурсов
    //delete testClass1;
    //fclose(file1);

    return c;
}

int main()
{
#if 0
    try
    {
        int res = testFunc1(5, 12);

        std::cout << res << std::endl;
    }
    catch (...)
    {
        std::cout << "Unhandled exception caught." << std::endl;
    }
#endif


    BooleanVector testVector1(10, true);
    BooleanVector testVector2(20, false);

    std::cout << testVector1.getWeight() << std::endl;
    std::cout << testVector2.getWeight() << std::endl;

    try
    {
        std::cout << testVector2[23] << std::endl;
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
    }

    testVector1[2] = false;
    testVector2[4] = true;
    testVector2[13] = true;

    std::cout << testVector1.getWeight() << std::endl;
    std::cout << testVector2.getWeight() << std::endl;

    std::cout << testVector1[0] << std::endl;
    std::cout << testVector1[2] << std::endl;
    std::cout << testVector1[9] << std::endl;
    std::cout << testVector2[0] << std::endl;
    std::cout << testVector2[4] << std::endl;
    std::cout << testVector2[10] << std::endl;
    std::cout << testVector2[13] << std::endl;
    std::cout << testVector2[19] << std::endl;

    std::cout << std::endl;

    BooleanVector testVector3(10, true);
    BooleanVector testVector4(10, true);

    std::cout << (testVector3 == testVector4) << std::endl;

    BooleanVector testVector5(10, true);
    BooleanVector testVector6(15, true);

    std::cout << (testVector5 == testVector6) << std::endl;

    BooleanVector testVector7(10, true);
    BooleanVector testVector8(10, false);

    std::cout << (testVector7 == testVector8) << std::endl;

    return 0;
}