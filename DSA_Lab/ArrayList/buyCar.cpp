#include <iostream>
#include <algorithm>

using namespace std;

int buyCar(int* nums, int length, int k) {
	int rs = 0;
	sort(nums, nums + length);
	for (int i = 0; i < length && k > 0; i++) {
		k -= nums[i];
		if (k >= 0) rs++;
	}
	return rs;
}

int main()
{
}
