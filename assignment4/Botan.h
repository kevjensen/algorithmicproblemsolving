//
// Created by kev_j on 5/26/2020.
//

#ifndef ASSIGNMENT4_BOTAN_H
#define ASSIGNMENT4_BOTAN_H

#include <cstdint>
#include <string>
#include <vector>

// SHA-256
void sha256(const std::string &input, std::vector<uint8_t> &output);
bool check_sha256(const std::string &password, const std::vector<uint8_t> &expected, std::vector<uint8_t> &buffer);

// SHA-256 Iterated
void sha256_iterated(const std::string &input, std::vector<uint8_t> &output, int iterations);
bool check_sha256_iterated(const std::string &password, const std::vector<uint8_t> &expected, int iterations, std::vector<uint8_t> &buffer);


// bcrypt
bool check_bcrypt(const std::string &input, const std::string &expected);

// pbkdf2
void pbkdf2_hmac_sha256(const std::string &password, const std::vector<uint8_t> &salt, size_t iterations,
                        std::vector<uint8_t> &output, size_t output_len);
bool check_pbkdf2_hmac_sha256(const std::string &password, const std::vector<uint8_t> &expected,
                              const std::vector<uint8_t> &salt, size_t iterations, std::vector<uint8_t> &buffer);

// scrypt
void scrypt(const std::string &password, const std::vector<uint8_t> &salt, size_t N, size_t r, size_t p,
            std::vector<uint8_t> &output, size_t output_len);
bool check_scrypt(const std::string &password, const std::vector<uint8_t> &expected, const std::vector<uint8_t> &salt,
                  size_t N, size_t r, size_t p, std::vector<uint8_t> &buffer);

// Argon2
bool check_argon2(const std::string &password, const std::string &expected);

#endif //ASSIGNMENT4_BOTAN_H
