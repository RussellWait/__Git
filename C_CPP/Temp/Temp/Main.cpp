#include "Complex.h"

int main()
{
	auto c1 = Complex(2, 3);
	auto c2 = Complex(7, 1);

	cout << c1 + c2 << endl;
	cout << c1 - c2 << endl;
	cout << c1 * c2 << endl;
	cout << c1 / c2 << endl;
	cout << c1++ << endl;
	cout << ++c2 << endl;

	getchar();

	return 0;
}
