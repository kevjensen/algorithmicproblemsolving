//
// Created by kev_j on 5/9/2020.
//

#ifndef BOTANASSIGNMENT_BOTAN_H
#define BOTANASSIGNMENT_BOTAN_H

#include <botan/exceptn.h>
#include <botan/hash.h>
#include <botan/hex.h>
#include <botan/pbkdf2.h>
#include <botan/bcrypt.h>
#include <botan/pwdhash.h>
#include <botan/argon2.h>
#include <iostream>

#endif //BOTANASSIGNMENT_BOTAN_H

bool botan_256_hash(std::string &input, std::string &output);
bool botan_256_hash_iteration(std::string &input, const int &iterations, std::string &output);
bool pbkdf2_hash_match(const size_t &iterations, const std::vector<uint8_t> &salt,
                                                       const std::string &passphrase, const std::vector<uint8_t> &output);
bool argon2_check(const char *password, size_t password_len, const std::string &hash);
bool bcrypt_check(const std::string &pass, const std::string &hash);
bool scrypt_hash(const std::string &passphrase, const std::vector<uint8_t> &salt,
        const std::vector<uint8_t> &output, const size_t &N, const size_t &R, const size_t &P);
