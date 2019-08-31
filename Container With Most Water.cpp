#include <vector>
#include <stdlib.h> /* abs */

using namespace std;

class Solution {
public:
	int maxArea(vector<int>& height) {

		// 1. Initalize helper variables
		int max_area = 0;

		// 2. Traverse through array
		for (int current_pos = 0; current_pos < height.size(); ++current_pos)
		{
			// Height of the line we are doing the comparison
			int current_height = height[current_pos];

			// Going through the other lines in the array
			for (int itr = current_pos; itr < height.size(); ++itr)
			{
				if (itr == current_pos)
					continue;

				int itr_height = height[itr];
				int width = itr - current_pos;
				int area = 0;
				
				if (itr_height < current_height)
					area = width * itr_height;
				else
					area = width * current_height;

				if (area > max_area)
					max_area = area;
			}
		}

		return max_area;
	}
};
