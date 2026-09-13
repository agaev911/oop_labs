#include"linkedlist.h"

int main()
{
	LinkedList<int>a, b;

	a.addToHead(10);
	a.addToHead(15);
	b = a;
	a.insertAt(0, 4);
	a.addAfter(15, 3);
	cout << a << endl << b;


	return 0;
}