//
// Created by kev_j on 4/23/2020.
//

#include <gtest/gtest.h>

#include "../ISBN.h"


// Used examples from canvas and this website http://www.hahnlibrary.net/libraries/isbncalc.html
TEST(isbn_10_calculation, return_valid) {
    EXPECT_EQ(isbn_10_calculation("0123456789"), "Valid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("0-521-33781-X"), "Valid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("0-521-33781-x"), "Valid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("3-540-20105-X"), "Valid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("4356721926"), "Valid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("1357924682"), "Valid ISBN-10.");
}

TEST(isbn_13_calculation, return_valid) {
    EXPECT_EQ(isbn_13_calculation("978-3-642-43001-5"), "Valid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("978-0-387-51768-1"), "Valid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("978-981-02-4897-0"), "Valid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("978 981 02 4897 0"), "Valid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("9-7-8--9-8-1--0-2--4-8-9-7-0-"), "Valid ISBN-13.");
    // Think Like a Programmer's ISBN-13
    EXPECT_EQ(isbn_13_calculation("978-1-59327-424-5"), "Valid ISBN-13.");
    // Plutarch's Fall of the Roman Republic ISBN-13
    EXPECT_EQ(isbn_13_calculation("9780140449341"), "Valid ISBN-13.");
}

TEST(isbn_10_calculation, return_invalid) {
    EXPECT_EQ(isbn_10_calculation("123456788"), "Invalid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("0-521-3378X-X"), "Invalid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("012345678"), "Invalid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("01234567890"), "Invalid ISBN-10.");
    EXPECT_EQ(isbn_10_calculation("012345678901"), "Invalid ISBN-10.");
}

TEST(isbn_13_calculation, return_invalid) {
    EXPECT_EQ(isbn_13_calculation("01234567890X5"), "Invalid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("012345678905X"), "Invalid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("978-0-486-63760-1"), "Invalid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("978-3-642-43001-3"), "Invalid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("790-981-02-4897-2"), "Invalid ISBN-13.");
    EXPECT_EQ(isbn_13_calculation("790-981-02-489"), "Invalid ISBN-13.");
}