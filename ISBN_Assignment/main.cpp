#include <iostream>
#include <string>

int isbn_10_calculation(const std::string &input);
int isbn_13_calculation(const std::string &input);

int main() {
    // use a switch statement at the end to go through the cases I can
    // have
    return 0;
}

int isbn_10_calculation(const std::string &input) {
    int total = 0;
    int count = 0;
    int coefficient = 10;
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            ++count;
            total += (input[i] - '0') * coefficient;
            --coefficient;
        } else if (input[i] == 'X') {
            if (count != 9) {
                return 3;
            } else {
                ++count;
                total += 10;
            }
        }
    }
    if (count != 10) {
        return 2;
    }
    // return static_cast<char>((num_for_calculation % 11) + '0');
    return total;
}

int isbn_13_calculation(const std::string &input) {
    // Total value of string
    int total = 0;
    // Number of digits in string
    int count = 0;
    // Boolean value to determine if the respective digit will be multiplied by 3
    bool multiply_by_three = false;

    for (unsigned long i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            // Add to count to verify correct amount of digits
            ++count;
            if (!multiply_by_three) {
                total += input[i] - '0';
            } else {
                total += (input[i] - '0') * 3;
            }
        }
        // Toggle to multiply by 3. I could just use modulo but I want to try this operation out
        multiply_by_three ^= true;
    }
    if (count != 13) {
        return 2;
    }
    //return static_cast<char>(num_for_calculation % 10 + '0');
    return total;
}
