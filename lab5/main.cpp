#include"linkedlist.h"

int main()
{
	LinkedList<int>a;
	LinkedList<int>b;

	a.addToHead(10);
	a.addToHead(15);
	b = a;
	a.insertAt(0, 4);
	a.addAfter(15, 3);
	cout <<b;




	return 0;
}