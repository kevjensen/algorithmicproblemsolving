//
// Created by kev_j on 5/26/2020.
//

#include "BruteForceHash.h"

double timed_256(const unsigned &pass_length, const std::string &alpha, int iterations, int func_iterations) {

    // Declare counter for the amount of iterations and clock to time it
    int counter = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    auto expected = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
    auto buffer = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");

    start = clock::now();
    // Hashing loop
    for (const auto &word : BruteForce(alpha, pass_length)) {
        check_sha256_iterated(word, expected, func_iterations, buffer);
        ++counter;

        if (counter > iterations) {
            break;
        }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();

    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;

    return elapsed_seconds.count();

}

double timed_bcrypt(const unsigned &pass_length, const std::string &alpha, int iterations) {

    // Declare counter for the amount of functions
    int counter = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;

    start = clock::now();

    // Hashing loop
    for (const auto &word : BruteForce(alpha, pass_length)) {
        check_bcrypt(word, "$2a$05$CCCCCCCCCCCCCCCCCCCCC.7uG0VCzI2bS7j6ymqJi9CdcdxiRTWNy");
        ++counter;

        if (counter > iterations) {
            break;
        }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();

    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;

    return elapsed_seconds.count();

}

double timed_argon2(const unsigned &pass_length, const std::string &alpha, int iterations) {

    // Declare counter for the amount of functions
    int counter = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;

    start = clock::now();

    // Hashing loop
    for (const auto &word : BruteForce(alpha, pass_length)) {
        check_argon2(word, "$argon2i$v=19$m=8,t=1,p=1$YWFhYWFhYWE$3ney028aI7naIJ/5U///1ICfSVF0Ta4jh2SpJ1jhsCE");
        ++counter;

        if (counter > iterations) {
            break;
        }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();

    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;

    return elapsed_seconds.count();
}