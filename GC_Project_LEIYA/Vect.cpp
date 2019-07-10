#include "Vect.h"
#include <cmath>
#include <iostream>

Vect::Vect(const Vect& t)
	:x(t.x_()), y(t.y_()), z(t.z_())  //拷贝构造
{
}

Vect::Vect(double a, double b, double c)
	: x(a), y(b), z(c)//构造
{
}

Vect::~Vect()
{
	//dtor
}

double Vect::length() const
{
	return sqrt(x*x + y*y + z*z);
}

Vect Vect::dirc()
{
	Vect temp = (*this);
	temp.standardLize();
	return temp;
}

double Vect::dis(const Vect& t)   const
{
	return sqrt((x - t.x_())*(x - t.x_()) + (y - t.y_())*(y - t.y_()) + (z - t.z_())*(z - t.z_()));
}

double Vect::arg(const Vect& t) const
{
	return acos((this->dotProduct(t)) / (this->length()*t.length()));
}
void Vect::standardLize()
{
	double t = this->length();
	x = x / t;
	y = y / t;
	z = z / t;

}

void Vect::outp() const
{
	std::cout << '(' << x << ',' << y << ',' << z << ')' ;
}

double Vect::dotProduct(const Vect& t) const
{
	return (x*t.x_() + y*t.y_() + z*t.z_());
}

Vect Vect::crossProduct(const Vect& t)
{
	double a, b, c;
	a = y*t.z_() - z*t.y_();
	b = z*t.x_() - x*t.z_();
	c = x*t.y_() - y*t.x_();
	Vect temp(a, b, c);
	return temp;
}

Vect Vect::operator+(const Vect & t)const
{
	Vect temp(*this);
	temp.x += t.x_();
	temp.y += t.y_();
	temp.z += t.z_();
	return temp;
}

Vect Vect::operator-(const Vect & t)const
{
	Vect temp(*this);
	temp.x -= t.x_();
	temp.y -= t.y_();
	temp.z -= t.z_();
	return temp;
}

Vect Vect::operator*(double t)
{
	Vect temp(*this);
	temp.x = temp.x*t;
	temp.y = temp.y*t;
	temp.z = temp.z*t;
	return temp;
}

Vect operator*(double t, Vect & p)
{
	return p*t;
	// TODO: 在此处插入 return 语句
}
