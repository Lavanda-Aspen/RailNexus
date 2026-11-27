#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "SAC.hpp"
#include "Vector.hpp"
#include "MinHeap.hpp"

// Returns one optimal path in Bucket, or false if no valid route exists.
inline bool dijkstra_path(size_t start, size_t end, bool by_price,
                         Vector<Vector<edge>>& Bucket,
                         Vector<Vector<edge>>& graph) {
    Bucket.clear();
    const size_t n = graph.size();
    if (start >= n || end >= n) return false;
    const size_t INF = std::numeric_limits<size_t>::max();
    Vector<size_t> dist(n), parent(n);
    Vector<edge> parent_edge(n);
    for (size_t i = 0; i < n; ++i) {
        dist.push_back(INF);
        parent.push_back(INF);
        parent_edge.push_back(edge{});
    }
    MinHeap heap;
    dist[start] = 0;
    heap.push({0, start});
    HeapState state;
    while (heap.pop(state)) {
        size_t u = state.station;
        if (state.cost != dist[u]) continue;
        if (u == end) break;
        for (size_t i = 0; i < graph[u].size(); ++i) {
            edge e = graph[u][i];
            if (e.to >= n) continue;
            size_t w = by_price ? e.price : e.time;
            if (state.cost > INF - w) continue;
            size_t candidate = state.cost + w;
            if (candidate < dist[e.to]) {
                dist[e.to] = candidate;
                parent[e.to] = u;
                parent_edge[e.to] = e;
                heap.push({candidate, e.to});
            }
        }
    }
    if (dist[end] == INF) return false;
    Vector<edge> path;
    for (size_t cur = end; cur != start; cur = parent[cur])
        path.push_back(parent_edge[cur]);
    for (size_t l = 0, r = path.size(); l + 1 < r; ++l, --r) {
        edge tmp = path[l];
        path[l] = path[r - 1];
        path[r - 1] = tmp;
    }
    Bucket.push_back(path);
    return true;
}

inline void Dijkstra(const std::string cmd, size_t start, size_t end,
                     Vector<Vector<edge>>& Bucket,
                     Vector<Vector<edge>>& graph) {
    std::string criterion = cmd;
    if (cmd == "Dijkstra" || cmd == "DIJKSTRA") {
        if (!(std::cin >> criterion)) return;
    } else if (cmd != "price" && cmd != "time") return;
    if (criterion != "price" && criterion != "time") {
        Bucket.clear();
        std::cout << "Invalid criterion\n";
        return;
    }
    if (!dijkstra_path(start, end, criterion == "price", Bucket, graph)) {
        std::cout << "No route found or invalid station\n";
        return;
    }
    size_t total_time = 0, total_price = 0;
    std::cout << "0> " << start;
    for (size_t i = 0; i < Bucket[0].size(); ++i) {
        edge e = Bucket[0][i];
        std::cout << " -> " << e.to;
        total_time += e.time;
        total_price += e.price;
    }
    std::cout << "\nTotal time: " << total_time << " minutes\n";
    std::cout << "Total price: " << total_price << " K VND\n";
}
