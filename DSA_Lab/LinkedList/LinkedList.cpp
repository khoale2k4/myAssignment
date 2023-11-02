#include <iostream>

using namespace std;

class LinkedList {
public:
    class Node;
private:
    Node* head;
    Node* tail;
    int size;
public:
    class Node {
    private:
        int value;
        Node* next;
        friend class LinkedList;
    public:
        Node() {
            this->next = NULL;
        }
        Node(Node* node) {
            this->value = node->value;
            this->next = node->next;
        }
        Node(int value, Node* next = NULL) {
            this->value = value;
            this->next = next;
        }
    };
    LinkedList() : head(NULL), tail(NULL), size(0) {};
    void partition(int k);
};

void LinkedList::partition(int k) {
    if (!head || !head->next) {
        return;
    }
    Node* group1_head = NULL;
    Node* group1_tail = NULL;
    Node* group2_head = NULL;
    Node* group2_tail = NULL;
    Node* group3_head = NULL;
    Node* group3_tail = NULL;

    Node* current = head;


    while (current) {
        if (current->value < k) {
            if (!group1_head) {
                group1_head = current;
                group1_tail = current;
            }
            else {
                group1_tail->next = current;
                group1_tail = current;
            }
        }
        else if (current->value == k) {
            if (!group2_head) {
                group2_head = current;
                group2_tail = current;
            }
            else {
                group2_tail->next = current;
                group2_tail = current;
            }
        }
        else {
            if (!group3_head) {
                group3_head = current;
                group3_tail = current;
            }
            else {
                group3_tail->next = current;
                group3_tail = current;
            }
        }

        current = current->next;
    }

    if (group1_head) {
        head = group1_head;
        tail = group1_tail;
    }
    if (group2_head) {
        if (group1_head) {
            group1_tail->next = group2_head;
            tail = group2_tail;
        }
        else {
            head = group2_head;
            tail = group2_tail;
        }
    }
    if (group3_head) {
        tail = group3_tail;
        if (group2_head) {
            group2_tail->next = group3_head;
        }
        else if (group1_head) {
            group1_tail->next = group3_head;
        }
        else {
            head = group3_head;
        }
    }
}

int main()
{
}
