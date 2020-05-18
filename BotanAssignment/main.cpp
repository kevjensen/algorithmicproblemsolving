#include <iostream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

#include "Botan.h"


void sha_256_timed(int iterations);

void sha_256_iterated_timed(int iterations);

void pbdkf2_timed(int iterations);

void bcrypt_timed(int iterations);

void scrypt_timed(int iterations);

void argon2id_timed(int iterations);

int main() {
    sha_256_timed(5);
    sha_256_iterated_timed(1);
    pbdkf2_timed(10);
    bcrypt_timed(5);
    scrypt_timed(5);
    argon2id_timed(5);
    return 0;
}

void sha_256_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        std::string input = "";
        std::string output = "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855";
        botan_256_hash(input, output);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time SHA-256: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time SHA-256: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time SHA-256: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time SHA-256: " << total_nanoseconds.count() << "ns\n";
}

void sha_256_iterated_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        std::string input = "";
        int hash_iterations = 100;
        std::string output = "";
        botan_256_hash_iteration(input, hash_iterations, output);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time SHA-256 Iterated: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time SHA-256 Iterated: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time SHA-256 Iterated: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time SHA-256 Iterated: " << total_nanoseconds.count() << "ns\n";
}

void pbdkf2_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        pbkdf2_hash_match(10000, Botan::hex_decode("0001020304050607"),
                          "xyz",
                          Botan::hex_decode("DEFD2987FA26A4672F4D16D98398432AD95E896BF619F6A6B8D4ED1FAF98E8B531B39FFB66966D0E115A6CD8E70B72D0"));

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time PBDKF2: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time PBDKF2: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time PBDKF2: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time PKDKF2: " << total_nanoseconds.count() << "ns\n";
}

void bcrypt_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        bcrypt_check("", "$2a$05$CCCCCCCCCCCCCCCCCCCCC.7uG0VCzI2bS7j6ymqJi9CdcdxiRTWNy");

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time BCRYPT: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time BCRYPT: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time BCRYPT: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time BCRYPT: " << total_nanoseconds.count() << "ns\n";

}

void scrypt_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        scrypt_hash("",
                    Botan::hex_decode(""),
                    Botan::hex_decode("77D6576238657B203B19CA42C18A0497F16B4844E3074AE8DFDFFA3FEDE21442FCD0069DED0948F8326A753A0FC81F17E8D3E0FB2E0D3628CF35E20C38D18906"),
                    16, 1, 1);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time SCRYPT: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time SCRYPT: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time SCRPYT: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time SCRYPT: " << total_nanoseconds.count() << "ns\n";
}

void argon2id_timed(int iterations) {
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start, end;
    std::chrono::duration<double> total_seconds;
    std::chrono::duration<double, std::milli> total_milliseconds;
    std::chrono::duration<double, std::micro> total_microseconds;
    std::chrono::duration<double, std::nano> total_nanoseconds;
    for (int i = 0; i != iterations; ++i) {
        start = clock::now();

        argon2_check("pass", 4, "$argon2i$v=19$m=8,t=1,p=1$YWFhYWFhYWE$3ney028aI7naIJ/5U///1ICfSVF0Ta4jh2SpJ1jhsCE");

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);

        end = clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        total_seconds += elapsed_seconds;

        std::chrono::duration<double, std::milli> elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start);
        total_milliseconds += elapsed_milliseconds;

        std::chrono::duration<double, std::micro> elapsed_microseconds =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_microseconds += elapsed_microseconds;

        std::chrono::duration<double, std::nano> elapsed_nanoseconds =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_nanoseconds += elapsed_nanoseconds;

    }

    // Seconds
    std::cout << "Elapsed time Argon: " << total_seconds.count() / iterations << "s\n";
    // Milliseconds
    std::cout << "Elapsed time Argon: " << total_milliseconds.count() / iterations << "ms\n";
    // Microseconds
    std::cout << "Elapsed time Argon: " << total_microseconds.count() / iterations << "us\n";
    // Nanoseconds
    std::cout << "Elapsed time Argon: " << total_nanoseconds.count() << "ns\n";
}