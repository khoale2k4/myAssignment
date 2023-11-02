#include <iostream>
#include <vector>


using namespace std;

class LLNode {
public:
    int val;
    LLNode* next;
    LLNode();
    LLNode(int val, LLNode* next);
};

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    LLNode* rs = new LLNode(0, 0);
    LLNode* cur = rs;
    vector<int> rsarr;
    int rem = 0;
    while (l1 && l0) {
        int plus = l1->val + l0->val + rem;
        rsarr.push_back(plus % 10);
        if (plus >= 10) rem = 1;
        else rem = 0;

        l1 = l1->next;
        l0 = l0->next;
    }
    while (l1) {
        int plus = l1->val + rem;
        rsarr.push_back(plus % 10);
        if (plus >= 10) rem = 1;
        else rem = 0;
        l1 = l1->next;
    }
    while (l0) {
        int plus = l0->val + rem;
        rsarr.push_back(plus % 10);
        if (plus >= 10) rem = 1;
        else rem = 0;
        l0 = l0->next;
    }
    if (rem) {
        rsarr.push_back(1);
    }
    for (size_t i = 0; i < rsarr.size(); i++) {
        cur->next = new LLNode(rsarr[i], nullptr);
        cur = cur->next;
    }
    cur = rs;
    rs = rs->next;
    delete cur;
    return rs;
}

int main()
{
}