//
// Created by kev_j on 5/2/2020.
//

#include "midterm.h"

std::string encrypt(const std::string &plaintext, const std::string &key) {
    //if (plaintext.length() % key.length() != 0) {
    //throw ("Plaintext not divisible by key.");
    // }
    // Use count to terminate for loops once all of the characters in the
    // plaintext have been input.
    unsigned long count = 0;
    std::string encrypt;
    std::vector<std::vector<char>> code;
    for (;;) {
            std::vector<char> row;
        for (unsigned long j = 0; j < key.length(); ++j) {
            row.push_back(plaintext[count]);
            ++count;
            if (count == plaintext.length()) {
                break;
            }
        }
        if (count == plaintext.length()) {
            break;
        }
        code.push_back(row);
    }
    unsigned long count_two = 0;

    unsigned long col = 0;
    for (unsigned long i = 0; i < key.length(); ++i) {
        for (col = 0; col < count_two; ++col) {
            encrypt.push_back(code[i][count_two]);
            ++count;
            if (count == plaintext.length()) {
                break;
            }
        }
        if (count == plaintext.length()) {
            break;
        }
    }
    return encrypt;
}

/*std::string decrypt(const std::string &ciphertext, const std::string &key) {

}*/

void encrypt_draw(const std::string &plaintext, const std::string &key) {
    // Use count to terminate for loops once all of the characters in the
    // plaintext have been input.
    unsigned long count = 0;
    std::vector<std::vector<char>> code;
    for (int i = 0; i < 2; ++i) {
        for (unsigned long j = 0; j < key.length(); ++j) {
            std::cout << plaintext[count];
            //code.emplace_back(plaintext[count]);
            ++count;
            if (count == plaintext.length()) {
                break;
            }
        }
        if (count == plaintext.length()) {
            break;
        }
        std::cout << "\n";
        i = 0;
    }
}

void encrypt_draw_two(const std::string &plaintext, const std::string &key) {
    // Use count to terminate for loops once all of the characters in the
    // plaintext have been input.
    unsigned long count = 0;
    std::vector<std::vector<char>> code;
    for (;;) {
            std::vector<char> row;
        for (unsigned long j = 0; j < key.length(); ++j) {
            //std::cout << plaintext[count];
            row.push_back(plaintext[count]);
            ++count;
            if (count == plaintext.length()) {
                break;
            }
        }
        if (count == plaintext.length()) {
            break;
        }
        code.push_back(row);
    }
    // Print out the vector I made
    for (unsigned long i = 0; i < plaintext.length(); ++i) {
        for (unsigned long j = 0; j < key.length(); ++j) {
            std::cout << code[i][count];
            //code.emplace_back(plaintext[count]);
            ++count;
            if (count == plaintext.length()) {
                break;
            }
        }
        if (count == plaintext.length()) {
            break;
        }
        std::cout << "\n";
        i = 0;
    }
}
