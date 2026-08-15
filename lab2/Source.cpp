#include <assert.h>
#include<iostream>
using namespace std;
#define rus setlocale(LC_ALL, "rus");


class DynamicArray
{
	int* arrayData_;
	int arrayLength_;

public:

	DynamicArray(); //конструктор по умолчанию
	DynamicArray(const DynamicArray&); //конструктор копирования
    DynamicArray(int); 
    DynamicArray(int[], int); //конструктор из обычного массива

	~DynamicArray(); //деструктор
    

    int arrayLength() { return arrayLength_; } //получение размера (количества хранимых элементов в настоящий момент)


    bool insertAt(const int, const int); //вставка элемента по индексу. Если индекс некорректный, вернуть false

    bool deleteAt(const int); //удаление элемента по индексу. Если индекс некорректный, вернуть false

    bool deleteEl(const int element); //удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
    

    int searchEl(const int) const;//поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет);

    bool swapArrays(DynamicArray&); //обмен содержимого с другим массивом(swap);

    friend ostream& operator <<(ostream& r, DynamicArray& s) //потоковый вывод
    {
        for (int curIdx = 0; curIdx < s.arrayLength_; ++curIdx)
            r << s[curIdx]<< " ";
        return r;
    }

    DynamicArray& operator=(const DynamicArray&); //присваивание копированием(= )

    int& operator[](const int index) //получение ссылки на элемент по индексу ([ ])
    {
        // Проверка выхода индекса за границы (только в отладочной версии)
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }
    const int& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }



    void add(const int);
};


DynamicArray::DynamicArray() : arrayData_(nullptr), arrayLength_(0) {} //конструктор по умолчанию

DynamicArray::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    arrayData_ = new int[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = 0;
    }
}

DynamicArray::DynamicArray(const DynamicArray& otherArray) //конструктор копирования
{
    // Если копируемый массив пуст, новый массив также будет пустым.
    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    // Копируем размер исходного массива.
    arrayLength_ = otherArray.arrayLength_;
    // Выделяем память под новый массив такого же размера.
    arrayData_ = new int[arrayLength_];

    // Копируем все элементы поэлементно.
    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

DynamicArray::DynamicArray(int array[], int size) //конструктор из обычного массива
{
    arrayLength_ = size;
    if (size == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayData_ = new int[size];

    for (int i = 0; i < size; ++i)
    {
        arrayData_[i] = array[i];
    }
}

DynamicArray::~DynamicArray() //деструктор
{
	delete[] arrayData_;
}


bool DynamicArray::insertAt(const int index, const int value) //вставка элемента по индексу. Если индекс некорректный, вернуть false
{
    // Особый случай: вставка в пустой массив (допустим только индекс 0).
    if (index == 0 && arrayLength_ == 0)
    {
        // Выделяем память под один элемент.
        arrayData_ = new int[1];
        arrayData_[0] = value;
        ++arrayLength_; // Теперь длина = 1.
        return true;    // Вставка успешна.
    }

    // Проверка, что индекс находится в допустимых пределах для непустого массива.
    if (index < 0 || index >= arrayLength_) return false;

    // Создаём временный массив увеличенного размера.
    int* tempArrayData = new int[arrayLength_ + 1];

    // Копируем элементы, которые находятся до позиции вставки (индексы [0, index-1]).
    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    // Копируем элементы, начиная с позиции вставки и до конца,
    // но в новом массиве они будут сдвинуты на 1 позицию вправо (индексы [index+1, arrayLength_]).
    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx + 1] = arrayData_[curIdx];
    }

    // Вставляем новый элемент на место index.
    tempArrayData[index] = value;

    // Увеличиваем длину массива (она стала на 1 больше).
    ++arrayLength_;

    // Освобождаем старую память.
    delete[] arrayData_;

    // Переключаем указатель на новый массив.
    arrayData_ = tempArrayData;

    return true; // Вставка успешна.
}

bool DynamicArray::deleteAt(const int index) //удаление элемента по индексу. Если индекс некорректный, вернуть false
{
    if (index < 0 || index >= arrayLength_) return false;
    
    int* tempArrayData = new int[arrayLength_ -1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }
    
    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx+1];
    }

    --arrayLength_;
    
    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}

bool DynamicArray::deleteEl(const int element) //удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
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

    int* tempArrayData = new int[arrayLength_ - 1];

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


int DynamicArray::searchEl(const int element) const //поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет);
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

bool DynamicArray::swapArrays(DynamicArray& b) //- обмен содержимого с другим массивом(swap)
{
    int* tempData = arrayData_;
    int tempLength = arrayLength_;

    arrayData_ = b.arrayData_;
    arrayLength_ = b.arrayLength_;

    b.arrayData_ = tempData;
    b.arrayLength_ = tempLength;

    return true;
}


DynamicArray& DynamicArray::operator=(const DynamicArray& otherArray) //присваивание копированием(=)
{
    // Проверка на самоприсваивание: если это один и тот же объект, ничего не делаем.
    if (this != &otherArray)
    {
        // 1. Освобождаем старую память, так как мы будем создавать новую копию.
        delete[] arrayData_;

        // 2. Если другой массив пуст, текущий тоже становится пустым.
        if (otherArray.arrayLength_ == 0)
        {
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
        else
        {
            // 3. Иначе выделяем новую память и копируем данные.
            arrayLength_ = otherArray.arrayLength_;
            arrayData_ = new int[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    // Возвращаем ссылку на текущий объект.
    return *this;
}

void DynamicArray::add(const int value)
{
    int* tempArrayData = new int[arrayLength_ + 1];

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
    rus;
    
    DynamicArray(a);
    a.add(1);
    a.add(2);
    a.add(3);

    DynamicArray(b);
    b.add(6);
    b.add(7);
    b.add(8);
    b.add(9);
    b.add(10);


    cout << a << a.arrayLength()<< endl << b << endl << endl;
    a.swapArrays(b);
    cout << a << a.arrayLength() << endl << b << b.arrayLength();

   

    return 0;
}