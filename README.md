# Hệ Thống Đặt Vé Tàu Hỏa

##  1. Cấu Trúc File 

Toàn bộ các cấu trúc dữ liệu và logic được phân rã thành các tệp `.hpp` độc lập

```
RailNexus/
├── DataBase/             
│   ├── Trip.txt          # Danh sách chuyến đi
│   ├── Seat.txt          # Trạng thái ma trận ghế ngồi 
│   └── Ticket.txt        # Danh sách mã vé phục vụ tra cứu Bảng băm
├── Lib/                  # Thư viện DSA
│   ├── Vector.hpp                
│   ├── DFS.hpp
│   └── SAC.hpp           # ghi mọi struct & const vào file nầy       
├── Module/    
│   ├── Data.hpp          # Đọc dữ liệu từ DataBase   
│   ├── Router.hpp        
│   ├── SeatManager.hpp   
│   └── TicketManager.hpp 
├── Test/                 
│   ├── Lib/
│   └── Module/
├── .gitignore            
├── README.md             
└── main.cpp              # Giao diện dòng lệnh (CLI)
```
---

## Giao Diện Dòng Lệnh & Luồng Tương Tác
Cần tách phần giao diện (CLI) và phần xử lý logic tức là ta sẽ có hai hàm riêng biệt cho 2 việc trên, phần logic sẽ chỉ cần gọi phần giao diện

### Các câu lệnh hỗ trợ:
* **`help`** : Hiển thị danh sách toàn bộ các câu lệnh hướng dẫn sử dụng hệ thống.
* **`from <station_A> to <station_B> <type>`** : Tìm kiếm hành trình giữa hai ga với các tùy chọn `<type>`:
	- `trip` : Tìm ít số tuyến nhất (Sử dụng thuật toán **BFS**).
	- `price` : Tìm hành trình rẻ nhất (Sử dụng thuật toán **Dijkstra**).
	- `time` : Tìm hành trình nhanh nhất (Sử dụng thuật toán **Dijkstra**).
	- `list <min> <max>` : Liệt kê mọi hành trình có số lượng lớn hơn min và nhỏ hơn max(Sử dụng thuật toán **DFS**).
* **`pick`** : Chọn một chuyến đi cụ thể từ danh sách kết quả vừa tìm kiếm ở lệnh `from...to`. Ngay sau lệnh này, hệ thống sẽ tự động hiển thị sơ đồ ghế ngồi 2 chiều của chuyến đó.
* **`book <row> <col>`** : Đặt vé tại vị trí hàng và cột ghế vừa chọn (chỉ sử dụng được sau khi đã `pick` chuyến). Nếu hết ghế, hệ thống tự động đưa khách vào `Queue`.
* **`find <ticket>`** : Tra cứu thông tin chi tiết vé tức thì bằng **Bảng băm (Hash Table)**.
* **`cancel <ticket>`** : Hủy vé theo mã,

---

##  3. Đọc File `fstream`

* **Kiểu dữ liệu nguyên không âm:** Nhất quán sử dụng `size_t` cho toàn bộ các chỉ số, mã, giá tiền, thời gian và số lượng ô nhớ để tương thích hoàn hảo với các hàm của `fstream` và tránh lỗi tràn bộ đệm.
* **Quy chuẩn đọc tệp (`fstream`):**
  * Mỗi bản ghi nằm trên một dòng, các trường ngăn cách bởi ký tự `'\0'`.

---

## 4. Chi Tiết Các tiêu chí Module  
### Router
- `from <A> to <B> <type>`
	- [x] DFS
	- [ ] BFS
	- [ ] Dijkstra

### SeatManager
- `pick`
- `book <row> <col>`
	- [ ] Mảng 2 chiều
	- [ ] Queue
	- [ ] Priority Queue cho khách VIP ``

### TicketManager
- `find <arg>`
- `cancel <arg>`



