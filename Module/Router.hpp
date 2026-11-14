#pragma once

#include <iostream>
#include <string>
#include "../Lib/SAC.hpp"
#include "../Lib/DFS.hpp"







namespace router {
    void cli_from_to(const std::string cmd, Vector<Vector<edge>>& Bucket, Vector<Vector<edge>>& graph, size_t& start) {
        if (cmd != "from") return;

        size_t station_A;
        size_t station_B;
        std::string cmd1;
        std::string type;

        std::cin >> station_A;
        std::cin >> cmd1;
        std::cin >> station_B;
        std::cin >> type;

        if (station_A >= TOTAL_STATION || station_B >= TOTAL_STATION || cmd1 != "to") {
            std::cout << "Invalid command\n";
            return;
        }

        start = station_A;
        DFS(type, station_A, station_B, Bucket, graph);
        

        
    }
}