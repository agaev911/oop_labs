#include "LinkedList.h"

#include <iostream>
using namespace std;

#define rus setlocale(LC_ALL, "rus");

int main()
{
    rus;

    cout << "<int>" << endl;

    int m[5] = { 50, 30, 70, 20, 60 };

    LinkedList<int> a;           // по умолчанию
    LinkedList<int> b(m, 5);     // из массива
    LinkedList<int> c(b);        // копирования

    cout << "a (по умолчанию): " << a << endl;
    cout << "b (из массива): " << b << endl;
    cout << "c (копия b): " << c << endl;

    cout << endl << "получение размера списка b: " << b.getSize() << endl;
   
    cout << endl << "потоковый ввод a: ";
    cin >> a;
    cout << "a: " << a << endl;

    cout << endl << "swap" << endl;
    cout << "до swap:" << endl << "a: " << a << endl << "b: " << b << endl;
    a.swap(b);
    cout << endl << "после swap:" << endl << "a: " << a << endl << "b: " << b << endl;


    //cout << endl << "поиск элемента по ключу 30 в списке a: " << *a.findIf(30) << endl;
  
    
    cout << endl << "добавление" << endl;
    a.addToHead(10);
    cout << "addToHead(10): " << a << endl;
    a.addToTail(99);
    cout << "addToTail(99): " << a << endl;
    a.insertAt(2, 55);
    cout << "insertAt(2, 55): " << a << endl;
    a.addAfter(55, 77);
    cout << "addAfter(55, 77): " << a << endl;

    cout << endl << "удаление" << endl;
    a.delFromHead();
    cout << "delFromHead: " << a << endl;
    a.delFromTail();
    cout << "delFromTail: " << a << endl;
    a.delAt(2);
    cout << "delAt(2): " << a << endl;
    a.delKey(55);
    cout << "delKey(55): " << a << endl;


    cout << endl << "max/min" << endl;
    cout << "getMax(): " << a.getMax() << endl;
    cout << "getMin(): " << a.getMin() << endl;

    cout << endl << "isEmpty()" << endl;
    cout << "b.isEmpty(): " << b.isEmpty() << endl;
    cout << "a.isEmpty(): " << a.isEmpty() << endl;

    cout << endl << "очистка" << endl;
    cout << endl << "c: " << c;
    c.Clear();
    cout << "после Clear: c: " << c << endl;
    cout << "c.isEmpty(): " << c.isEmpty() << endl;

    cout << endl << "[]" << endl;
    cout << "a[0]: " << a[0] << endl;
    a[0] = 999;
    cout << "a[0] = 999: " << a << endl;
  
    cout << endl << "присваивание" << endl;
    LinkedList<int> d;
    d = a;
    cout << "d = a: " << d << endl;

    cout << endl << "сравнение" << endl;
    cout << "a == d: " << (a == d) << endl;
    cout << "a != b: " << (a != b) << endl;


    cout << endl << endl <<"<string>" << endl;

    string m_[5] = { "50", "30", "70", "20", "60"};

    LinkedList<string> a_;           // по умолчанию
    LinkedList<string> b_(m_, 5);     // из массива
    LinkedList<string> c_(b_);        // копирования

    cout << "a (по умолчанию): " << a_ << endl;
    cout << "b (из массива): " << b_ << endl;
    cout << "c (копия b): " << c_ << endl;

    cout << endl << "получение размера списка b: " << b_.getSize() << endl;

    cout << endl << "потоковый ввод a: ";
    cin >> a_;
    cout << "a: " << a_ << endl;

    cout << endl << "swap" << endl;
    cout << "до swap:" << endl << "a: " << a_ << endl << "b: " << b_ << endl;
    a_.swap(b_);
    cout << endl << "после swap:" << endl << "a: " << a_ << endl << "b: " << b_ << endl;


    //cout << endl << "поиск элемента по ключу 30 в списке a: " << *a.findIf(30) << endl;


    cout << endl << "добавление" << endl;
    a_.addToHead("10");
    cout << "addToHead(10): " << a_ << endl;
    a_.addToTail("9");
    cout << "addToTail(99): " << a_ << endl;
    a_.insertAt(2, "55");
    cout << "insertAt(2, 55): " << a_ << endl;
    a_.addAfter("55", "77");
    cout << "addAfter(55, 77): " << a_ << endl;

    cout << endl << "удаление" << endl;
    a_.delFromHead();
    cout << "delFromHead: " << a_ << endl;
    a_.delFromTail();
    cout << "delFromTail: " << a_ << endl;
    a_.delAt(2);
    cout << "delAt(2): " << a_ << endl;
    a_.delKey("55");
    cout << "delKey(55): " << a_ << endl;


    cout << endl << "max/min" << endl;
    cout << "getMax(): " << a_.getMax() << endl;
    cout << "getMin(): " << a_.getMin() << endl;

    cout << endl << "isEmpty()" << endl;
    cout << "b.isEmpty(): " << b_.isEmpty() << endl;
    cout << "a.isEmpty(): " << a_.isEmpty() << endl;

    cout << endl << "очистка" << endl;
    cout << endl << "c: " << c_;
    c_.Clear();
    cout << "после Clear: c: " << c_ << endl;
    cout << "c.isEmpty(): " << c_.isEmpty() << endl;

    cout << endl << "[]" << endl;
    cout << "a[0]: " << a_[0] << endl;
    a_[0] = "999";
    cout << "a[0] = 999: " << a_ << endl;

    cout << endl << "присваивание" << endl;
    LinkedList<string> d_;
    d_ = a_;
    cout << "d = a: " << d_ << endl;

    cout << endl << "сравнение" << endl;
    cout << "a == d: " << (a_ == d_) << endl;
    cout << "a != b: " << (a_ != b_) << endl;

    return 0;
}