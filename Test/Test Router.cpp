#include "../Module/data.hpp"
#include "../Module/Router.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "../Lib/Vector.hpp"
#include "../Lib/DFS.hpp"


int main() {
    std::fstream trip_file("../DataBase/Trip.txt");


    Vector<Vector<edge>> graph;
    Vector<Vector<edge>> Bucket;
    size_t start;

    data::load_graph(trip_file, graph);

    std::string cmd;
    std::cout << "enter command: from 1 to 0 DFS 3\nEnter: ";
    std::cin >> cmd;
    router::cli_from_to(cmd, Bucket, graph, start);

    trip_file.close();
}






