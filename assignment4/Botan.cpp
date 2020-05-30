//
// Created by kev_j on 5/24/2020.
//

#include "Botan.h"

#include <iostream>
#include <memory>

#include <botan/argon2.h>
#include <botan/bcrypt.h>
#include <botan/hash.h>
#include <botan/hex.h>
#include <botan/pwdhash.h>
#include <botan/scrypt.h>

void sha256(const std::string &input, std::vector<uint8_t> &output) {
    std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create("SHA-256"));
    hash->update(input);
    output.clear();
    output.resize(hash->output_length());
    hash->final(output.data());
}

bool check_sha256(const std::string &password, const std::vector<uint8_t> &expected, std::vector<uint8_t> &buffer) {
    sha256(password, buffer);
    return expected == buffer;
}

void sha256_iterated(const std::string &input, std::vector<uint8_t> &output, int iterations) {
    std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create("SHA-256"));
    // First iteration
    hash->update(input);
    output.clear();
    output.resize(hash->output_length());
    hash->final(output.data());

    // Remaining iterations
    for (int i = 1; i < iterations; ++i) {
        hash->update(output);
        hash->final(output.data());
    }
}

bool check_sha256_iterated(const std::string &password, const std::vector<uint8_t> &expected, int iterations,
                           std::vector<uint8_t> &buffer) {
    sha256_iterated(password, buffer, iterations);
    return buffer == expected;
}


bool check_bcrypt(const std::string &input, const std::string &expected) {
    return Botan::check_bcrypt(input, expected);
}

void pbkdf2_hmac_sha256(const std::string &password, const std::vector<uint8_t> &salt, size_t iterations, std::vector<uint8_t> &output,
                        size_t output_len) {
    output.clear();
    output.resize(output_len);

    std::unique_ptr<Botan::PasswordHashFamily> hashFamily =  Botan::PasswordHashFamily::create("PBKDF2(HMAC(SHA-256))");
    std::unique_ptr<Botan::PasswordHash> hash = hashFamily->from_params(iterations);
    hash->derive_key(output.data(), output.size(), password.c_str(), password.size(), salt.data(), salt.size());
}

bool check_pbkdf2_hmac_sha256(const std::string &password, const std::vector<uint8_t> &expected,
                              const std::vector<uint8_t> &salt, size_t iterations, std::vector<uint8_t> &buffer) {
    pbkdf2_hmac_sha256(password, salt, iterations, buffer, expected.size());
    return buffer == expected;
}


void scrypt(const std::string &password, const std::vector<uint8_t> &salt, size_t N, size_t r, size_t p,
            std::vector<uint8_t> &output, size_t output_len) {
    output.clear();
    output.resize(output_len);

    // Calling directly should be slightly faster that going through the PasswodHash interface because
    // it avoids creating a couple extra unique_ptr and function calls
    Botan::scrypt(output.data(), output_len, password, salt.data(), salt.size(), N, r, p);

    // Alternative way using PasswordHash interface
    //std::unique_ptr<Botan::PasswordHashFamily> hashFamily =  Botan::PasswordHashFamily::create("Scrypt");
    //std::unique_ptr<Botan::PasswordHash> hash = hashFamily->from_params(N, r, p);
    //hash->derive_key(output.data(), output.size(), password.c_str(), password.size(), salt.data(), salt.size());
}

bool check_scrypt(const std::string &password, const std::vector<uint8_t> &expected, const std::vector<uint8_t> &salt,
                  size_t N, size_t r, size_t p, std::vector<uint8_t> &buffer) {
    scrypt(password, salt, N, r, p, buffer, expected.size());
    return buffer == expected;
}

bool check_argon2(const std::string &password, const std::string &expected) {
    return Botan::argon2_check_pwhash(password.c_str(), password.size(), expected);
}