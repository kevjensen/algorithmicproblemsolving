#include <iostream>
#include <string>

#include "ISBN.h"

int main() {
    // Variables for user input and counts to check the validity of inputs with "X"
    std::string input;
    int count = 0;
    int x_count = 0;

    std::cout << "Please enter an ISBN: ";
    std::cin >> input;

    // Checks for if 'X' is in the correct position and if the input only has 1. If not it prints a warning.
    // I originally had these in my calculation loops but I couldn't get the print to resemble the example on
    // canvas, so I moved them here
    for (unsigned long i = 0; i < input.length(); ++i) {
        if (input[i] == 'X') {
            ++x_count;
        }
    }
    for (unsigned long i = 0; i < input.length(); ++i) {
        ++count;
        if ((input[i] == 'X' || input[i] == 'x') && count < 9) {
            std::cout << "X can only occur as a check digit.\n";
            break;
        }
    }
    if (x_count > 1) {
        std::cout << "Invalid number of Xs.\n";
    }

    std::cout << "The input " << input << " is:\n";
    std::cout << isbn_10_calculation(input) << "\n";
    std::cout << isbn_13_calculation(input);

    return 0;
}