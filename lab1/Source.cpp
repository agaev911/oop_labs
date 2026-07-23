#include "lib.h"

#include <iostream>
using namespace std;

#include <locale.h>
#define rus setlocale(LC_ALL, "rus");

int main()
{
	rus;
	trapezoid a(0, 0, 4, 6, 2), b;
	float x, y, Ox, Oy;

	cout << "Трапеция A:" << endl; a.output();
	puts("");

	cout << "x: " << a.get_x() << endl;
	cout << "y: " << a.get_y() << endl;
	cout << "a: " << a.get_a() << endl;
	cout << "b: " << a.get_b() << endl;
	cout << "h: " << a.get_h() << endl;

	a.set_x(2);
	a.set_y(2);
	a.set_a(8);
	a.set_b(10);
	a.set_h(4);

	a.output();

	a.point(3, x, y);
	cout << "Координата нужной вершины x: " << x << "\nКоордината нужной вершины y: " << y << endl;

	cout << "Средняя линия трапеции D=" << a.middleline() << endl;

	cout << "Тупой угол трапеции @=" << a.angle() << endl;

	a.pointO(Ox, Oy);
	cout << "Точка пересечения диагоналей x: " << Ox << " y: " << Oy << endl;

	cout << "Нахождение площади трапеции S=" << a.area() << endl;

	cout << "Радиус описанной окружности R=" << a.radius() << endl;
	puts("");

	cout << endl << "Введите трапецию B:" << endl;
	b.input();

	cout << endl << "Трапеция B:" << endl;
	b.output();

	puts("");
	a == b;
	puts("");

	b * 2;
	b.output();
	a == b;





	return 0;
}