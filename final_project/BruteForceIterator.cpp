//
// Created by kev_j on 6/11/2020.
//

#include "BruteForceIterator.h"

#include <utility>

BruteForceIterator::BruteForceIterator(std::string alphabet_, unsigned length_, bool at_end_)
        : alphabet(std::move(alphabet_)), length(length_), at_end(at_end_) {
    // Initialize current
    for (unsigned i = 0; i < length; ++i) {
        current += alphabet[0];
    }
}

BruteForceIterator &BruteForceIterator::operator++() {
    increment();
    return *this;
}

const BruteForceIterator BruteForceIterator::operator++(int) {
    increment();
    return *this;
}

std::string BruteForceIterator::operator*() const {
    return current;
}

void BruteForceIterator::increment() {
    // If at end of sequence, don't increment
    if (at_end) {
        return;
    }

    // Attempt to increment char at size() - 1 - i
    for (unsigned i = 0; i < length; ++i) {
        auto alpha_index = alphabet.find(current[current.size() - 1 - i]);

        if (alpha_index < alphabet.size() - 1) {
            // Found one we can increment
            ++alpha_index;
            current[current.size() - 1 - i] = alphabet[alpha_index];
            // something here
            return;
        }
        // Can't increment, reset to beginning of alphabet
        current[current.size() - 1 - i] = alphabet[0];
    }

    // If you got here, you didn't hit the return in the loop, which means the loop
    // stopped because i >= length. That only occurs if you have gone through the
    // full sequence and attempted to increment past the end of the sequence
    at_end = true;
}

bool operator==(const BruteForceIterator &lhs, const BruteForceIterator &rhs) {
    return lhs.at_end == rhs.at_end && lhs.length == rhs.length
           && lhs.current == rhs.current && lhs.alphabet == rhs.alphabet;
}

bool operator!=(const BruteForceIterator &lhs, const BruteForceIterator &rhs) {
    return !(lhs == rhs);
}

BruteForce::BruteForce(std::string alphabet_, unsigned length_)
        : alphabet(std::move(alphabet_)), length(length_)
{}

BruteForceIterator BruteForce::begin() const {
    return BruteForceIterator(alphabet, length);
}

BruteForceIterator BruteForce::end() const {
    return BruteForceIterator(alphabet, length, true);
}