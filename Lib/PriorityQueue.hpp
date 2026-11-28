#pragma once

template <typename T>
class PriorityQueue {
private:
    T* Q;
    int maxSize;
    int count;
public:
    PriorityQueue(int maxSize = 100) {
        this->maxSize = maxSize;
        Q = new T[maxSize];
        count = 0;
    }
    ~PriorityQueue() {
        delete[] Q;
    }
    bool isEmpty() const {
        return count == 0;
    }
    bool isFull() const {
        return count == maxSize;
    }
    int sizeQ() const {
        return count;
    }
    bool enqueue(const T& x) {
        if (isFull()) return false;
        int i = count - 1;
        while (i >= 0 && Q[i] > x) {
            Q[i + 1] = Q[i];
            i--;
        }
        Q[i + 1] = x;
        count++;
        return true;
    }
    bool dequeue(T& x) {
        if (isEmpty()) return false;
        count--;
        x = Q[count];
        return true;
    }
    T& frontQ() {
        return Q[count - 1];
    }
    const T& frontQ() const {
        return Q[count - 1];
    }
};