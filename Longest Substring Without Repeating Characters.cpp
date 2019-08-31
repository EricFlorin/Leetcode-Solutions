#include <string>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// Our first solution will be a brute force solution.
		// It will be very slow, but it will be a start.
		
		// Special Case: If we are given an empty string, we return 0
		//               since we can't make a substring out of an empty string.
		if (s.empty())
			return 0;
		
		int max_length = 0; // This will store the length of the biggest substring with no repeating characters
		int start_new_str = 0; // This will mark the beginning of our new substrings

		// Holds the characters we encountered
		string seen = "";
		
		// Traverse through the string
		for (int i = 0; i < s.length(); i++)
		{
			// If the current character wasn't seen before, we add it to our "seen" string and continue
			if (seen.find(s[i]) == string::npos)
			{
				seen += s[i];
			}
			else // Else, we take the substring length and adjust our i and start_new_str pointers.
			{
				int substring_len = i - start_new_str;

				if (substring_len > max_length)
				{
					max_length = substring_len;
				}
				
				start_new_str++;
				i = start_new_str;

				// Although we cleared out seen, we have to add the character
				// at i (which here is equal to start_new_str) as that character could
				// be a repeating character.
				seen.clear();
				seen += s[i];
			}
		}

		// In the case that the last substring made by the loop did not contain repeating characters.
		int substring_len = s.length() - start_new_str;

		if (substring_len > max_length)
			max_length = substring_len;

		return max_length;
	}
};
