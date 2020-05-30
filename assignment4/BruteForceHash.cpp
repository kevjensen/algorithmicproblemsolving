//
// Created by kev_j on 5/26/2020.
//

#include "BruteForceHash.h"

double timed_256(const unsigned &pass_length, const std::string &alpha, int iterations, int func_iterations) {

    // Declare counter for the amount of iterations and clock to time it
    int i = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    auto expected = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");
    auto buffer = Botan::hex_decode("E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855");

    start = clock::now();
    // Hashing loop
    while (i < iterations) {
        for (const auto &word : BruteForce(alpha, pass_length)) {
            check_sha256_iterated(word, expected, func_iterations, buffer);
        }
        ++i;
}

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();

}

/*void timed_bcrypt(unsigned pass_length, std::string alpha, int iterations) {

    // Declare counter for the amount of functions
    int i = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;

    start = clock::now();

    // Hashing loop
    while (i < iterations) {
        for (const auto &word : BruteForce(alpha, pass_length)) {
            //check_bcrypt(word, const std::string &expected)
            ++i;
        }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}

void timed_argon2(unsigned pass_length, std::string alpha, int iterations) {

    // Declare counter for the amount of functions
    int i = 0;
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;

    start = clock::now();

    // Hashing loop
    while (i < iterations) {
        for (const auto &word : BruteForce(alpha, pass_length)) {
            //check_argon2(word, const std::string &expected)
            ++i;
        }
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    end = clock::now();
    // Seconds
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}*/