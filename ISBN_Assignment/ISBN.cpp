//
// Created by kev_j on 4/23/2020.
//

#include "ISBN.h"

char ISBN::isbn_10_calculation(const std::string &input) {
    int num_for_calculation = 0;
    int coefficient = 10;
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (input[i] != 'X') {
            num_for_calculation += (input[i - '0'] * coefficient);
            --coefficient;
        } else {
            num_for_calculation += (input[i - 'I']);
        }
    }

    return static_cast<char>((num_for_calculation % 11) + '0');
}

bool ISBN::is_valid_isbn_10(const std::string &input) {
    // std::string input_minus_dashes;
    // Use count variable for boolean check
    int count = 0;
    // Checks validity of user input and pushes input to new string
    // which is used for the calculation functions
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            ++count;
            // input_minus_dashes.push_back(input[i]);
        } else if (input[i] == 'X' && input[i] == input.back()) {
            ++count;
        }
    }
    if (count == 10) {
        return true;
    } else {
        return false;
    }
}

bool ISBN::is_valid_isbn_13(const std::string &input) {
    // Use count variable for boolean check
    int count = 0;
    // Checks validity of user input
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            ++count;
            //input_minus_dashes.push_back(input[i]);
        }
    }
    if (count == 13) {
        return true;
    } else {
        return false;
    }
}

/*char ISBN::isbn_13_calculation(const std::string &input) {
    int num_for_calculation = 0;
    bool multiply_by_three = false;
    for (unsigned long i = 0; i < input.length(); ++i) {
        num_for_calculation += (input[i - '0'] * coefficient);
        -- coefficient;

    // Toggle to multiply by 3. I could just use modulo but I want to try this out
    multiply_by_three ^= false;
    }
    return reinterpret_cast<const char *>(num_for_calculation % 11 + '0');
}*/

std::string ISBN::remove_dashes(const std::string &input) {
    std::string input_minus_dashes;
    // Loops through the input string and removes dashes; returns a new string
    // to use for the calculation. I haven't decided whether or not I'll keep this
    // function or just incorporate it into the valid checks
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            input_minus_dashes.push_back(input[i]);
        }
    }
    return input_minus_dashes;
}
