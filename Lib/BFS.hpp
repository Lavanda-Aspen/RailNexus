#pragma once

#include <string>
#include <iostream>
#include "SAC.hpp"
#include "Vector.hpp"

void BFS(const std::string cmd, size_t start, size_t end, Vector<Vector<edge>>& Bucket, Vector<Vector<edge>>& graph) {
    if (cmd != "BFS") return;

    Bucket.clear();
    bool visited[graph.size()] = {};
    size_t parent[graph.size()];
    edge parent_edge[graph.size()];

    Vector<size_t> q;
    size_t head = 0;

    visited[start] = true;
    q.push_back(start);

    while (head < q.size()) {
        size_t u = q[head++];
        if (u == end) {
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
            break;
        }

        for (size_t i = 0; i < graph[u].size(); i++) {
            size_t to = graph[u][i].to;
            if (visited[to]) continue;

            visited[to] = true;
            parent[to] = u;
            parent_edge[to] = graph[u][i];
            q.push_back(to);
        }
    }

    for (size_t i = 0; i < Bucket.size(); i++) {
        std::cout << i << "> " << start;
        for (size_t j = 0; j < Bucket[i].size(); j++) {
            std::cout << " -> " << Bucket[i][j].to;
        }
        std::cout << '\n';
    }
}