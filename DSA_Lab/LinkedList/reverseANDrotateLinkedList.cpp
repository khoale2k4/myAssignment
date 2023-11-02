#include <iostream>

using namespace std;

class LLNode {
public:
    int val;
    LLNode* next;
    LLNode(); // Constructor: val = 0, next = nullptr
    LLNode(int val, LLNode* next); // Constructor with customized data
};

LLNode* reverseLinkedList(LLNode* head) {
    LLNode* newhead = nullptr;
    while (head) {
        newhead = new LLNode(head->val, newhead);
        head = head->next;
    }
    return newhead;
}

LLNode* rotateLinkedList(LLNode* head, int k) {
    // STUDENT ANSWER
    LLNode* cur = head;
    if (!head || !head->next) return head;
    int len = 1;
    while (cur->next) {
        len++;
        cur = cur->next;
    }
    cur->next = head;
    k %= len;
    k = len - k;
    while (k--) {
        cur = cur->next;
        head = head->next;
    }
    cur->next = nullptr;
    return head;
}

int main()
{
}
