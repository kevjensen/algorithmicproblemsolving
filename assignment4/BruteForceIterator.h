//
// Created by kev_j on 5/26/2020.
//

#ifndef ASSIGNMENT4_BRUTEFORCEITERATOR_H
#define ASSIGNMENT4_BRUTEFORCEITERATOR_H

#include <iterator>
#include <string>

class BruteForceIterator {
public:
    // The necessary member types for an iterator
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::string;
    using difference_type = int;
    using pointer = std::string *;
    using reference = std::string &;

    BruteForceIterator(std::string alphabet, unsigned length, bool at_end = false);

    BruteForceIterator &operator++(); // prefix
    const BruteForceIterator operator++(int); // postfix

    std::string operator*() const;

    friend bool operator==(const BruteForceIterator &lhs, const BruteForceIterator &rhs);
private:
    void increment();

    std::string alphabet;
    unsigned length;
    bool at_end;
    std::string current;
};

bool operator==(const BruteForceIterator &lhs, const BruteForceIterator &rhs);
bool operator!=(const BruteForceIterator &lhs, const BruteForceIterator &rhs);

class BruteForce {
public:
    BruteForce(std::string alphabet, unsigned length);

    [[nodiscard]] BruteForceIterator begin() const;
    [[nodiscard]] BruteForceIterator end() const;

private:
    const std::string alphabet;
    const unsigned length;
};

#endif //ASSIGNMENT4_BRUTEFORCEITERATOR_H
