#include <iostream>  

class CA
{
public:
	CA(int a, int b, int &c) 
		: a(a), b(b), c(c) {}

	void show() {std::cout << "a:" << a << "\tb:" << b << "\tc:" << c << std::endl;}

private:
	int a;
	const int b;
	int &c;
};


class CB
{
public:
	CB(int a) {}
};


class CC
{
public:
	CC(int b) : cb(b) {}

private:
	CB cb;
};

class CD : CB
{
public:
	CD() : CB(0) {}
};


int main()  
{  
	int c = 3;
	CA ca(1, 2, c);
	ca.show();

	getchar();

	return 0;
} 
