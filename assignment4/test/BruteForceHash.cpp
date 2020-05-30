//
// Created by kev_j on 5/26/2020.
//

#include <gtest/gtest.h>

#include "../BruteForceHash.h"

TEST(sha_256_1k, validation) {

    double time(30);
   EXPECT_EQ(time, timed_256(2, alpha_upper, 1000));

}