#pragma once

template <typename T>
class Queue {
private:
    T* Q;
    int maxSize;
    int front;
    int count;
public:
    Queue(int maxSize = 100) {
        this->maxSize = maxSize;
        Q = new T[maxSize];
        front = 0;
        count = 0;
    }
    ~Queue() {
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
        int rear = (front + count) % maxSize;
        Q[rear] = x;
        count++;
        return true;
    }
    bool dequeue(T& x) {
        if (isEmpty()) return false;
        x = Q[front];
        front = (front + 1) % maxSize;
        count--;
        return true;
    }
    T& frontQ() {
        return Q[front];
    }
    const T& frontQ() const {
        return Q[front];
    }
};