#pragma once

#include <string>
#include <iostream>
#include "../Lib/Vector.hpp"
#include "../Lib/SAC.hpp"


namespace SeatManager {
    void cli_pick(std::string cmd, Vector<Vector<edge>>& Bucket, Vector<edge>& current_route, size_t start)  {
        if (cmd != "pick") return;

        size_t arg; std::cin >> arg;

        if (Bucket.size() == 0) {
            std::cerr << "You must use cmd: from <station A> to <station B> <type> before using cmd pick" << std::endl;
            return;
        }

        if (arg >= Bucket.size()) return;

        current_route.clear();
        current_route = Bucket[arg];

        std::cout << "You have pick route: " << start;
        for (size_t i = 0; i < current_route.size(); i++) {
            std::cout << " -> " << current_route[i].to;
        }

        std::cout << '\n';
    }
}