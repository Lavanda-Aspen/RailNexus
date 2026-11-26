#include <iostream>
#include <fstream>
#include "../Module/data.hpp"

int main() {
    std::fstream seat_file("../DataBase/Seat.txt", std::ios::in | std::ios::binary);
    std::fstream ticket_file("../DataBase/Ticket.txt", std::ios::out | std::ios::trunc | std::ios::binary);

    const char* sample_names[] = {
        "Nguyen Van An", "Tran Thi Binh", "Le Hoang Cuong", "Pham Minh Dung",
        "Hoang Thu Ha", "Vu Duc Huy", "Dang Ngoc Lan", "Bui Quang Minh",
        "Do Thanh Nam", "Ngo Mai Phuong", "Duong Tuan Anh", "Ly Thu Trang",
        "Trinh Quang Khai", "Phan Thao Vy", "Vo Dinh Trong", "Ngo Gia Bao"
    };
    size_t total_names = sizeof(sample_names) / sizeof(sample_names[0]);

    data::init_ticket(seat_file, ticket_file, sample_names, total_names);

    seat_file.close();
    ticket_file.close();

    // Đọc thử 5 vé đầu tiên ra màn hình để kiểm tra
    std::fstream check("../DataBase/Ticket.txt", std::ios::in | std::ios::binary);
    Ticket t;
    for (int i = 0; i < 5 && check.read(reinterpret_cast<char*>(&t), sizeof(t)); i++) {
        std::cout << t.ticket_id << " - " << t.name << '\n';
    }
    check.close();

    return 0;
}