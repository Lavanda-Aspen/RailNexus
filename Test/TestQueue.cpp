#include <iostream>
#include <string>
#include "../Lib/Queue.hpp"
#include "../Lib/PriorityQueue.hpp"

struct Customer {
    std::string name;
    int priority;

    bool operator>(const Customer& other) const {
        return priority > other.priority;
    }
};

int main() {
    Queue<std::string> q(3);
    q.enqueue("Khach 1");
    q.enqueue("Khach 2");
    q.enqueue("Khach 3");
    if (!q.enqueue("Khach 4")) {
        std::cout << "Queue day!\n";
    }

    std::string name;
    while (q.dequeue(name)) {
        std::cout << "Lay ra: " << name << '\n';
    }

    PriorityQueue<Customer> pq(5);
    pq.enqueue({"Lan", 2});
    pq.enqueue({"Minh", 9});
    pq.enqueue({"Hoa", 5});

    Customer c;
    while (pq.dequeue(c)) {
        std::cout << "Uu tien ra truoc: " << c.name << ":" << c.priority << '\n';
    }

    return 0;
}