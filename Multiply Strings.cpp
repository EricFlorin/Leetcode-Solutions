#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
private:
	// Parses a string to a vector
	vector<unsigned int> string_to_vector(string& num)
	{
		vector<unsigned int> result;

		for (char c : num)
			result.push_back(c - '0');

		reverse(result.begin(), result.end());

		return result;
	}

	// Turns a vector into a string
	string vector_to_string(vector<unsigned int>& vec)
	{
		stringstream ss;

		for (unsigned int i : vec)
			ss << i;

		string result = ss.str();

		// Simple fix for exta zero bug
		size_t pos_of_last_leading_zero = 0;
		while (result[pos_of_last_leading_zero] == '0')
		{
			++pos_of_last_leading_zero;
		}
		result.erase(result.begin(), result.begin() + pos_of_last_leading_zero);

		return result;
	}

	// Makes the two vectors the same size.
	// Since the parameters are references, no need to return anything.
	void preprocess_vectors(vector<unsigned int>& num1, vector<unsigned int>& num2)
	{
		if (num1.size() < num2.size())
		{
			while (num1.size() != num2.size())
				num1.push_back(0);
		}
		else
		{
			while (num2.size() != num1.size())
				num2.push_back(0);
		}
	}

	// Gets the extra and remainder
	// 0 <= num < 100
	void get_extra_and_remainder(unsigned int num, unsigned int& extra, unsigned int& remainder)
	{
		string temp = "";
		stringstream ss;
		ss << num;
		temp = ss.str();

		if (temp.size() > 1)
		{
			extra = temp[0] - '0';
			remainder = temp[1] - '0';
		}
		else
		{
			extra = 0;
			remainder = temp[0] - '0';
		}
	}

	// Adds two vectors
	// Modified the code from "Add Two Numbers" to work for vectors
	// instead of the ListNode struct.
	vector<unsigned int> addTwoNumbers(vector<unsigned int> l1, vector<unsigned int> l2) {

		// Preprocess the lists
		preprocess_vectors(l1, l2);

		// Initalize result vector
		vector<unsigned int> result;

		// Traverse through the two lists until the end it hit
		for (size_t i = 0; i < l1.size() && i < l2.size(); i++)
		{
			// The sum of the two numbers in each list
			int sum = l1[i] + l2[i];

			// We need to check if our sum is greater than or equal to 10.
			if (sum >= 10)
			{
				// This will go in place of the two digit number
				int difference = sum - 10;
				// This will be the 1 in two digit number
				int remainder = 1;

				// Check if there is room to add our remainder
				if (i + 1 == l1.size() && i + 1 == l2.size())
				{
					l1.push_back(remainder);
					l2.push_back(0);
					result.push_back(difference);
				}
				else if (i + 1 == l1.size() && i + 1 != l2.size())
				{
					l1.push_back(remainder);
					result.push_back(difference);
				}
				else if (i + 1 != l1.size() && i + 1 == l2.size())
				{
					l2.push_back(0);
					l1[i + 1] += remainder;
					result.push_back(difference);
				}
				else
				{
					l1[i + 1] += remainder;
					result.push_back(difference);
				}
			}
			else
			{
				result.push_back(sum);
			}
		}

		return result;
	}

	// Multiplies the two vectors
	// NOTE: The vectors have the digits in reverse order (like in Add Two Numbers)
	vector<unsigned int> multiply_vector(vector<unsigned int>& num1, vector<unsigned int>& num2)
	{
		// 1. Initalize our product vector (what we will be returning)
		vector<unsigned int> product;

		// 2. Initalize double vector for "partial sums"
		vector<vector<unsigned int>> partial_sums;

		// 3. Do multiplication
		unsigned int extra = 0;
		unsigned int remainder = 0;
		unsigned int numZeros = 0;
		for (size_t i = 0; i < num1.size(); i++)
		{
			vector<unsigned int> sum;

			for (size_t z = 0; z < numZeros; z++)
				sum.push_back(0);

			for (size_t j = 0; j < num2.size() - 1; j++)
			{
				unsigned int product = (num1[i] * num2[j]) + extra;
				get_extra_and_remainder(product, extra, remainder);
				sum.push_back(remainder);
			}

			unsigned int product = (num1[i] * num2[num2.size() - 1]) + extra;
			get_extra_and_remainder(product, extra, remainder);

			// These two lines are giving me an extra zero
			// on the right side of the number (0400 instead of 400)
			sum.push_back(remainder);
			sum.push_back(extra);

			partial_sums.push_back(sum);

			extra = 0;
			remainder = 0;
			numZeros++;
		}

		// 4. Add the partial sums
		for (vector<unsigned int> vec : partial_sums)
		{
			product = addTwoNumbers(product, vec);
		}
		
		reverse(product.begin(), product.end());

		return product;
	}

public:
	string multiply(string num1, string num2) 
	{
		// Special Case: If one of the numbers is 0, return 0
		if (num1 == "0" || num2 == "0")
		{
			return "0";
		}

		// Special Case: If one of the numbers is 1, return the other number
		if (num1 == "1")
		{
			return num2;
		}
		if (num2 == "1")
		{
			return num1;
		}

		vector<unsigned int> num1_vec = string_to_vector(num1);
		vector<unsigned int> num2_vec = string_to_vector(num2);

		vector<unsigned int> product = multiply_vector(num1_vec, num2_vec);

		return vector_to_string(product);
	}
};
