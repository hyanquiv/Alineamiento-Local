#pragma once

#include <string>
#include <vector>

struct AlignmentLocalResult {
    int maxScore;
    std::string commonSubsequence;
    std::pair<size_t, size_t> positionSeq1;
    std::pair<size_t, size_t> positionSeq2;
    std::vector<std::vector<int>> scoreMatrix;
    bool foundElsewhere;
};

AlignmentLocalResult localAlignment(const std::string& s1, const std::string& s2, int gap);
void saveLocalAlignmentToFile(const AlignmentLocalResult& result, const std::string& filename);
