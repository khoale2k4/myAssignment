#include <iostream>

using namespace std;

template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~SLinkedList();
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
    string toString();
    SLinkedList(const SLinkedList& list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node* next)
        {
            this->next = next;
        }
        Node(T data, Node* next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T>* pList = nullptr;
        Node* current = nullptr;
        int index = 0;
    public:
        Iterator() {}
        Iterator(SLinkedList<T>* pList, bool begin);
        Iterator& operator=(const Iterator& iterator);
        void set(const T& e);
        T& operator*();
        bool operator!=(const Iterator& iterator);
        void remove();
        Iterator& operator++();
        Iterator operator++(int);
    };
};

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    this->pList = pList;
    if (begin) {
        if (pList && pList->head) {
            current = pList->head;
            index = 0;
        }
        else {
            current = nullptr;
            index = -1;
        }
    }
    else {
        current = nullptr;
        if (pList) index = pList->size();
        else index = 0;
    }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    if (current == nullptr || pList == nullptr || pList->head == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }

    if (current == pList->head) {
        pList->head = pList->head->next;
        if (pList->head == nullptr) { // list is now empty
            pList->tail = nullptr;
        }
        current = nullptr;
        index = -1;
    }
    else {
        Node* temp = pList->head;
        while (temp && temp->next != current) {
            temp = temp->next;
        }
        if (temp) {
            temp->next = current->next;
            if (temp->next == nullptr) { // last element was removed
                pList->tail = temp;
            }
            current = temp;
            index--;
        }
    }
    pList->count--; // decrease size of list
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    return !(this->current == iterator.current && this->index == iterator.index);
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    if (current == nullptr && index == -1) {
        throw std::out_of_range("Segmentation fault!");
    }

    if (current != nullptr) {
        current = current->next;
        index++;
    }
    else if (index == -1) {
        current = pList->head;
        index = 0;
    }

    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    if (current == nullptr && index == -1) {
        throw std::out_of_range("Segmentation fault!");
    }

    Iterator previous = *this;

    if (current != nullptr) {
        current = current->next;
        index++;
    }
    else if (index == -1) {
        current = pList->head;
        index = 0;
    }

    return previous;
}

template<class T>
T SLinkedList<T>::get(int index) {
    if (index < 0 || index > count) {
        throw std::out_of_range("");
    }
    Node* cur = head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    Node* cur = head;
    if (index < 0 || index >= count) return;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    cur->data = e;
}

template<class T>
bool SLinkedList<T>::empty() {
    return (!count);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    Node* cur = head;
    int i = 0;
    while (cur) {
        if (item == cur->data) {
            return i;
        }
        i++;
        cur = cur->next;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    Node* cur = head;
    while (cur) {
        if (cur->data == item) return true;
        cur = cur->next;
    }
    return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= this->count)
        throw std::out_of_range("The index is out of range!");
    Node* prev = NULL;
    Node* current = this->head;
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            if (prev == NULL) {
                this->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            if (current == this->tail) {
                this->tail = prev;
            }
            T data = current->data;
            delete current;
            this->count--;
            return data;
        }
        i++;
        prev = current;
        current = current->next;
    }
    return head->data;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    Node* prev = NULL;
    Node* current = this->head;
    while (current != NULL) {
        if (current->data == item) {
            if (prev == NULL) {
                this->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            if (current == this->tail) {
                this->tail = prev;
            }
            delete current;
            this->count--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear() {
    while (this->head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
    count = 0;
}


int main(){
}
