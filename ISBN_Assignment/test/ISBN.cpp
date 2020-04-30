//
// Created by kev_j on 4/23/2020.
//

#include <gtest/gtest.h>

#include "../ISBN.h"

TEST(isbn_10, False) {
    ISBN o;
    EXPECT_FALSE(o.is_valid_isbn_10("111"));
}

TEST(isbn_10, True) {
    ISBN o;
    EXPECT_TRUE(o.is_valid_isbn_10("1111111111"));
    EXPECT_TRUE(o.is_valid_isbn_10("111111111X"));
    EXPECT_TRUE(o.is_valid_isbn_10("123-456-789-X"));
}

TEST(isbn_13, False) {
    ISBN o;
    EXPECT_FALSE(o.is_valid_isbn_13("123456789012"));
}

TEST(isbn_13, True) {
    ISBN o;
    EXPECT_TRUE(o.is_valid_isbn_13("1234567890123"));
    EXPECT_TRUE(o.is_valid_isbn_13("123-45678-9012-3"));
}

TEST(remove_dashes, True) {
    ISBN o;
    EXPECT_EQ(o.remove_dashes("123-456-789-0"), "1234567890");
    EXPECT_EQ(o.remove_dashes("1234-5678-9012-3"), "1234567890123");
}

TEST(isbn_10_calculation, testalpha) {
    std::string test;
    ISBN o;
    test = o.remove_dashes("0-486-63760-3");
    EXPECT_EQ(o.isbn_10_calculation(test), '3');
}

TEST(isbn_10_calculation, testx) {
    std::string test;
    ISBN o;
    test = o.remove_dashes("0-521-33781-X");
    EXPECT_EQ(o.isbn_10_calculation(test), ' ');
}