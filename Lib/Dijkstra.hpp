
#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
#include <limits>
#include "SAC.hpp"
#include "Vector.hpp"

inline void Dijkstra(
    const std::string cmd,
    size_t start,
    size_t end,
    Vector<Vector<edge>>& Bucket,
    Vector<Vector<edge>>& graph
) {
    if (cmd != "Dijkstra" && cmd != "DIJKSTRA")
        return;

    std::string criterion;
    std::cin >> criterion;

    if (criterion != "time" && criterion != "price") {
        std::cout << "Invalid criterion\n";
        return;
    }

    Bucket.clear();

    size_t n = graph.size();

    if (start >= n || end >= n) {
        std::cout << "Invalid station\n";
        return;
    }

    const size_t INF =
        std::numeric_limits<size_t>::max();

    std::vector<size_t> dist(n, INF);
    std::vector<size_t> parent(n, INF);
    std::vector<edge> parent_edge(n);

    // Min Heap: (cost, station)
    using State = std::pair<size_t, size_t>;

    std::priority_queue<
        State,
        std::vector<State>,
        std::greater<State>
    > pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        size_t cost = pq.top().first;
        size_t u = pq.top().second;
        pq.pop();

        // Skip outdated states
        if (cost != dist[u])
            continue;

        if (u == end)
            break;

        for (size_t i = 0; i < graph[u].size(); i++) {
            edge E = graph[u][i];

            size_t v = E.to;

            if (v >= n)
                continue;

            size_t weight;

            if (criterion == "price")
                weight = E.price;
            else
                weight = E.time;

            // Prevent integer overflow
            if (cost > INF - weight)
                continue;

            size_t new_cost = cost + weight;

            // Relaxation
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                parent[v] = u;
                parent_edge[v] = E;

                pq.push({dist[v], v});
            }
        }
    }

    if (dist[end] == INF) {
        std::cout << "No route found\n";
        return;
    }

    // Reconstruct the shortest path
    Vector<edge> path;

    for (size_t cur = end;
         cur != start;
         cur = parent[cur]) {

        path.push_back(parent_edge[cur]);
    }

    // Reverse the path
    for (size_t l = 0, r = path.size();
         l + 1 < r;
         l++, r--) {

        edge tmp = path[l];
        path[l] = path[r - 1];
        path[r - 1] = tmp;
    }

    Bucket.push_back(path);

    size_t total_time = 0;
    size_t total_price = 0;

    // Print the route
    std::cout << "0> " << start;

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << " -> " << path[i].to;

        total_time += path[i].time;
        total_price += path[i].price;
    }

    std::cout << '\n';

    std::cout << "Total time: "
              << total_time << " minutes\n";

    std::cout << "Total price: "
              << total_price << " K VND\n";
}
