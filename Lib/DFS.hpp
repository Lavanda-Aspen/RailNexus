#pragma once


#include <iostream>
#include <string>
#include "SAC.hpp"
#include "Vector.hpp"

void print_DFS(Vector<Vector<edge>>& Bucket, size_t start) {
    for (size_t i = 0; i < Bucket.size(); i++) {
        std::cout << i << "> " << start;
        for (size_t j = 0; j < Bucket[i].size(); j++) {
            std::cout << " -> " << Bucket[i][j].to;
        }
        std::cout << '\n';
    }
}


void DFS_recursion(size_t start, size_t end, size_t max, Vector<Vector<edge>>& Bucket, Vector<Vector<edge>>& graph, Vector<edge>& temp, bool* visited) {
    if (temp.size() >= max ) return;

    if (start == end) {
        Bucket.push_back(temp);
        return;
    }

    for (size_t i = 0; i < graph[start].size(); i++) {
        size_t to = graph[start][i].to;

        if (visited[to]) continue;

        visited[to] = true;
        temp.push_back(graph[start][i]);
        DFS_recursion(to, end, max, Bucket, graph, temp, visited);
        temp.pop_back();
        visited[to] = false;
    }

}


void DFS(const std::string cmd, size_t start, size_t end, Vector<Vector<edge>>& Bucket, Vector<Vector<edge>>& graph) {
    if (cmd != "DFS") return;

    size_t max ; std::cin >> max;

    Bucket.clear();
    Vector<edge> temp;
    bool visited[graph.size()] = {};

    DFS_recursion(start, end, max, Bucket, graph, temp, visited);

    print_DFS(Bucket, start);
}