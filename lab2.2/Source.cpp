#include <iostream>
#include <assert.h>
#include <random>

template<typename ItemType>
class DynamicArray
{
public:

    DynamicArray(); //конструктор по умолчанию
    DynamicArray(int);
    DynamicArray(const DynamicArray&); //конструктор копирования
    DynamicArray(DynamicArray&&); //конструктор перемещения
    ~DynamicArray(); //деструктор

    DynamicArray& operator=(const DynamicArray&); //присваивание копированием(= )
    DynamicArray& operator=(DynamicArray&&); //присваивание перемещением (=(DynamicArray&& other))

    //получение ссылки на элемент по индексу ([ ])
    /* Мы вынуждены создать две версии индексирования, чтобы разрешить константым объектам только чтение элементов, но не запись,
       а изменяемым объектам разрешить и чтение, и запись*/
    ItemType& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const ItemType& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    bool insertAt(const int, const ItemType&); //вставка элемента по индексу.Если индекс некорректный, вернуть false



    void add(const ItemType&);

    int getLength() const { return arrayLength_; } //получение размера(количества хранимых элементов в настоящий момент)


    ItemType* getData() const { return arrayData_; }

private:

    ItemType* arrayData_;
    int arrayLength_;
};

template<typename ItemType> ////конструктор по умолчанию
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0) 
{
    std::cout << "DynamicArray::DynamicArray()" << std::endl;
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    std::cout << "DynamicArray::DynamicArray(int)" << std::endl;

    arrayData_ = new ItemType[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = ItemType();
    }
}

template<typename ItemType> //конструктор копирования
DynamicArray<ItemType>::DynamicArray(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(const DynamicArray&)" << std::endl;

    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;

        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new ItemType[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

template<typename ItemType> //конструктор перемещения
DynamicArray<ItemType>::DynamicArray(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(DynamicArray&&)" << std::endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

template<typename ItemType> //деструктор
DynamicArray<ItemType>::~DynamicArray()
{
    std::cout << "DynamicArray::~DynamicArray()" << std::endl;

    delete[] arrayData_;
}

template<typename ItemType> //присваивание копированием(= )
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray<ItemType>& otherArray)
{
    std::cout << "DynamicArray::operator=(const DynamicArray&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        if (otherArray.arrayLength_ == 0)
        {
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
        else
        {
            arrayLength_ = otherArray.arrayLength_;
            arrayData_ = new ItemType[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

template<typename ItemType> //присваивание перемещением (=(DynamicArray&& other))
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(DynamicArray<ItemType>&& otherArray)
{
    std::cout << "DynamicArray::operator=(DynamicArray&&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        arrayData_ = otherArray.arrayData_;
        arrayLength_ = otherArray.arrayLength_;
        otherArray.arrayData_ = nullptr;
        otherArray.arrayLength_ = 0;
    }

    return *this;
}

template<typename ItemType> //вставка элемента по индексу.Если индекс некорректный, вернуть false
bool DynamicArray<ItemType>::insertAt(const int index, const ItemType& value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new ItemType[1];

        arrayData_[0] = value;

        ++arrayLength_;

        return true;
    }

    if (index < 0 || index >= arrayLength_) return false;

    ItemType* tempArrayData = new ItemType[arrayLength_ + 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx + 1] = arrayData_[curIdx];
    }

    tempArrayData[index] = value;

    ++arrayLength_;

    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}

template<typename ItemType>
void DynamicArray<ItemType>::add(const ItemType& value)
{
    ItemType* tempArrayData = new ItemType[arrayLength_ + 1];

    for (int index = 0; index < arrayLength_; ++index)
    {
        tempArrayData[index] = arrayData_[index];
    }

    tempArrayData[arrayLength_] = value;

    ++arrayLength_;

    delete[] arrayData_;
    arrayData_ = tempArrayData;
}



int main()
{
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    std::uniform_real_distribution<float> distribution(-100.0f, 100.0f);

    DynamicArray<float> floatArray(100);

    for (int i = 0; i < 100; i++)
    {
        floatArray[i] = distribution(generator);

        std::cout << floatArray[i] << std::endl;
    }

    DynamicArray<unsigned int> uintArray(100);

    for (int i = 0; i < 100; i++)
    {
        uintArray[i] = distribution(generator) + 100u;

        std::cout << uintArray[i] << std::endl;
    }

    return 0;
}