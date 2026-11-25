#pragma once
#include <iostream>

inline const size_t SEATS_PER_CABIN = 20;
inline const size_t MAX_NAME_LENGTH = 30;
inline const size_t TOTAL_STATION = 20;
inline const size_t MAX_ROWS = 4;
inline const size_t MAX_COLS = 8;


typedef struct {
    char trip_id[7];        // trip_id = số dòng trong file Trip.txt
    char from[6];           //00001 - 99999
    char to[6];             //00001 - 99999
    char minute[4];         //060 - 720 phút
    char price[4];          //050 - 950 K
    char newline = '\n';
} Trip;

typedef struct {
    char trip_id[7];
    char rows[2];                           //2-9
    char cols[3];                           //05-40
} Seat;


typedef struct {
    size_t to;
    size_t time;
    size_t price;
    size_t trip_id;
} edge;

typedef struct {
    char ticket_id[12];             // "VE" + trip_id + row + col + '\0'
    char name[MAX_NAME_LENGTH];   
    char newline = '\n';
} Ticket;