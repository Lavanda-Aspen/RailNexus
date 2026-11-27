#include <iostream>
#include <cassert>
#include "../Lib/Dijkstra.hpp"

int main() {
    Vector<Vector<edge>> graph;
    Vector<Vector<edge>> bucket;
    Vector<edge> empty;
    for (size_t i = 0; i < 6; ++i) graph.push_back(empty);
    // edge = {destination, time, price, trip_id}
    graph[0].push_back({1, 60, 300, 1});
    graph[1].push_back({4, 60, 300, 2});
    graph[0].push_back({2, 180, 50, 3});
    graph[2].push_back({4, 180, 50, 4});
    graph[0].push_back({4, 500, 900, 5});
    graph[2].push_back({0, 10, 10, 6});
    graph[0].push_back({1, 80, 400, 7});
    // Fastest path: 0 -> 1 -> 4 (120 minutes).
    bool found = dijkstra_path(0, 4, false, bucket, graph);
    assert(found && bucket.size() == 1 && bucket[0].size() == 2);
    assert(bucket[0][0].trip_id == 1 && bucket[0][1].trip_id == 2);
    std::cout << "PASS: fastest route\n";
    found = dijkstra_path(0, 4, true, bucket, graph);
    assert(found && bucket.size() == 1 && bucket[0].size() == 2);
    assert(bucket[0][0].trip_id == 3 && bucket[0][1].trip_id == 4);
    std::cout << "PASS: cheapest route\n";
    found = dijkstra_path(0, 5, false, bucket, graph);
    assert(!found && bucket.size() == 0);
    std::cout << "PASS: unreachable station\n";
    found = dijkstra_path(0, 0, true, bucket, graph);
    assert(found && bucket.size() == 1 && bucket[0].size() == 0);
    std::cout << "PASS: same station\n";
    found = dijkstra_path(0, 6, false, bucket, graph);
    assert(!found && bucket.size() == 0);
    std::cout << "PASS: invalid station\n";
    MinHeap heap;
    heap.push({20, 0}); heap.push({5, 1}); heap.push({10, 2});
    HeapState s;
    bool ok = heap.pop(s); assert(ok && s.cost == 5);
    ok = heap.pop(s); assert(ok && s.cost == 10);
    ok = heap.pop(s); assert(ok && s.cost == 20);
    ok = heap.pop(s); assert(!ok);
    std::cout << "PASS: min heap\nAll tests passed\n";
}
