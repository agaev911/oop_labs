#include "booleanvector.h"

#include <memory>
#include <fstream>

#define rus setlocale(LC_ALL, "rus");

int main()
{

    /*
    cout << endl << "" << a << endl;
    */
    rus
    BooleanVector a, b(8,1), c("1111000011001010");
    cout << "конструктор по умолчанию a:" << a << endl;
    cout << "конструктор с параметрами b:" << b << endl;
    cout << "конструктор из массива const char* c:" << c << endl;

    BooleanVector d(b);
    cout << "конструктор копирования d:" << d << endl;

    cout << endl << "длина (количество бит) вектора c:" << c.getLength() << endl;

    cout << endl << "обмен содержимого с другим вектором(swap): ";
    cout << endl << "b:" << b << endl << "c:" << c << endl << "swap:";
    b.SwapBV(c);
    cout << endl << "b:" << b << endl << "c:" << c << endl;

    cout << endl << "инверсия всех компонент вектора c :";
    c.InvertBV();
    cout << c << endl;

    cout << endl << "инверсия i(0)-ой компоненты: ";
    c.InvertInd(0);
    cout << c << endl;

    cout << endl << "установка в 0/-1 i(2)-ой компоненты: ";
    c.SetBit(2, 1);
    cout << c << endl;

    cout << endl << "установка в 0 / -1 k(3) компонент, начиная с 4 - ой: ";
    c.SetBits(4, 3, 1);
    cout << c << endl;

    cout << endl << "установка в 0 / 1 всех компонент вектора: ";
    c.SetAllBits(1);
    cout << c << endl;

    cout << endl << "вес вектора b: " << b.getWeight() << endl;
   
    cout << endl << "получение компоненты[]" << endl << "b[1]: " << b[1] << endl << "b[5]: " << b[5] << endl << "b[9]: " << b[9] << endl << "b[15] :" << b[15] << endl;

    BooleanVector mask("00010001");
    cout << endl << "c: " << c << ", mask: " << mask << endl;

    cout << endl << "побитовое умножение(&)" << endl;
    c = c & mask;
    cout << "c & mask = " << c << endl;

    cout << endl << "побитовое умножение(&=)" << endl;
    c &= (mask >>4) ;
    cout << "c & (mask<<4) = " << c << endl;

    cout << endl << "побитовое сложение(|)" << endl;
    c = c | mask;
    cout << "c | mask = " << c << endl;

    cout << endl << "побитовое сложение(|=)" << endl;
    c |= (mask >> 1);
    cout << "c |= (mask>>1) = " << c << endl;

    cout << endl << "побитовое исключающее ИЛИ(^)" << endl;
    c = c ^ mask;
    cout << "c ^ mask = " << c << endl;

    cout << endl << "побитовое исключающее ИЛИ(^=)" << endl;
    c ^= (mask >> 1);
    cout << "c ^= (mask>>1) = " << c << endl;


    cout << endl << "b = " << b << endl;

    cout << endl << "побитовые сдвиг(<<)" << endl;
    b = b << 1;
    cout << "b << 1 = " << b << endl;

    cout << endl << "побитовые сдвиги(>>)" << endl;
    b = b >> 1;
    cout << "b >> 1 = " << b << endl;

    cout << endl << "побитовые сдвиги(<<=)" << endl;
    b <<= 1;
    cout << "b <<= 1 = " << b << endl;

    cout << endl << "побитовые сдвиги(>>=)" << endl;
    b >>= 1;
    cout << "b <<= 1 = " << b << endl;

    cout << endl << "побитовая инверсия(~)" << endl;
    b = ~b;
    cout << "~b = " << b << endl;





    return 0;
}