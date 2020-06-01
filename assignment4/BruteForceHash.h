//
// Created by kev_j on 5/26/2020.
//

#ifndef ASSIGNMENT4_BRUTEFORCEHASH_H
#define ASSIGNMENT4_BRUTEFORCEHASH_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <botan/hex.h>

#include "Botan.h"
#include "BruteForceIterator.h"

double timed_256(const unsigned &pass_length, const std::string &alpha, int iterations, int func_iterations);

double timed_bcrypt(const unsigned &pass_length, const std::string &alpha, int iterations);

double timed_argon2(const unsigned &pass_length, const std::string &alpha, int iterations);

//std::string alpha_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//std::string alpha_lower = "abcdefghijklmnopqrstuvwxyz";

//std::string alpha_ints = "abcdefghijklmnopqrstuvwxyz0123456789";

//std::string alpha_ints_symbols = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=";

#endif //ASSIGNMENT4_BRUTEFORCEHASH_H
