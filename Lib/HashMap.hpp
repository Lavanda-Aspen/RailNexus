#pragma once

#include <string>

// 1. Cấu trúc một Hộp chứa (Node)
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode<K, V> *next;

    HashNode(const K &k, const V &v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

// 2. Bảng Băm (HashMap)
template <typename K, typename V>
class HashMap {
private:
    HashNode<K, V> **table;
    size_t capacity;
    size_t currentSize;

    // Hàm băm dành cho Key là số nguyên (size_t)
    size_t hashKey(const size_t &key) const {
        return key % capacity;
    }

    // Hàm băm dành cho Key là chuỗi (std::string)
    size_t hashKey(const std::string &key) const {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); i++) {
            hash = (hash * 31 + static_cast<size_t>(key[i])) % capacity;
        }
        return hash;
    }

public:
    // Khởi tạo bảng băm có 101 ngăn trống
    HashMap(size_t cap = 101) {
        capacity = cap;
        currentSize = 0;
        table = new HashNode<K, V>*[capacity];
        for (size_t i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Dọn dẹp bộ nhớ khi kết thúc
    ~HashMap() {
        clear();
        delete[] table;
    }

    // Xóa toàn bộ dữ liệu bên trong bảng
    void clear() {
        for (size_t i = 0; i < capacity; i++) {
            HashNode<K, V> *cur = table[i];
            while (cur != nullptr) {
                HashNode<K, V> *temp = cur;
                cur = cur->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        currentSize = 0;
    }

    // 3. Thêm mới hoặc Cập nhật (put)
    void put(const K &key, const V &value) {
        size_t index = hashKey(key);
        HashNode<K, V> *cur = table[index];

        // Nếu trùng Key thì cập nhật Value mới
        while (cur != nullptr) {
            if (cur->key == key) {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }

        // Chưa có thì chèn vào đầu danh sách liên kết
        HashNode<K, V> *newNode = new HashNode<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        currentSize++;
    }

    // 4. Tìm kiếm (get) - Trả về true nếu thấy, kết quả lưu vào outValue
    bool get(const K &key, V &outValue) const {
        size_t index = hashKey(key);
        HashNode<K, V> *cur = table[index];

        while (cur != nullptr) {
            if (cur->key == key) {
                outValue = cur->value;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Kiểm tra xem Key có tồn tại không
    bool containsKey(const K &key) const {
        size_t index = hashKey(key);
        HashNode<K, V> *cur = table[index];

        while (cur != nullptr) {
            if (cur->key == key) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // 5. Xóa phần tử theo Key (remove)
    bool remove(const K &key) {
        size_t index = hashKey(key);
        HashNode<K, V> *cur = table[index];
        HashNode<K, V> *prev = nullptr;

        while (cur != nullptr) {
            if (cur->key == key) {
                if (prev == nullptr) {
                    table[index] = cur->next;
                } else {
                    prev->next = cur->next;
                }
                delete cur;
                currentSize--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    // Trả về số lượng phần tử đang có
    size_t size() const {
        return currentSize;
    }
};


