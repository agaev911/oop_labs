#pragma once

class trapezoid
{
	float x, y, a, b, h;

public:

	trapezoid();
	trapezoid(float, float, float, float, float);

	void input();
	void output();

	float get_x() const;
	float get_a() const;
	float get_y() const;
	float get_b() const;
	float get_h() const;

	void set_x(float x_);
	void set_y(float y_);
	void set_a(float a_);
	void set_b(float b_);
	void set_h(float h_);

	void point(int i, float& x_, float& y_);

	float middleline();

	float angle(); //нахождение тупого угла

	void pointO(float& x_, float& y_); //координата точки пересечения диагоналей

	float area(); //нахождение площади

	void operator*(int k);

	float radius();

	void operator==(trapezoid t);
};
#pragma once
