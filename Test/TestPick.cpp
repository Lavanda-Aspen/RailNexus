#include "../Module/data.hpp"
#include "../Module/Router.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "../Lib/Vector.hpp"
#include "../Lib/DFS.hpp"
#include "../Module/SeatManager.hpp"


int main() {
    std::fstream trip_file("../DataBase/Trip.txt");


    Vector<Vector<edge>> graph;
    Vector<Vector<edge>> Bucket;
    Vector<edge> current_route;
    size_t start;

    data::load_graph(trip_file, graph);

    std::string cmd;
    
    std::cout << "enter cmd: \"exit\" to exit this program\n\nenter these command:\npick 0\nfrom 1 to 0 DFS 3; pick 0; pick 5\n\n";
    
    while (true) {
        std::cout << "Enter: ";
        std::cin >> cmd;
        router::cli_from_to(cmd, Bucket, graph, start);
        SeatManager::cli_pick(cmd, Bucket, current_route, start);

        if (cmd == "exit") break;
    }

    trip_file.close();
}






