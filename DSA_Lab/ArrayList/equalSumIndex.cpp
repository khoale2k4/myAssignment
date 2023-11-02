#include <iostream>
#include <vector>

using namespace std;

int equalSumIndex(vector<int>& nums) {
	int len = nums.size();
	vector<int> sl(len);
	sl[0] = nums[0];
	vector<int> sr(len);
	sr[len - 1] = nums[len - 1];
	for (int i = 1; i < len; i++) {
		sl[i] = sl[i - 1] + nums[i];
	}
	for (int i = len - 2; i >= 0; i--) {
		sr[i] = sr[i + 1] + nums[i];
	}
	for (int i = 0; i < len; i++) {
		if (sl[i] == sr[i]) return i;
	}
	return -1;
}

int main(){
}
