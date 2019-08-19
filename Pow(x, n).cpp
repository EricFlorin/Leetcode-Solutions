// Pow(x, n).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class Solution {
private:
	double myPowRecur(double x, int n)
	{
		// If n == 0, result is always 1
		if (n == 0)
		{
			return 1.0;
		}

		/*
		
		temp = x^(n/2). temp * temp = x^n

		If n is even, the power can be seen as x^(n / 2) * x^(n / 2) == x^(n / 4) * x^(n / 4) * x ^(n / 4) * x^(n / 4) == ...
		If n is odd, the power can be seen as x * x^(n / 2) * x^(n / 2) == x * x^(n / 4) * x^(n / 4) * x ^(n / 4) * x^(n / 4) == ...

		Instead of having myPowRecur() occur multiple times, we will store the result of myPowRecur(x, n) into "temp" and use "temp" instead.
		*/
		double temp = myPowRecur(x, n / 2);

		if (n % 2 == 0)
			return temp * temp;
		else
			return x * temp * temp;
	}

public:

	// x is our base
	// n is our exponent
	double myPow(double x, int n) {

		/*
		What we know about exponents
		1. An exponent of 0 returns 1
		2. An exponent of 1 returns x
		3. An exponent of -1 returns (1 / x)
		4. An exponent > 1 returns x^n
		5. An exponent < -1 returns (1 / x)^n

		We also know that our exponent will be an integer, so we do not have to worry about fractional exponenets.
		*/
		
		if (n == 0)
		{
			return 1.0;
		}
		else if (n == 1)
		{
			return x;
		}
		else if (n == -1)
		{
			return (1 / x);
		}
		else if (n > 1)
		{
			return myPowRecur(x, n);
		}
		else // n < -1
		{
			// 1^n is always 1
			// This means we can use our myPowRecur(x, n) method to calculate the denominator of the fraction (1 / x^n)

			// We cast n to an unsigned int as the MIN_INT when multiplied by a -1 is greater than MAX_INT
			// Leetcode's compiler gave me the tip
			double denominator = myPowRecur(x, static_cast<unsigned int>(n));

			return 1 / denominator;
		}

	}
};
