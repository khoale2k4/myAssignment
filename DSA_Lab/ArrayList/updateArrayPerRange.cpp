#include <iostream>
#include <vector>

using namespace std;

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    int leno = operations.size();
    for (int i = 0; i < leno; i++) {
        for (int k = operations[i][0]; k <= operations[i][1]; k++) {
            nums[k] += operations[i][2];
        }
    }
    return nums;
}

int main(){
}
