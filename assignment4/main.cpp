#include <iostream>
#include <math.h>
#include "BruteForceHash.h"

void sha_256_hash_result();
void bcrypt_hash_result();
void argon2_hash_result();

int main() {

    /*//Sha256 timed hashes
    auto sha256_pl2_upperalpha_1k = timed_256(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10000, 1000);
    std::cout << "Sha-256 1k function iterations with password length 2 and uppercase alphabet: "
              << sha256_pl2_upperalpha_1k <<
              " seconds\nHashes per second: " << 10000 / sha256_pl2_upperalpha_1k << "\n\n";

    //Larger alphabets slow the hashing process
    auto sha256_pl2_allalpha_10k = timed_256(2, "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=",
                                             10000, 10000);
    std::cout
            << "Sha-256 10k function iterations with password length 2 and uppercase alphabet, integers, and symbols: "
            << sha256_pl2_allalpha_10k << " seconds\nHashes per second: " << 10000 / sha256_pl2_allalpha_10k << "\n\n";

    auto sha256_pl2_upperalpha_100k = timed_256(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10000, 100000);
    std::cout << "Sha-256 100k function iterations with password length 2 and uppercase alphabet: "
              << sha256_pl2_upperalpha_100k << " seconds\nHashes per second: " << 10000 / sha256_pl2_upperalpha_100k << "\n\n";

    auto sha256_pl2_allalpha_100k = timed_256(2, "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=", 5000, 100000);
    std::cout << "Sha-256 100k function iterations with password length 2 and uppercase alphabet, integers, and symbols: "
              << sha256_pl2_allalpha_100k << " seconds\nHashes per second: " << 5000 / sha256_pl2_allalpha_100k << "\n\n";

    //auto sha256_pl2_allalpha_100k_result = 5000 / sha256_pl2_allalpha_100k;

    //Argon2 Timed hashes
    auto argon2_pl2_upperalpha_10k = timed_argon2(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10000);
    std::cout << "Argon2 10k iterations with password length 2 and uppercase alphabet: "
              << argon2_pl2_upperalpha_10k << " seconds.\nHashes per second: " << 10000 / argon2_pl2_upperalpha_10k
              << "\n\n";

    auto argon2_pl2_allalpha_10k = timed_argon2(2, "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=", 10000);
    std::cout << "Argon2 10k iterations with password length 2 and uppercase alphabet, integers, and symbols: "
              << argon2_pl2_allalpha_10k << " seconds.\nHashes per second: " << 10000 / argon2_pl2_allalpha_10k
              << "\n\n";

    auto argon2_pl6_allalpha_10k = timed_argon2(6, "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=", 10000);
    std::cout << "Argon2 10k iterations with password length 6 and uppercase alphabet, integers, and symbols: "
              << argon2_pl6_allalpha_10k << " seconds.\nHashes per second: " << 10000 / argon2_pl6_allalpha_10k
              << "\n\n";

    auto argon2_pl6_upperalpha_10k = timed_argon2(6, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10000);
    std::cout << "Argon2 10k iterations with password length 6 and uppercase alphabet: "
              << argon2_pl6_upperalpha_10k << " seconds\nHashes per second: " << 10000 / argon2_pl6_upperalpha_10k
              << "\n\n";

    auto argon2_pl6_upperalpha_100k = timed_argon2(6, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 100000);
    std::cout << "Argon2 100k iterations with password length 6 and uppercase alphabet: "
              << argon2_pl6_upperalpha_100k << " seconds\nHashes per second: " << 100000 / argon2_pl6_upperalpha_100k
              << "\n\n";

    //Bcrypt Timed hashes
    auto bcrypt_pl2_upperalpha_1k = timed_bcrypt(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1000);
    std::cout << "Bcrypt 1k iterations with password length 2 and uppercase alphabet: "
              << bcrypt_pl2_upperalpha_1k << " seconds\nHashes per second: " << 1000 / bcrypt_pl2_upperalpha_1k
              << "\n\n";

    auto bcrypt_pl4_upperalpha_10k = timed_bcrypt(4, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 10000);
    std::cout << "Bcrypt 10k iterations with password length 4 and uppercase alphabet: "
              << bcrypt_pl4_upperalpha_10k << " seconds\nHashes per second: " << 10000 / bcrypt_pl4_upperalpha_10k
              << "\n\n";*/

    sha_256_hash_result();
    bcrypt_hash_result();
    argon2_hash_result();

}

void sha_256_hash_result() {
    std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string alpha_ints_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=";

    std::cout << "Sha-256 iterated 1k times: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha, 10000, 1000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha.length() << ": \n" <<
        rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
        " days\n";
    }
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha_ints_symbols, 10000, 1000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha_ints_symbols.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha_ints_symbols.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    std::cout << "Sha-256 iterated 10k times: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha, 10000, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha_ints_symbols, 10000, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha_ints_symbols.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha_ints_symbols.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    std::cout << "Sha-256 iterated 100k times: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha, 10000, 100000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    for (unsigned length = 2; length <= 12; ++length) {
        auto sha_256_hash_time = timed_256(length, alpha_ints_symbols, 10000, 100000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha_ints_symbols.length(), length);
        double rate = pwtotal / sha_256_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha_ints_symbols.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
}

void bcrypt_hash_result() {
    std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string alpha_ints_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=";

    std::cout << "Bcrypt: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto bcrypt_hash_time = timed_bcrypt(length, alpha_ints_symbols, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha_ints_symbols.length(), length);
        double rate = pwtotal / bcrypt_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha_ints_symbols.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    std::cout << "Bcrypt: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto bcrypt_hash_time = timed_bcrypt(length, alpha, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha.length(), length);
        double rate = pwtotal / bcrypt_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
}
void argon2_hash_result() {
    std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string alpha_ints_symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+=";

    std::cout << "Argon Dos: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto argon2_hash_time = timed_argon2(length, alpha, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha.length(), length);
        double rate = pwtotal / argon2_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
    std::cout << "Argon Dos: \n";
    for (unsigned length = 2; length <= 12; ++length) {
        auto argon2_hash_time = timed_argon2(length, alpha_ints_symbols, 10000);

        //The part I wish I had done this way originally. So many hours of life lost to 5 lines of code
        double pwtotal =  pow(alpha_ints_symbols.length(), length);
        double rate = pwtotal / argon2_hash_time;
        std::cout << "Estimated time to brute force password of length " << length << " and alphabet of length " << alpha_ints_symbols.length() << ": \n" <<
                  rate << " seconds\n" << rate / 60 << " minutes\n" << rate / 60 / 60 << " hours\n" << rate / 60 / 60 / 24 <<
                  " days\n";
    }
}