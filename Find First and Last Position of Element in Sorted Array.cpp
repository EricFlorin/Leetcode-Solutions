#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	int binarySearch(vector<int>& arr, int low, int high, int target)
	{
		while (low <= high) 
		{
			int m = low + (high - low) / 2;

			// Check if x is present at mid 
			if (arr[m] == target)
				return m;

			// If x greater, ignore left half 
			if (arr[m] < target)
				low = m + 1;
			// If x is smaller, ignore right half 
			else
				high = m - 1;
		}

		// if we reach here, then element was 
		// not present 
		return -1;
	}

public:
	vector<int> searchRange(vector<int>& nums, int target) {

		vector<int> results(2);
		int pos_1 = -1;
		int pos_2 = -1;

		// Special Cases
		// If nums is empty
		if (nums.empty())
		{
			results[0] = -1;
			results[1] = -1;
			return results;
		}
		if (nums[0] == target && nums[nums.size() - 1] == target) // If target values are at the end points of the array
		{
			results[0] = 0;
			results[1] = nums.size() - 1;
			return results;
		}

		// Get bsResult
		int bsResult = binarySearch(nums, 0, nums.size() - 1, target);

		if (bsResult == -1) // No instance of the target value was found
		{
			results[0] = -1;
			results[1] = -1;
			return results;
		}

		// Find first instance using "Battle Ship" method
		for (pos_1 = bsResult; pos_1 - 1 >= 0 && nums[pos_1 - 1] == target; --pos_1)
		{
		}

		// Find last instance using "Battle Ship" method
		for (pos_2 = bsResult; pos_2 + 1 <= nums.size() - 1 && nums[pos_2 + 1] == target; ++pos_2)
		{
		}

		// Store results and return
		results[0] = pos_1;
		results[1] = pos_2;
		return results;
	}
};
