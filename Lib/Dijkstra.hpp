#pragma once

#include <iostream>
#include <string>
#include "SAC.hpp"
#include "Vector.hpp"

// Find and store one optimal route in Bucket.
inline void dijkstra_path(bool by_price, size_t start, size_t end,
                          Vector<Vector<edge>>& Bucket,
                          Vector<Vector<edge>>& graph) {
    Bucket.clear();
    size_t n = graph.size();
    if (n > TOTAL_STATION || start >= n || end >= n) return;

    size_t dist[TOTAL_STATION] = {};
    size_t parent[TOTAL_STATION] = {};
    edge parent_edge[TOTAL_STATION] = {};
    bool reached[TOTAL_STATION] = {};
    bool visited[TOTAL_STATION] = {};
    reached[start] = true;

    for (size_t step = 0; step < n; step++) {
        // Find the closest unvisited station.
        size_t u = n;
        for (size_t i = 0; i < n; i++) {
            if (!visited[i] && reached[i]) {
                if (u == n || dist[i] < dist[u]) u = i;
            }
        }
        if (u == n) break;
        visited[u] = true;
        if (u == end) break;

        // Relax outgoing edges.
        for (size_t i = 0; i < graph[u].size(); i++) {
            edge E = graph[u][i];
            size_t v = E.to;
            if (v >= n || visited[v]) continue;
            size_t weight = by_price ? E.price : E.time;
            size_t cost = dist[u] + weight;
            if (!reached[v] || cost < dist[v]) {
                reached[v] = true;
                dist[v] = cost;
                parent[v] = u;
                parent_edge[v] = E;
            }
        }
    }
    if (!visited[end]) return;

    // Follow predecessors backwards, then reverse the route.
    Vector<edge> path;
    for (size_t cur = end; cur != start; cur = parent[cur]) {
        path.push_back(parent_edge[cur]);
    }
    for (size_t l = 0, r = path.size(); l + 1 < r; l++, r--) {
        edge tmp = path[l];
        path[l] = path[r - 1];
        path[r - 1] = tmp;
    }
    Bucket.push_back(path);
}

// Handle the command and print the route, like BFS/DFS.
inline void Dijkstra(const std::string cmd, size_t start, size_t end,
                     Vector<Vector<edge>>& Bucket,
                     Vector<Vector<edge>>& graph) {
    if (cmd != "price" && cmd != "time") return;
    dijkstra_path(cmd == "price", start, end, Bucket, graph);
    if (Bucket.size() == 0) {
        std::cout << "No route found\n";
        return;
    }
    std::cout << "0> " << start;
    for (size_t i = 0; i < Bucket[0].size(); i++) {
        std::cout << " -> " << Bucket[0][i].to;
    }
    std::cout << '\n';
}
