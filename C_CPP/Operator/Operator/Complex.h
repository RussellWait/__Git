#pragma once

#include <iostream>
#include <math.h>

using namespace std;

//#define FRIEND	// ������Ԫ����ʽ���أ��ѱ���ע�������͸�Ϊ���ó�Ա�������ز�������

class Complex
{
public:
	Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) {}
	Complex(const Complex &c) : m_real(c.m_real), m_imag(c.m_imag) {}

	friend  ostream &operator << ( ostream &o, const Complex &c);

#ifdef FRIEND

	// ����Ԫ��������ʽ���ز�����
	friend Complex operator + (const Complex &c1, const Complex &c2);
	friend Complex operator - (const Complex &c1, const Complex &c2);
	friend Complex operator * (const Complex &c1, const Complex &c2);
	friend Complex operator / (const Complex &c1, const Complex &c2);
	friend Complex operator ++ (Complex &c);
	friend Complex operator ++ (Complex &c, int);

#else

	// �ó�Ա��������ʽ���ز�����
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


ostream &operator << (ostream &o, const Complex &c)
{
	return o << c.m_real << "+" << c.m_imag << "i";
}


// ����ʵ��
#ifdef FRIEND

Complex operator + (const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real + c2.m_real, c1.m_imag + c2.m_imag);
}

Complex operator - (const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real - c2.m_real, c1.m_imag - c2.m_imag);
}

Complex operator * (const Complex &c1, const Complex &c2)
{
	double real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
	double imag = c1.m_real * c2.m_imag + c1.m_imag * c2.m_real;
	return Complex(real, imag);
}

Complex operator / (const Complex &c1, const Complex &c2)
{
	double deno = pow(c2.m_real, 2) + pow(c2.m_imag, 2);
	double real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag) / deno;
	double imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag) / deno;
	return Complex(real, imag);
}

Complex operator ++ (Complex &c)
{
	++c.m_real;
	return c;
}

Complex operator ++ (Complex &c, int)
{
	auto temp = c;
	++c.m_real;
	return temp;
}

#else

Complex Complex::operator + (const Complex &c) const
{
	return Complex(this->m_real + c.m_real, this->m_imag + c.m_imag);
}

Complex Complex::operator - (const Complex &c) const
{
	return Complex(this->m_real - c.m_real, this->m_imag - c.m_imag);
}

Complex Complex::operator * (const Complex &c) const
{
	double real = this->m_real * c.m_real - this->m_imag * c.m_imag;
	double imag = this->m_real * c.m_imag + this->m_imag * c.m_real;
	return Complex(real, imag);
}

Complex Complex::operator / (const Complex &c) const
{
	double deno = pow(c.m_real, 2) + pow(c.m_imag, 2);
	double real = (this->m_real * c.m_real + this->m_imag * c.m_imag) / deno;
	double imag = (this->m_imag * c.m_real - this->m_real * c.m_imag) / deno;
	return Complex(real, imag);
}

Complex &Complex::operator ++ ()
{
	++this->m_real;
	return *this;
}

Complex Complex::operator ++ (int)
{
	auto temp = *this;
	++this->m_real;
	return temp;
}

#endif // FRIEND

