#include "Module/data.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "Lib/Vector.hpp"
#include "Lib/DFS.hpp"

void cli_help(const std::string cmd) {
    if (cmd != "help") return;

    std::cout << 
        "=== MARS-1 CLI Manual ===\n"
        "help\n"
        "from <station_A> to <station_B> <type>\n"
        "    type = trip, price, time, list <min> <max>\n\n"
        "Commands:\n"
        "  - help                          : Show system instructions.\n"
        "  - from <A> to <B> <type>        : Search routes (trip/price/time/list).\n"
        "  - pick                          : Select a trip from search results & view seats.\n"
        "  - book <row> <col>              : Book seat on the picked trip (auto-queue if full).\n"
        "  - find <ticket>                 : Look up ticket via Hash Table.\n"
        "  - cancel <ticket>               : Cancel ticket, push to Stack & notify queue.\n";
}






int main() {
    std::fstream trip_file("DataBase/Trip.txt");
    std::fstream seat_file("DataBase/Seat.txt");
    std::fstream ticket_file("DataBase/Ticket.txt");


    Vector<Vector<edge>> graph;
    Vector<Vector<edge>> Bucket;
    size_t start;

    data::load_graph(trip_file, graph);

    

    //data::init_data(trip_file, seat_file);


    DFS("DFS", 0, 3, Bucket, graph);


    trip_file.close();
    seat_file.close();
    ticket_file.close();
}






