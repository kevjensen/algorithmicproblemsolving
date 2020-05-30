//
// Created by kev_j on 5/26/2020.
//

#include <gtest/gtest.h>

#include "../BruteForceHash.h"

TEST(sha_256_1k, validation) {

    double time(30);
   EXPECT_EQ(time, timed_256(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 100, 1000));

}

TEST(sha_256_10k, validation) {

    double time(30);
    EXPECT_EQ(time, timed_256(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 100, 10000));

}

/*TEST(sha_256_100k, validation) {

    double time(30);
    EXPECT_EQ(time, timed_256(2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1000, 100000));

}*/