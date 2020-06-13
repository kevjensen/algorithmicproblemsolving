#ifndef FINAL_PROJECT_BOTAN_H
#define FINAL_PROJECT_BOTAN_H

#include <cstdint>
#include <string>
#include <vector>

#include "BruteForceIterator.h"
#include "SharedQueue.h"

// SHA-256
void sha256(const std::string &input, std::vector<uint8_t> &output);
bool check_sha256(const std::string &password, const std::vector<uint8_t> &expected, std::vector<uint8_t> &buffer);
void sha256_range(BruteForceIterator low, const BruteForceIterator &high);
void sha256_queue(int block_limit, int block_size, int num_threads);

// SHA-256 Iterated
void sha256_iterated(const std::string &input, std::vector<uint8_t> &output, int iterations);
bool check_sha256_iterated(const std::string &password, const std::vector<uint8_t> &expected, int iterations, std::vector<uint8_t> &buffer);
void iterated_sha256_range(BruteForceIterator low, const BruteForceIterator &high);
void iterated_sha256_queue(int block_limit, int block_size, int num_threads);

// bcrypt
bool check_bcrypt(const std::string &input, const std::string &expected);
void bcrypt_range(BruteForceIterator low, const BruteForceIterator &high);
void bcrypt_queue(int block_limit, int block_size, int num_threads);

// argon2
bool check_argon2(const std::string &password, const std::string &expected);
void argon2_range(BruteForceIterator low, const BruteForceIterator &high);
void argon2_queue(int block_limit, int block_size, int num_threads);

// Struct for tasks in the queue
struct NameHere {
    BruteForceIterator low, high;
};

void hash_cracker_sha256(SharedQueue<NameHere> &tasks);
void hash_cracker_iterated_sha256(SharedQueue<NameHere> &tasks);
void hash_cracker_bcrypt(SharedQueue<NameHere> &tasks);
void hash_cracker_argon2(SharedQueue<NameHere> &tasks);

double time_sha256_queue(int block_limit, int block_size, int num_threads);
double time_iterated_sha256_queue(int block_limit, int block_size, int num_threads);
double time_bcrypt_queue(int block_limit, int block_size, int num_threads);
double time_argon2_queue(int block_limit, int block_size, int num_threads);


#endif //FINAL_PROJECT_BOTAN_H
