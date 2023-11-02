#include <iostream>
#include <vector>

using namespace std;

int longestSublist(vector<string>& words) {
	int len = words.size();
	int rs = 0;
	for (int i = 0; i < len; i++) {
		int c = 0;
		for (int k = i; k < len; k++) {
			if (words[k][0] == words[i][0]) c++;
			else break;
		}
		rs = max(rs, c);
	}
	return rs;
}

int main(){}
