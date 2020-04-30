#include <iostream>

int main() {
    std::string test = "12";
    test[0] = static_cast<char>(static_cast<int>(test[0 + '0']) * 2);
    std::cout << test;
    return 0;
}
