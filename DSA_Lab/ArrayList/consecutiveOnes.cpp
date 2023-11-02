#include <iostream>
#include <vector>

using namespace std;

bool consecutiveOnes(vector<int>& nums) {
	int len = nums.size();
	bool con = true;
	for (int i = 0; i < len; i++) {
		if (nums[i] == 1) {
			if (con) {
				while (i < len && con) {
					i++;
					if (nums[i] != 1) {
						con = false;
					}
				}
			}
			else return false;
		}
	}
	return true;
}

int main(){
}
