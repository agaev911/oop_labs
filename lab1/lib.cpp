#include "lib.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

#include <locale.h>
#define rus setlocale(LC_ALL, "rus");


trapezoid::trapezoid() : x(0), y(0), a(0), b(0), h(0) {}
trapezoid::trapezoid(float x_, float y_, float a_, float b_, float h_) : x(x_), y(y_), a(a_), b(b_), h(h_) {}

void trapezoid::input()
{
	cout << "введите координаты верхней левой вершины: \n";
	cout << "координата x: "; cin >> x;
	cout << "координата y: "; cin >> y;

	cout << "введите длину основания a: \n";
	cout << "a: "; cin >> a;

	cout << "введите длину основания b: \n";
	cout << "b: "; cin >> b;

	cout << "введите длину высоты h: \n";
	cout << "h: "; cin >> h;
}

void trapezoid::output()
{
	cout << "координаты верхнй левой вершины трапеции : \n";
	cout << "координата x: " << x << endl;
	cout << "координата y: " << y << endl;

	cout << "длина основания a: " << a << endl;

	cout << "длина основания b: " << b << endl;

	cout << "длина высоты h: " << h << endl;
}

float trapezoid::get_x() const { return x; }
float trapezoid::get_y() const { return y; }
float trapezoid::get_a() const { return a; }
float trapezoid::get_b() const { return b; }
float trapezoid::get_h() const { return h; }

void trapezoid::set_x(float x_) { x = x_; }
void trapezoid::set_y(float y_) { y = y_; }
void trapezoid::set_a(float a_) { a = a_; }
void trapezoid::set_b(float b_) { b = b_; }
void trapezoid::set_h(float h_) { h = h_; }

void trapezoid::point(int i, float& x_, float& y_)
{
	x_ = x;
	y_ = y;

	if (i == 1)
	{
		x_ = x;
		y_ = y;
	}
	if (i == 2)
	{
		x_ = x + a;
		y_ = y;
	}
	if (i == 3)
	{
		x_ = x - ((b - a) / 2);
		y_ = y - h;
	}
	if (i == 4)
	{
		x_ = x + (a + b) / 2;
		y_ = y - h;
	}
}

float trapezoid::middleline()
{
	float s;
	s = ((a + b) / 2);
	return s;
}

float trapezoid::angle()
{
	float const p = 3.14159;
	float s;
	s = 180 - ((atan((2 * h) / abs(a - b))) * 180) / p;
	return s;
}

void trapezoid::pointO(float& x_, float& y_)
{
	float k;
	k = b / a;
	x_ = ((this->x - ((b - a) / 2)) + k * (this->x + a) / (1 + k));
	y_ = (((this->y - h) + k * this->y) / (1 + k));
}

float trapezoid::area()
{
	float s;
	s = ((a + b) / 2) * h;
	return s;
}

void trapezoid::operator*(int k)
{
	a *= k;
	b *= k;
}

float trapezoid::radius()
{
	float r, c;
	c = pow((pow(b, 2) - pow(a, 2) - (4 * pow(h, 2))) / (4 * h), 2);
	r = 0.5 * sqrt(pow(b, 2) + c);
	return r;
}

void trapezoid::operator==(trapezoid t)
{
	float a[2], b[2], c[2], d[2], a1[2], b1[2], c1[2], d1[2];
	float v1[2], v2[2], v3[2], v4[2];

	this->point(1, a[0], a[1]);
	this->point(2, b[0], b[1]);
	this->point(3, c[0], c[1]);
	this->point(4, d[0], d[1]);

	t.point(1, a1[0], a1[1]);
	t.point(2, b1[0], b1[1]);
	t.point(3, c1[0], c1[1]);
	t.point(4, d1[0], d1[1]);

	v1[0] = a[0] - a1[0];
	v1[1] = a[1] - a1[1];

	v2[0] = b[0] - b1[0];
	v2[1] = b[1] - b1[1];

	v3[0] = c[0] - c1[0];
	v3[1] = c[1] - c1[1];

	v4[0] = d[0] - d1[0];
	v4[1] = d[1] - d1[1];
	if (v1[0] == v2[0] && v1[0] == v3[0] && v1[0] == v4[0] && v1[1] == v2[1] && v1[1] == v3[1] && v1[1] == v4[1])
	{
		cout << "Трапеции равны." << endl;
	}
	else cout << "Трапеции не равны" << endl;
}