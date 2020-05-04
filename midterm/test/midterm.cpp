//
// Created by kev_j on 5/2/2020.
//

#include "../midterm.h"
#include <gtest/gtest.h>

TEST(Encrypt, valid) {
    EXPECT_EQ(encrypt("Please work!", "012"), "Pa rlswkeeo!");
    EXPECT_EQ(encrypt("Attack at dawn", "012"), "Aa  wtcadntkta");
    EXPECT_EQ(encrypt("Please work!", "01"), "Pes oklaewr!");
    EXPECT_EQ(encrypt("Attack at dawn", "021"), "Aa  wtktatcadn");
    EXPECT_EQ(encrypt("Attack at dawn", "120"), "tcadntktaAa  w");
    EXPECT_EQ(encrypt("Hello Will", "012"), "HlWleoil l");
    EXPECT_EQ(encrypt("I like that this function actually does what it's supposed to.", "2310"),
            "l tiuiaa satso it snocld t'ust eahft uyehi pd.Ikht cntlow speo");
    EXPECT_EQ(encrypt("Lord of the Rings is BETTER THAN Star Trek but not Star Wars. Do you agree?", "013542"),
            "LfRiTAr or.oeo isEN bt  uedhgB SrtSaoao  THaknasyr esETte tr grtn R Tu WD ?");
}

TEST(Decrpyt, valid) {
    EXPECT_EQ(decrypt("Aa  wtcadntkta", "012"), "Attack at dawn");
}

TEST(Encrypt, Exception) {
    EXPECT_THROW(encrypt("Please Work!", "0123456789123"), std::length_error);
    EXPECT_THROW(encrypt("Attack at Dawn", "12345670899"), std::length_error);
}