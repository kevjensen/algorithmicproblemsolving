//
// Created by kev_j on 4/23/2020.
//

#ifndef ISBN_ASSIGNMENT_ISBN_H
#define ISBN_ASSIGNMENT_ISBN_H

#include <string>
#include <iostream>

class ISBN {
public:
    char isbn_10_calculation(const std::string &input);
    char isbn_13_calculation(const std::string &input);
    std::string remove_dashes(const std::string &input);
    bool is_valid_isbn_10(const std::string &input);
    bool is_valid_isbn_13(const std::string &input);

};


#endif //ISBN_ASSIGNMENT_ISBN_H
