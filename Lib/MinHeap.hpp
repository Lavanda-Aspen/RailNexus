#pragma once
#include "Vector.hpp"

struct HeapState {
    size_t cost;
    size_t station;
};

class MinHeap {
    Vector<HeapState> data;
    void swap_nodes(size_t a, size_t b) {
        HeapState tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }
public:
    bool empty() { return data.size() == 0; }
    void push(HeapState value) {
        data.push_back(value);
        size_t i = data.size() - 1;
        while (i > 0) {
            size_t p = (i - 1) / 2;
            if (data[p].cost <= data[i].cost) break;
            swap_nodes(p, i);
            i = p;
        }
    }
    bool pop(HeapState& result) {
        if (empty()) return false;
        result = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();
        size_t i = 0;
        while (i < data.size() / 2) {
            size_t l = 2 * i + 1, r = l + 1;
            size_t best = l;
            if (r < data.size() && data[r].cost < data[l].cost)
                best = r;
            if (data[i].cost <= data[best].cost) break;
            swap_nodes(i, best);
            i = best;
        }
        return true;
    }
};
