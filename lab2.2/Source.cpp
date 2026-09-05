#include "DynamicArray.h"

using namespace std;
#define rus setlocale(LC_ALL, "rus");

int main()
{
    rus;

    DynamicArray<char> a;
    cin >> a;
    cout << a;

    return 0;
}