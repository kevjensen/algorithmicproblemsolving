//
// Created by kev_j on 4/23/2020.
//

#include "ISBN.h"

std::string ISBN::isbn_10(std::string input) {
    if (input.length() > 0) {
        return input;
    }
    else {
        return "Not valid entry.";
    }
}
