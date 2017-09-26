//Hash/Rehash implementation
#include "HashTable.h"
#include <iostream>


bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	//3>9, 5>25, 7>49, ...  for n=8
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

//for rehash
int nextPrime(int n)
{
	if (n % 2 == 0)
		n++;
	for (; !isPrime(n); n += 2)
		;

	return n;
}

size_t hash(const std::string & key)
{
	size_t hashVal = 0;

	for (char ch : key)
		hashVal = 37 * hashVal + ch;

	return hashVal;
}

