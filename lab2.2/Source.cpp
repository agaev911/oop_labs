#include "DynamicArray.h"

using namespace std;
#define rus setlocale(LC_ALL, "rus");

int main()
{
    rus;
    cout << "<int>" << endl;

    int m[8] = { 501, 45, 65, 45, 911, 47, 555, -600 };

    DynamicArray<int> a, b(m, 8);

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    DynamicArray<int> copy_b(b);
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

    cout << endl << "вставка элемента=65 по индексу=7" << endl;
    a.insertAt(7, 65);
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

    cout << endl << "получение ссылки на элемент по индексу 4 ([ ]): a[4]: " << a[4] << endl;

    cout << endl << "замена элемента 22 по индексу 1 ([ ]): a: ";
    a[1] = 22;
    cout << a << endl;

    DynamicArray<int> c;
    c = copy_b;
    cout << endl << "присваивание копированием(= ), c=copy_b: с: " << c << endl;

    cout << endl << "добавление элемента 774 в конец массива(+) c: ";
    c = c + 774;
    cout << c << endl;

    cout << endl << "добавление элемента 33 в конец массива(+=) c:";
    c += 33;
    cout << c << endl;

    cout << endl << "сложение с другим массивом +, c+b: c: ";
    c = c + b;
    cout << c << endl;

    cout << endl << "сложение с другим массивом +=, a+b: a: ";
    a += b;
    cout << a << endl;


    
    
    
    cout << endl << "<char>" << endl;

    char z[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'c', 'c'};

    DynamicArray<char> x, y(z, 8);

    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    DynamicArray<char> copy_y(y);
    cout << "copy_y: " << copy_y << endl;
    puts("");
    cout << "arrayLength: " << y.arrayLength() << endl;


    cout << "потоковый ввод: "; cin >> x;
    cout << "x: " << x << endl;
    puts("");

    cout << "swap: "; x.swapArrays(y);
    puts("");
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    cout << endl << "поиск индекса элемента b: " << x.searchEl('b') << endl;

    cout << endl << "сортировка: " << endl;
    x.sortArray();
    cout << "x: " << x << endl;

    cout << endl << "вставка элемента=a по индексу=5" << endl;
    x.insertAt(5, 'a');
    cout << "x: " << x << endl;

    cout << endl << "удаление элемента по индексу = 3" << endl;
    x.deleteAt(3);
    cout << "x: " << x << endl;

    cout << endl << "удаление элемента по значению = a (первое вхождение)" << endl;
    x.deleteEl('a');
    cout << "x: " << x << endl;

    cout << endl << "удаление всех элементов с заданным значением = c" << endl;
    x.deleteAllEl('c');
    cout << "x: " << x << endl;

    cout << endl << "поиск максимального: " << x.maxEl() << endl;

    cout << endl << "поиск минимального: " << x.minEl() << endl;

    cout << endl << "begin: " << *x.begin() << endl;

    //cout << endl << "end: " << *x.end() << endl;

    cout << endl << "получение ссылки на элемент по индексу 3 ([ ]): x[3]: " <<x[3] << endl;

    cout << endl << "замена элемента на 2 по индексу 1 ([ ]): x: ";
    x[1] = '2';
    cout << x << endl;

    DynamicArray<char> i;
    i = copy_y;
    cout << endl << "присваивание копированием(= ), i=copy_y: i: " << i << endl;

    cout << endl << "добавление элемента 7 в конец массива(+) i: ";
    i = i + '7';
    cout << i << endl;

    cout << endl << "добавление элемента 3 в конец массива(+=) i: ";
    i += '3';
    cout << i << endl;

    cout << endl << "сложение с другим массивом +, i+y: i: ";
    i = i + y;
    cout << i << endl;

    cout << endl << "сложение с другим массивом +=, x+y: x: ";
    x += y;
    cout << x << endl;

    return 0;
}