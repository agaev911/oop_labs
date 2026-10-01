#pragma once

#include <assert.h>
#include<iostream>

using namespace std;

class DynamicArray
{
    int* arrayData_;
    int arrayLength_;

public:

    DynamicArray(); //конструктор по умолчанию
    DynamicArray(const int[], int); //конструктор из обычного массива
    DynamicArray(const DynamicArray&); //конструктор копирования

    DynamicArray(int);//конструктор по длине

    ~DynamicArray(); //деструктор

    int arrayLength() const { return arrayLength_; } //получение размера (количества хранимых элементов в настоящий момент)
 
    bool swapArrays(DynamicArray&); //обмен содержимого с другим массивом(swap)
    
    int searchEl(const int) const; //поиск элемента(возвращает индекс первого совпавшего элемента, либо - 1, если совпадений нет)
    
    void sortArray(); //сортировка элементов (пузырёк)

    bool insertAt(const int, const int); //вставка элемента по индексу. Если индекс некорректный, вернуть false
    bool deleteAt(const int); //удаление элемента по индексу. Если индекс некорректный, вернуть false
    bool deleteEl(const int element); //удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
  
    bool deleteAllEl(int); //удаление всех элементов с заданным значением
   
    //поиск максимального/минимального элемента
    int maxEl()const;
    int minEl()const;

    //получение итераторов на начало/конец массива
    int* begin() const; 
    int* end() const;

    DynamicArray(DynamicArray&&); //конструктор перемещения
  
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

    DynamicArray& operator=(const DynamicArray&); //присваивание копированием(= )

    //добавление элемента в конец массива(+и += )
    DynamicArray operator+(int value) const;
    DynamicArray& operator+=(int value);

    DynamicArray& operator=(DynamicArray&&); //присваивание перемещением(= (DynamicArray && other))
  
    //сложение(конкатенация) с другим массивом(здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+и += );
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator+=(const DynamicArray&);
};

ostream& operator<<(ostream&, const DynamicArray&);//потоковый вывод

istream& operator>>(istream&, DynamicArray&); //потоковый ввод


//friend ostream& operator <<(ostream& r, DynamicArray& s) //потоковый вывод
//{
//    for (int curIdx = 0; curIdx < s.arrayLength_; ++curIdx)
//        r << s[curIdx] << " ";
//    return r;
//}

//friend istream& operator>>(istream& r, DynamicArray& a) //потоковый ввод
//{
//    int length;
//    cout << "\nВведите длину массива: "; cin >> length;

//    delete[]a.arrayData_;

//    a.arrayLength_ = length;
//    a.arrayData_ = new int[length];

//    cout << "\nВведите элементы массива через Enter:\n";
//    for (int i = 0; i < a.arrayLength_; i++)
//        r >> a.arrayData_[i];

//    return r;
//}
