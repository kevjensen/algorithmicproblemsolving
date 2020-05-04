//
// Created by kev_j on 5/2/2020.
//

#include "midterm.h"

std::string decrypt(const std::string &ciphertext, const std::string &key) {
    std::string decrypted_string;
    //unsigned long position = 0;
    unsigned long row_num = ciphertext.length() / key.length();

    //unsigned long col_remainder = plaintext.length() & key.length();
    // Nested for loops that loop through the cipher text in the order of the key
    for (char i : key) {
        for (unsigned long count = 0; count <= row_num; ++count) {
            // This conditional determines if the value is an alphabetic letter, a space, or a punctuation. If it is
            // I push it to the encrypted string. Unfortunately, I persisted with the vector of vectors for too long
            // so I did not have enough time to get this function working properly.
            if (isalpha(ciphertext[static_cast<unsigned long>(i - '0')]) ||
            ciphertext[static_cast<unsigned long>(i - '0')] == ' ' ||
            ispunct(ciphertext[static_cast<unsigned long>(i - '0')])) {
                decrypted_string.push_back(ciphertext[static_cast<unsigned long>(i - '0')]);
                i = (static_cast<char>(static_cast<unsigned long>(i) + key.length()));
            }
        }
    }
    return decrypted_string;
}

std::string encrypt(const std::string &plaintext, const std::string &key) {
    // Throw exception of key length is greater than 10; would include the catch in main.cpp
    if (key.length() > 10) {
        throw std::length_error("Key length too long!");
    }
    // Declare encrypted string to return
    std::string encrypted_string;
    unsigned long position = 0;
    unsigned long col_num = plaintext.length() / key.length();

    // Nested for loops that loop through the plaintext in the order of the key
    for (char i : key) {
        for (unsigned long count = 0; count <= col_num; ++count) {
            // This helped prevent any unnecessary characters from pushing to the encrypted string
            if (position == plaintext.length()) {
                break;
            }
            // This conditional determines if the value is an alphabetic letter, a space, or a punctuation. If it is
            // I push it to the encrypted string and then increment the next push by the key length since the next row value
            // to push is the current position plus the key length. This also allowed me to push values to the encrypted
            // string if the plaintext.length % key.length != 0 without the risk of pushing unnecessary values because
            // of the conditional.
            if (isalpha(plaintext[static_cast<unsigned long>(i - '0')]) ||
            plaintext[static_cast<unsigned long>(i - '0')] == ' ' ||
            ispunct(plaintext[static_cast<unsigned long>(i - '0')])) {
                encrypted_string.push_back(plaintext[static_cast<unsigned long>(i - '0')]);
                i = (static_cast<char>(static_cast<unsigned long>(i) + key.length()));
                ++position;
            }
        }
    }
    return encrypted_string;
}