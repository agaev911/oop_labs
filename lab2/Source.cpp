#include "DynamicArray.h"

using namespace std;
#define rus setlocale(LC_ALL, "rus");

int main()
{
    rus;
    
    int m[8] = { 501, 45, 65, 45, 911, 47, 555, -600 };
    
    DynamicArray a, b(m, 8); 

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    DynamicArray copy_b(b);
    cout << "copy_b: " << copy_b << endl;
    puts("");
    cout << "arrayLength: " << b.arrayLength() << endl;

    
    cout << "потоковый ввод: "; cin >> a;
    cout << "a: " << a << endl;
    puts("");

    cout << "swap: "; a.swapArrays(b);
    puts("");
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    cout << endl << "поиск индекса элемента 65: " << a.searchEl(65) << endl;

    cout << endl << "сортировка: " << endl;
    a.sortArray();
    cout << "a: " << a << endl;

    cout << endl << "вставка элемента=333 по индексу=0" << endl;
    a.insertAt(0, 333);
    cout << "a: " << a << endl;

    cout << endl << "удаление элемента по индексу = 3" << endl;
    a.deleteAt(3);
    cout << "a: " << a << endl;

    cout << endl << "удаление элемента по значению = 65 (первое вхождение)" << endl;
    a.deleteEl(65);
    cout << "a: " << a << endl;

    cout << endl << "удаление всех элементов с заданным значением = 45" << endl;
    a.deleteAllEl(45);
    cout << "a: " << a << endl;

    cout << endl << "поиск максимального: " << a.maxEl() << endl;

    cout << endl << "поиск минимального: " << a.minEl() << endl;
    
    cout << endl << "begin: " << *a.begin() << endl;

    cout << endl << "end: " << *a.end() << endl;

    cout << endl << "получение ссылки на элемент по индексу 5 ([ ]): " << a[4] << endl;

    cout << endl << "замена элемента 22 по индексу 2 ([ ]): "; 
    a[1] = 22;
    cout << a << endl;

    DynamicArray c;
    c = copy_b;
    cout << endl << "присваивание копированием(= ), c=copy_b: " << c << endl;

    cout << endl<< "добавление элемента в конец массива(+)";
    c = c + 2;
    cout << c << endl;

    cout << endl << "добавление элемента в конец массива(+=)";
    c += 2;
    cout << c << endl;

    cout << endl << "сложение с другим массивом +, c+b: ";
    c = c + b;
    cout << c << endl;

    cout << endl << "сложение с другим массивом +=, a+b: ";
    a += b;
    cout << a << endl;

    
    return 0;
}