#pragma once

#include <iostream>
#include <math.h>


using namespace std;

//#define FRIEND	// 采用友元得形式重载（把本行注释起来就改为调用成员函数重载操作符）


class Complex
{
public:
	Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) {}
	Complex(const Complex &c) : m_real(c.m_real), m_imag(c.m_imag) {}

	friend  ostream &operator << ( ostream &o, const Complex &c);

#ifdef FRIEND

	// 用友元函数的形式重载操作符
	friend Complex operator + (const Complex &c1, const Complex &c2);
	friend Complex operator - (const Complex &c1, const Complex &c2);
	friend Complex operator * (const Complex &c1, const Complex &c2);
	friend Complex operator / (const Complex &c1, const Complex &c2);
	friend Complex operator ++ (Complex &c);
	friend Complex operator ++ (Complex &c, int);

#else

	// 用成员函数的形式重载操作符
	Complex operator + (const Complex &c) const;
	Complex operator - (const Complex &c) const;
	Complex operator * (const Complex &c) const;
	Complex operator / (const Complex &c) const;
	Complex &operator ++ ();
	Complex operator ++ (int);

#endif // FRIEND


private:
	double m_real;
	double m_imag;
};
