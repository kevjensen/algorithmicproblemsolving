//
// Created by kev_j on 5/9/2020.
//

#include "gtest/gtest.h"
#include "../Botan.h"

TEST(SHA256, Valid) {
    {
        std::string input = "";
        std::string expected_output = "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855";
        EXPECT_TRUE(botan_256_hash(input, expected_output));
    }
    {
        std::string input = "a";
        std::string expected_output = "CA978112CA1BBDCAFAC231B39A23DC4DA786EFF8147C4E72B9807785AFEE48BB";
        EXPECT_TRUE(botan_256_hash(input, expected_output));
    }
}

TEST(SHA256_Iteration, Output) {
    // I expect this test to fail.
    {
        std::string input = "";
        int iterations = 100;
        std::string output = "";
        EXPECT_TRUE(botan_256_hash_iteration(input, iterations, output));
    }
}


TEST(Bcrypt, True) {
    {
        EXPECT_TRUE(bcrypt_check("", "$2a$05$CCCCCCCCCCCCCCCCCCCCC.7uG0VCzI2bS7j6ymqJi9CdcdxiRTWNy"));
    }
    {
        EXPECT_TRUE(bcrypt_check("U*U", "$2a$05$CCCCCCCCCCCCCCCCCCCCC.E5YPO9kmyuRGyh0XouQYb4YMJKvyOeW"));
    }
}

TEST(PBKDF2, Valid) {

    {
        EXPECT_TRUE(pbkdf2_hash_match(10000, Botan::hex_decode("0001020304050607"),
                "xyz", Botan::hex_decode("DEFD2987FA26A4672F4D16D98398432AD95E896BF619F6A6B8D4ED1FAF98E8B531B39FFB66966D0E115A6CD8E70B72D0")));
    }
}

TEST(Scrypt, Valid) {
    {
        EXPECT_TRUE(scrypt_hash("",
                Botan::hex_decode(""),
                Botan::hex_decode("77D6576238657B203B19CA42C18A0497F16B4844E3074AE8DFDFFA3FEDE21442FCD0069DED0948F8326A753A0FC81F17E8D3E0FB2E0D3628CF35E20C38D18906"),
                16, 1, 1));
    }
    {
        EXPECT_TRUE(scrypt_hash("password",
                                Botan::hex_decode("4E61436C"),
                                Botan::hex_decode("FDBABE1C9D3472007856E7190D01E9FE7C6AD7CBC8237830E77376634B3731622EAF30D92E22A3886FF109279D9830DAC727AFB94A83EE6D8360CBDFA2CC0640"),
                                1024, 8, 16));
    }
}

TEST(Argon2, Valid) {
    {
        EXPECT_TRUE(argon2_check("pass", 4, "$argon2i$v=19$m=8,t=1,p=1$YWFhYWFhYWE$3ney028aI7naIJ/5U///1ICfSVF0Ta4jh2SpJ1jhsCE"));
    }

}