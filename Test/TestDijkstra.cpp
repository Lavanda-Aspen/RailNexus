#include <fstream>
#include <iostream>
#include <string>
#include "../Module/data.hpp"
#include "../Module/Router.hpp"

int main() {
    std::fstream trip_file("DataBase/Trip.txt", std::ios::in );
    if (!trip_file.is_open())
        trip_file.open("../DataBase/Trip.txt", std::ios::in );
    if (!trip_file.is_open()) {
        std::cout << "Cannot open Trip.txt\n";
        return 1;
    }

    Vector<Vector<edge>> graph;
    Vector<Vector<edge>> Bucket;
    size_t start = 0;
    data::load_graph(trip_file, graph);

    std::string cmd;
    std::cout << "enter command: from 1 to 5 time\n"
              << "or: from 1 to 5 price\nEnter: ";
    if (std::cin >> cmd)
        router::cli_from_to(cmd, Bucket, graph, start);

    trip_file.close();
}
