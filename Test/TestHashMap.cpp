#include <iostream>
#include <string>
#include "../Lib/HashMap.hpp"

int main() {
    std::cout << "--- Test HashMap ---\n";
    
    // Tạo bảng băm lưu Mã vé (string) -> Số ghế (size_t)
    HashMap<std::string, size_t> test_map;

    // 1. Test thêm dữ liệu (put)
    test_map.put("VE01", 12);
    test_map.put("VE02", 25);
    test_map.put("VE03", 40);
    std::cout << "So luong ve hien tai: " << test_map.size() << '\n';

    // 2. Test tìm kiếm (get)
    size_t soGhe = 0;
    if (test_map.get("VE02", soGhe)) {
        std::cout << "Tim thay VE02 -> So ghe: " << soGhe << '\n';
    } else {
        std::cout << "Khong tim thay VE02\n";
    }

    // 3. Test cập nhật (put trùng key)
    test_map.put("VE02", 99);
    if (test_map.get("VE02", soGhe)) {
        std::cout << "Sau khi sua VE02 -> So ghe moi: " << soGhe << '\n';
    }

    // 4. Test xóa (remove)
    test_map.remove("VE01");
    if (!test_map.get("VE01", soGhe)) {
        std::cout << "Da xoa VE01 thanh cong! Con lai: " << test_map.size() << " ve.\n";
    }

    return 0;
}