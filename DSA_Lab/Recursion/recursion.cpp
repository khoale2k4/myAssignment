#include <iostream>

using namespace std;

void printArray(int n, int i = 0)
{
    cout << i;
    if (i < n) cout << ", ";
    else return;
    printArray(n, i + 1);
}

void printPattern(int n)
{
    if (n <= 0) {
        cout << n;
        return;
    }
    cout << n << " ";
    printPattern(n - 5);
    cout << " " << n;
}

int findMax(int* arr, int length, int i = 0)
{
    if (i == length) return arr[0];
    if (arr[i] > arr[0]) swap(arr[i], arr[0]);
    return findMax(arr, length, i + 1);
}

bool isPalindrome(string str, int l = 0, int r = 0)
{
    if (!l) r = str.size() - 1;
    if (l > r) return true;
    if (str[l] == ' ') l++;
    if (str[r] == ' ') r--;
    if (str[l] != str[r]) return false;
    else return isPalindrome(str, l + 1, r - 1);
}

int main(){
}
