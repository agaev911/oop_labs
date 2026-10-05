#include <iostream>

#include "booleanmatrix.h"

#define rus setlocale(LC_ALL, "rus");

int main()
{
    rus;

    const char* ch[] = { "01110", "01110" ,"01010" ,"01110" ,"01110" };
    
    BooleanMatrix m, a(ch, 5, 5), b(3, 3, 0), c;

    m = a; //присваивание
    cout << "матрица m:" << endl << m;

    cout << endl << "получение числа строк a: " << a.numRows() << endl;
    cout << "получение числа столбцов a: " << a.numColumns() << endl;

    puts("");
    cout << endl << "матрица a: " << endl << a << endl;
    cout << "матрица b: " << endl << b << endl;

    cout << "обмен содержимого с другой матрицей(swap), a swap с b: " << endl;
    
    a.swapMatrix(b);
    
    cout << endl << "матрица a: " << endl << a << endl;
    cout << "матрица b: " << endl << b << endl;

    cout << endl << "вес матрицы m: " << endl << m.getWeight() << endl;
    
    cout << endl << "конъюнкция всех строк: " << m.conjunctionRows() << endl;
    cout << endl << "дизъюнкция всех строк: " << m.disjunctionRows() << endl;

    cout << endl << "вес 3-ой строки m: " << m.rowWeight(2) << endl;
  
    m.invertRowBit(2, 2);
    cout << endl << "инверсия в 3-ой компоненты 3-ой строки: " << endl << m << endl;

    m.invertRowBits(2,1,3);
    cout << "инверсия 3 компонент 3-ой строки, начиная с 2-ой компоненты " << endl << m << endl;

    m.setRowBit(0, 2, 0);
    cout << "установка в 0 3-ой компоненты 1-ой строки " << endl << m << endl;

    m.setRowBits(4,1,3,0);
    cout << "установка в 0 3 компонент 5-ой строки, начиная с 2-ой компоненты;  " << endl << m << endl;

    cout << endl << "получение строки" << endl;
    cout << "m[1]: " << m[1] << endl << "m[2]: " << m[2] << endl << "m[3]: " << m[3] << endl;
    
    c = ~m;
    cout << endl << "построчная побитовая инверсия (~) ~m: " << endl << c << endl;

    cout << endl << "b: " << endl << b;
    cout << endl << "m: " << endl << m << endl;

    cout << "построчное побитовое умножение" << endl;
    m = m & b;
    cout << "m & b" << endl << m << endl;

    cout << "построчное побитовое умножение" << endl;
    m &= b;
    cout << "m &= b" << endl << m << endl;

    cout << "построчное побитовое сложение" << endl;
    m = m | b;
    cout << "m & b" << endl << m << endl;

    cout << "построчное побитовое сложение" << endl;
    m |= b;
    cout << "m &= b" << endl << m << endl;

    cout << "построчное побитовое исключающее ИЛИ" << endl;
    m = m ^ b;
    cout << "m ^ b" << endl << m << endl;

    cout << "построчное побитовое исключающее ИЛИ" << endl;
    m ^= b;
    cout << "m ^= b" << endl << m << endl;

    return 0;
}