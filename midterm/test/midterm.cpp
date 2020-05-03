//
// Created by kev_j on 5/2/2020.
//

#include "../midterm.h"
#include <gtest/gtest.h>

TEST(Encrypt, valid) {
    EXPECT_EQ(encrypt("Attack at dawn", "01234"), "test");
}