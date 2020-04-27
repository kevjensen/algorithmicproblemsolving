//
// Created by kev_j on 4/23/2020.
//

#include <gtest/gtest.h>

#include "../ISBN.h"

TEST(isbn_10, True) {
    ISBN o;
    EXPECT_EQ(o.isbn_10("aaa"), "aaa");
}

