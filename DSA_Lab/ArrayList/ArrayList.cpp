#include <iostream>

using namespace std;

template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array
public:
    ArrayList() { capacity = 5; count = 0; data = new T[5]; }
    ~ArrayList() { delete[] data; }
    void    add(T e);
    void    add(int index, T e);
    int     size();
    void    ensureCapacity(int index);
    void    ArrayList<T>::clear();
    T       ArrayList<T>::removeAt(int index);
    bool    ArrayList<T>::removeItem(T item);
};

template<class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if (cap >= capacity) {
        int newcap = capacity * 1.5;
        T* newdata = new T[newcap];
        for (int i = 0; i < capacity; i++) {
            newdata[i] = data[i];
        }
        for (int i = capacity; i < newcap; i++) {
            newdata[i] = 0;
        }
        capacity = newcap;
        data = newdata;
    }
}

template <class T>
void ArrayList<T>::add(T e) {
    if (count >= capacity) {
        ensureCapacity(count);
    }
    this->data[count] = e;
    count++;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
    if (index < 0 || index > capacity) throw std::out_of_range("the input index is out of range!");
    else {
        ensureCapacity(count + 1);
        for (int i = count; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = e;
        count++;
    }
}

template<class T>
int ArrayList<T>::size() {
    return count;
}

template<class T>
T ArrayList<T>::removeAt(int index) {
    T datare;
    if (index < 0 || index >= count) {
        throw std::out_of_range("index is out of range");
    }
    else {
        datare = data[index];
        for (int i = index; i < count; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }
    return datare;
}

template<class T>
bool ArrayList<T>::removeItem(T item) {
    bool deleted = false;
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            removeAt(i);
            deleted = true;
        }
    }
    return deleted;
}

template<class T>
void ArrayList<T>::clear() {
    count = 0;
    capacity = 5;
}

int main(){
}