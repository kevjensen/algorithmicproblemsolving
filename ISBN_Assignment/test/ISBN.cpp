//
// Created by kev_j on 4/23/2020.
//

#include <gtest/gtest.h>

#include "../main.cpp"

/*TEST(isbn_10, False) {
    ISBN o;
    EXPECT_FALSE(o.is_valid_isbn_10("111"));
    EXPECT_FALSE(o.is_valid_isbn_10("12345678X9"));
}

TEST(isbn_10, True) {
    ISBN o;
    EXPECT_TRUE(o.is_valid_isbn_10("1111111111"));
    EXPECT_TRUE(o.is_valid_isbn_10("111111111X"));
    EXPECT_TRUE(o.is_valid_isbn_10("123-456-789-X"));
}*/

TEST(isbn_10_calculation, calculation) {
    EXPECT_EQ(isbn_10_calculation("0-486-63760-3"), 242);
    //EXPECT_EQ(isbn_10_calculation())
}

TEST(isbn_10_calculation, testx) {
    EXPECT_EQ(isbn_10_calculation("0-521-33781-X"), 165);
}

TEST(isbn_13_calculation, calculation) {
    EXPECT_EQ(isbn_13_calculation("978-3-642-43001-5"), 90);
    EXPECT_EQ(isbn_13_calculation("978-0-387-51768-1"), 140);
}