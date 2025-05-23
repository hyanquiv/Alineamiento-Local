#include "pch.h"

#include "gtest/gtest.h"
#include "alignment_local.h"

TEST(LocalAlignmentTest, MaxScoreAndSubsequence) {
    std::string s1 = "TACGTCGC";
    std::string s2 = "TCCGTA";

    AlignmentLocalResult result = localAlignment(s1, s2, -2);

    EXPECT_GT(result.maxScore, 0);
    EXPECT_EQ(result.commonSubsequence, "CGT");
    EXPECT_TRUE(result.positionSeq1.first < s1.size());
    EXPECT_TRUE(result.positionSeq2.first < s2.size());
    EXPECT_FALSE(result.commonSubsequence.empty());
}
