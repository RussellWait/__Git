#include <iostream>
#include "StringHash.h"

using namespace std;


int main()
{
	StringHash *stringHash = new StringHash();

	cout << "hash(\"abcdef\") : " << stringHash->hash("abcdef") << endl;
	cout << "hash(\"abcdef\") : " << stringHash->hash("abcdef") << endl;
	cout << "hash(\"123456\") : " << stringHash->hash("123456") << endl;

	cout << "hashed(\"abcdef\") : " << stringHash->hashed("abcdef") << endl;
	cout << "hashed(\"123456\") : " << stringHash->hashed("123456") << endl;
	cout << "hashed(\"kkkkkk\") : " << stringHash->hashed("kkkkkk") << endl;
	cout << "hashed(\"llllll\") : " << stringHash->hashed("llllll") << endl;
	cout << "hashed(\"AbCDeF\") : " << stringHash->hashed("AbCDeF") << endl;

	return 0;
}
