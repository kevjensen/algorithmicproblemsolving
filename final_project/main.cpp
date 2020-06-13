#include <iostream>
#include <thread>
#include <cmath>

#include "Botan.h"

void timed_hash_row(double rate, std::string alpha_type, int alpha_len, int pw_len, std::string hash_name);
double rate(double time, int block_limit, int block_size);


int main() {

    // Created alphabets for easy math below
    std::string lower_case_alpha = "abcdefghijklmnopqrstuvwxyz";
    std::string lower_upper_alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lower_upper_int_alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string all = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-+=,.";

    // Timing Functions
    auto sha256_time = time_sha256_queue(10, 10000, static_cast<int>(std::thread::hardware_concurrency()));
    auto iterated_sha256_time = time_iterated_sha256_queue(10, 10000, static_cast<int>(std::thread::hardware_concurrency()));
    auto bcrypt_time = time_bcrypt_queue(10, 500, static_cast<int>(std::thread::hardware_concurrency()));
    auto argon2_time = time_argon2_queue(10, 500, static_cast<int>(std::thread::hardware_concurrency()));

    // Create rate objects to be used in the hash table below
    auto sha256_rate = rate(sha256_time, 10, 10000);
    auto iterated_sha256_rate = rate(iterated_sha256_time, 10, 10000);
    auto bcrypt_rate = rate(bcrypt_time, 10, 500);
    auto argon2_rate = rate(argon2_time, 10, 500);

    // Start of table
    std::cout << "Using " << std::thread::hardware_concurrency() << " threads:\n"
                                                                    "sha_256 rate = " << sha256_rate <<
              " hashes/sec\n"
              "iterated_sha256 rate = " << iterated_sha256_rate << " hashes/sec\n"
                                                                   "bcrypt rate = " << bcrypt_rate << " hashes/sec\n"
                                                                                                      "argon2id rate = " <<argon2_rate << " hashes/sec\n\n";

    std::cout << "Hash, Alphabet, Length 6, Length 7, Length 8, Length 9, Length 10, Length 11, Length 12\n";
    timed_hash_row(sha256_rate, "a-z", static_cast<int>(lower_case_alpha.length()), 6, "Sha-256");
    timed_hash_row(sha256_rate, "a-zA-z", static_cast<int>(lower_upper_alpha.length()), 6, "Sha-256");
    timed_hash_row(sha256_rate, "a-zA-z0-9", static_cast<int>(lower_upper_int_alpha.length()), 6, "Sha-256");
    timed_hash_row(sha256_rate, "a-zA-z0-9 + symbols", static_cast<int>(all.length()), 6, "Sha-256");
    timed_hash_row(iterated_sha256_rate, "a-z", static_cast<int>(lower_case_alpha.length()), 6, "Iterated Sha-256");
    timed_hash_row(iterated_sha256_rate, "a-zA-z", static_cast<int>(lower_upper_alpha.length()), 6, "Iterated Sha-256");
    timed_hash_row(iterated_sha256_rate, "a-zA-z0-9", static_cast<int>(lower_upper_int_alpha.length()), 6, "Iterated Sha-256");
    timed_hash_row(iterated_sha256_rate, "a-zA-z0-9 + symbols", static_cast<int>(all.length()), 6, "Iterated Sha-256");
    timed_hash_row(bcrypt_rate, "a-z", static_cast<int>(lower_case_alpha.length()), 6, "Bcrypt");
    timed_hash_row(bcrypt_rate, "a-zA-z", static_cast<int>(lower_upper_alpha.length()), 6, "Bcrypt");
    timed_hash_row(bcrypt_rate, "a-zA-z0-9", static_cast<int>(lower_upper_int_alpha.length()), 6, "Bcrypt");
    timed_hash_row(bcrypt_rate, "a-zA-z0-9 + symbols", static_cast<int>(all.length()), 6, "Bcrypt");
    timed_hash_row(argon2_rate, "a-z", static_cast<int>(lower_case_alpha.length()), 6, "Argon2");
    timed_hash_row(argon2_rate, "a-zA-z", static_cast<int>(lower_upper_alpha.length()), 6, "Argon2");
    timed_hash_row(argon2_rate, "a-zA-z0-9", static_cast<int>(lower_upper_int_alpha.length()), 6, "Argon2");
    timed_hash_row(argon2_rate, "a-zA-z0-9 + symbols", static_cast<int>(all.length()), 6, "Argon2");
    return 0;
}

void timed_hash_row(double rate, std::string alpha_type, int alpha_len, int pw_len, std::string hash_name) {
    // Sha-256 Timed Hash
    std::cout << hash_name << ", " << alpha_type << ", ";
    for (; pw_len <= 12; ++ pw_len) {
        std::cout << pow(alpha_len, pw_len) / rate << ", ";
    }

    std::cout << "\n";
}

double rate(double time, int block_limit, int block_size) {
    return (block_limit * block_size) / time;
}