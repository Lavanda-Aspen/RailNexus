#pragma once

#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdio>
#include "../Lib/SAC.hpp"
#include "../Lib/Vector.hpp"

void init_seat_cells(std::fstream& seat_file, size_t rows, size_t cols) {
    size_t size = rows * cols;
    for (size_t i = 0; i < size; i++) {
        if (rand() % 100 > 30) {
            seat_file.write("0", 1);
        } else {
            seat_file.write("1", 1);
        }
    }
    seat_file.write("\0\n", 2);
}

namespace data {
    void init_data(std::fstream& trip_file, std::fstream& seat_file) {
        std::srand(std::time(0));

        trip_file.seekp(0, std::ios::beg);
        seat_file.seekp(0, std::ios::beg);

        Trip trip_data;
        Seat seat_data;
        size_t trip_id = 1;

        for (size_t from = 0; from < TOTAL_STATION; from++) {
            for (size_t to = 0; to < TOTAL_STATION; to++) {

                if (from == to) continue;

                if (rand() % 100 > 30) continue;
                
                snprintf(trip_data.trip_id, 7, "%06zu", trip_id);
                snprintf(trip_data.from, 6, "%05zu", from);
                snprintf(trip_data.to, 6, "%05zu", to);

                size_t minute = (rand() % 12 + 1) * 60;
                size_t price = (rand() % 91) * 10 + 50;

                snprintf(trip_data.minute, 4, "%03zu", minute);
                snprintf(trip_data.price, 4, "%03zu", price);
                
                trip_file.write(reinterpret_cast<const char*>(&trip_data), sizeof(trip_data));

                snprintf(seat_data.trip_id, 7, "%06zu", trip_id++);

                size_t rows = rand() % (MAX_ROWS - 2) + 2;
                size_t cols = rand() % (MAX_COLS - 5) + 5;

                snprintf(seat_data.rows, 2, "%01zu", rows);
                snprintf(seat_data.cols, 3, "%02zu", cols);

                seat_file.write(reinterpret_cast<const char*>(&seat_data), sizeof(seat_data));
                init_seat_cells(seat_file, rows, cols);
            }
        }
 
    }

    void load_graph(std::fstream& trip_file, Vector<Vector<edge>>& graph) {
        trip_file.seekg(0, std::ios::beg);
        Trip trip_data;
        edge E;

        while (trip_file.read(reinterpret_cast<char*>(&trip_data), sizeof(trip_data))) {
            E.to = std::stoull(trip_data.to, nullptr, 10);
            E.time = std::stoull(trip_data.minute, nullptr, 10);
            E.price = std::stoull(trip_data.price, nullptr, 10);
            E.trip_id =std::stoull(trip_data.trip_id, nullptr, 10);

            size_t from = std::stoull(trip_data.from, nullptr, 10);

            if (graph.size() == from + 1) {
                graph[from].push_back(E);
            } else {
                Vector<edge> temp;
                temp.push_back(E);
                graph.push_back(temp);
            }
            
        }
    }

    void init_ticket(std::fstream& seat_file, std::fstream& ticket_file, 
        const char* names[], size_t total_names) {
        if (total_names == 0) return;

        seat_file.clear();
        seat_file.seekg(0, std::ios::beg);
        ticket_file.seekp(0, std::ios::beg);

        Seat seat_data;
        Ticket ticket_data;
        size_t name_idx = 0;

        while (seat_file.read(reinterpret_cast<char*>(&seat_data), sizeof(seat_data))) {
            size_t rows = std::stoull(seat_data.rows);
            size_t cols = std::stoull(seat_data.cols);
            size_t total_seats = rows * cols;

            for (size_t i = 0; i < total_seats; i++) {
                char cell;
                seat_file.read(&cell, 1);

                if (cell == '1') {
                    size_t r = (i / cols) + 1;
                    size_t c = (i % cols) + 1;

                    snprintf(ticket_data.ticket_id, sizeof(ticket_data.ticket_id),
                            "VE%s%01zu%02zu", seat_data.trip_id, r, c);

                    memset(ticket_data.name, 0, sizeof(ticket_data.name));
                    snprintf(ticket_data.name, sizeof(ticket_data.name), "%s",
                            names[name_idx % total_names]);
                    name_idx++;

                    ticket_file.write(reinterpret_cast<const char*>(&ticket_data), sizeof(ticket_data));
                }
            }

            char ch;
            while (seat_file.read(&ch, 1) && ch != '\n') {}
        }
    }

   
}

