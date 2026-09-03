#include <iostream>
#include <assert.h>
#include <random>

using namespace std;

template<typename ItemType>
void Swap(ItemType& a, ItemType& b)
{
    ItemType c;
    c = a;
    a = b;
    b = c;
}

template<typename ItemType>
class DynamicArray
{
public:

    DynamicArray(); //конструктор по умолчанию
    DynamicArray(int);
    DynamicArray(const DynamicArray&); //конструктор копирования
    DynamicArray(DynamicArray&&); //конструктор перемещения

    DynamicArray(const ItemType[], int size); // конструктор из обычного массива

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

    // ввод/вывод в консоль(потоковый)
    friend ostream& operator<<(ostream& r, const DynamicArray<ItemType>& s)
    {
        for (int curIdx = 0; curIdx < s.arrayLength_; ++curIdx)
            r << s[curIdx] << " ";
        return r;
    }

    friend istream& operator>>(istream& r, DynamicArray<ItemType>& a)
    {
        int length;
        cout << "\nВведите длину массива: ";
        r >> length;

        delete[] a.arrayData_;

        a.arrayLength_ = length;
        a.arrayData_ = new ItemType[length];

        cout << "\nВведите элементы массива через Enter:\n";
        for (int i = 0; i < a.arrayLength_; i++)
            r >> a.arrayData_[i];

        return r;
    }


    bool swapArrays(DynamicArray&); //обмен содержимого с другим массивом(swap)

    void sortArray(); //сортировка элементов(любым алгоритмом)

    bool insertAt(const int, const ItemType&); //вставка элемента по индексу.Если индекс некорректный, вернуть false
    int searchEl(const ItemType&) const; //поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет)
    bool deleteAt(const int); //удаление элемента по индексу.Если индекс некорректный, вернуть false
    bool deleteEl(const ItemType& element); //удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
    bool deleteAllEl(const ItemType&); //удаление всех элементов с заданным значением

    //поиск максимального / минимального элемента
    ItemType maxEl() const;
    ItemType minEl() const;

    //добавление элемента в конец массива (+ и +=);
    DynamicArray operator+(const ItemType& value) const;
    DynamicArray& operator+=(const ItemType& value);

    //сложение (конкатенация) с другим массивом (здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+ и +=);
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator+=(const DynamicArray& other);

    void add(const ItemType&);

    int getLength() const { return arrayLength_; } //получение размера(количества хранимых элементов в настоящий момент)


    ItemType* getData() const { return arrayData_; }

private:

    ItemType* arrayData_;
    int arrayLength_;
};

template<typename ItemType> //конструктор по умолчанию
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{
    cout << "DynamicArray::DynamicArray()" << endl;
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    cout << "DynamicArray::DynamicArray(int)" << endl;

    arrayData_ = new ItemType[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = ItemType();
    }
}

template<typename ItemType> //конструктор копирования
DynamicArray<ItemType>::DynamicArray(const DynamicArray<ItemType>& otherArray)
{
    cout << "DynamicArray::DynamicArray(const DynamicArray&)" << endl;

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

template<typename ItemType> // конструктор из обычного массива
DynamicArray<ItemType>::DynamicArray(const ItemType array[], int size)
{
    arrayLength_ = size;
    if (size == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayData_ = new ItemType[size];
    for (int i = 0; i < size; ++i)
        arrayData_[i] = array[i];
}

template<typename ItemType> //конструктор перемещения
DynamicArray<ItemType>::DynamicArray(DynamicArray<ItemType>&& otherArray)
{
    cout << "DynamicArray::DynamicArray(DynamicArray&&)" << endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

template<typename ItemType> //деструктор
DynamicArray<ItemType>::~DynamicArray()
{
    cout << "DynamicArray::~DynamicArray()" << endl;

    delete[] arrayData_;
}

template<typename ItemType> //обмен содержимого с другим массивом(swap)
bool DynamicArray<ItemType>::swapArrays(DynamicArray& b)
{
    if (this == &b) return true;

    ItemType* tempData = arrayData_;
    int tempLength = arrayLength_;

    arrayData_ = b.arrayData_;
    arrayLength_ = b.arrayLength_;

    b.arrayData_ = tempData;
    b.arrayLength_ = tempLength;

    return true;
}

template<typename ItemType> //сортировка элементов(любым алгоритмом)
void DynamicArray<ItemType>::sortArray()
{
    int i, j, f;
    for (i = 0, f = 1; i < arrayLength_ - 1 && f; i++)
        for (j = 0, f = 0; j < arrayLength_ - i - 1; j++)
            if (arrayData_[j] > arrayData_[j + 1])
            {
                Swap(arrayData_[j], arrayData_[j + 1]);
                f = 1;
            }
}

//поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет)
template<typename ItemType>
int DynamicArray<ItemType>::searchEl(const ItemType& element) const
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == element)
        {
            return i;
        }
    }
    return -1;
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

template<typename ItemType> //удаление элемента по индексу. Если индекс некорректный, вернуть false
bool DynamicArray<ItemType>::deleteAt(const int index)
{
    if (index < 0 || index >= arrayLength_) return false;

    ItemType* tempArrayData = new ItemType[arrayLength_ - 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    for (int curIdx = index; curIdx < arrayLength_ - 1; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx + 1];
    }

    --arrayLength_;

    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}

template<typename ItemType> //удаление элемента по значению(первое вхождение).Если элемент отсутствует в массиве, вернуть false
bool DynamicArray<ItemType>::deleteEl(const ItemType& element)
{
    int index = -1;

    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == element)
        {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    ItemType* tempArrayData = new ItemType[arrayLength_ - 1];

    for (int i = 0; i < index; i++)
    {
        tempArrayData[i] = arrayData_[i];
    }

    for (int i = index; i < arrayLength_ - 1; i++)
    {
        tempArrayData[i] = arrayData_[i + 1];
    }

    arrayLength_--;

    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}

template<typename ItemType> //удаление всех элементов с заданным значением
bool DynamicArray<ItemType>::deleteAllEl(const ItemType& value)
{
    if (arrayLength_ == 0) return false;

    int newLength = 0;
    for (int i = 0; i < arrayLength_; ++i)
    {
        if (arrayData_[i] != value)
            ++newLength;
    }
    if (newLength == arrayLength_) return false;

    ItemType* newArray = new ItemType[newLength];
    int newIndex = 0;

    for (int i = 0; i < arrayLength_; ++i)
    {
        if (arrayData_[i] != value)
        {
            newArray[newIndex] = arrayData_[i];
            ++newIndex;
        }
    }

    delete[] arrayData_;
    arrayData_ = newArray;
    arrayLength_ = newLength;

    return true;
}

template<typename ItemType> //присваивание копированием(= )
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray<ItemType>& otherArray)
{
    cout << "DynamicArray::operator=(const DynamicArray&)" << endl;

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
    cout << "DynamicArray::operator=(DynamicArray&&)" << endl;

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

//добавление элемента в конец массива(+и += );
template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const ItemType& value) const
{
    DynamicArray result(arrayLength_ + 1);

    for (int i = 0; i < arrayLength_; ++i)
        result.arrayData_[i] = arrayData_[i];

    result.arrayData_[arrayLength_] = value;

    return result;
}
template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const ItemType& value)
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

    return *this;
}

//сложение(конкатенация) с другим массивом(здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+и += );
template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const DynamicArray& other) const
{
    if (other.arrayLength_ == 0) return DynamicArray(*this);

    DynamicArray a(arrayLength_ + other.arrayLength_);

    for (int i = 0; i < arrayLength_; ++i)
        a.arrayData_[i] = arrayData_[i];

    for (int i = 0; i < other.arrayLength_; ++i)
        a.arrayData_[arrayLength_ + i] = other.arrayData_[i];

    return a;
}
template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const DynamicArray& other)
{
    if (other.arrayLength_ == 0) return *this;

    int newLength = arrayLength_ + other.arrayLength_;
    ItemType* newData = new ItemType[newLength];

    for (int i = 0; i < arrayLength_; ++i)
        newData[i] = arrayData_[i];

    for (int i = 0; i < other.arrayLength_; ++i)
        newData[arrayLength_ + i] = other.arrayData_[i];

    delete[] arrayData_;
    arrayData_ = newData;
    arrayLength_ = newLength;

    return *this;
}

//поиск максимального / минимального элемента
template<typename ItemType>
ItemType DynamicArray<ItemType>::maxEl() const
{
    ItemType max = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
        if (arrayData_[i] > max)
            max = arrayData_[i];
    return max;
}

// Минимальный элемент
template<typename ItemType>
ItemType DynamicArray<ItemType>::minEl() const
{
    ItemType min = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
        if (arrayData_[i] < min)
            min = arrayData_[i];
    return min;
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

//получение итераторов на начало / конец массива(методы должны называться begin и end.Метод end должен возвращать итератор не на последний элемент, а за позицию после него)
template<typename ItemType>
ItemType* begin(const DynamicArray<ItemType>& array)
{
    return array.getData();
}

template<typename ItemType>
ItemType* end(const DynamicArray<ItemType>& array)
{
    return array.getData() + array.getLength();
}

int main()
{

    return 0;
}
