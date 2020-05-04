//
// Created by kev_j on 5/2/2020.
//

#ifndef MIDTERM_MIDTERM_H
#define MIDTERM_MIDTERM_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

std::string encrypt(const std::string &plaintext, const std::string &key);
std::string decrypt(const std::string &ciphertext, const std::string &key);
void encrypt_draw(const std::string &plaintext, const std::string &key);
void encrypt_draw_two(const std::string &plaintext, const std::string &key);

int error();


#endif //MIDTERM_MIDTERM_H
