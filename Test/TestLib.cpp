#include <iostream>

#include "../Lib/Vector.hpp"


int main() {
    //Vector
    std::cout << "--- Vector ---\n";
    Vector<size_t> test_vector;
    
    test_vector.push_back(2);
    test_vector.push_back(20);
    test_vector.push_back(200);
    test_vector.push_back(2000);

    test_vector.show();
    
    std::cout << "size: " << test_vector.size() << '\n';

    test_vector.pop_back();
    
    std::cout << test_vector[0] << '\n';

    test_vector.show();

    Vector<size_t> copycat = test_vector;
    std::cout << "copycat: ";

    copycat.show();
    //


}