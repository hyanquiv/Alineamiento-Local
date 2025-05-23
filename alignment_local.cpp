#include "pch.h"
#include "alignment_local.h"
#include <fstream>
#include <algorithm>

// Score simple: +1 si iguales, -2 si diferentes
int simpleScore(char a, char b) {
    return a == b ? 1 : -2;
}

// Alineamiento local (Smith-Waterman)
AlignmentLocalResult localAlignment(const std::string& s1, const std::string& s2, int gap) {
    size_t m = s1.size();
    size_t n = s2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    int maxScore = 0;
    size_t end_i = 0, end_j = 0;

    // === Inicialización de la matriz (ya está en 0 por defecto) ===

    // === Llenado de la matriz de puntuaciones ===
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int match = dp[i - 1][j - 1] + simpleScore(s1[i - 1], s2[j - 1]);
            int del = dp[i - 1][j] + gap;
            int ins = dp[i][j - 1] + gap;
            dp[i][j] = std::max({ 0, match, del, ins });

            if (dp[i][j] > maxScore) {
                maxScore = dp[i][j];
                end_i = i;
                end_j = j;
            }
        }
    }

    // === Backtracking para recuperar alineamiento ===
    std::string aligned1, aligned2;
    size_t i = end_i, j = end_j;
    while (i > 0 && j > 0 && dp[i][j] > 0) {
        if (dp[i][j] == dp[i - 1][j - 1] + simpleScore(s1[i - 1], s2[j - 1])) {
            aligned1 = s1[i - 1] + aligned1;
            aligned2 = s2[j - 1] + aligned2;
            --i; --j;
        }
        else if (dp[i][j] == dp[i - 1][j] + gap) {
            aligned1 = s1[i - 1] + aligned1;
            aligned2 = '-' + aligned2;
            --i;
        }
        else {
            aligned1 = '-' + aligned1;
            aligned2 = s2[j - 1] + aligned2;
            --j;
        }
    }

    // === Verificar si subsecuencia aparece de nuevo ===
    bool foundElsewhere = false;
    if (s1.find(aligned1, end_i) != std::string::npos || s2.find(aligned2, end_j) != std::string::npos) {
        foundElsewhere = true;
    }

    return {
        maxScore,
        aligned1,
        {i, end_i - 1},
        {j, end_j - 1},
        dp,
        foundElsewhere
    };
}

void saveLocalAlignmentToFile(const AlignmentLocalResult& result, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return;

    file << "Score máximo: " << result.maxScore << "\n";
    file << "Subsecuencia común: " << result.commonSubsequence << "\n";
    file << "Posición en S1: [" << result.positionSeq1.first << ", " << result.positionSeq1.second << "]\n";
    file << "Posición en S2: [" << result.positionSeq2.first << ", " << result.positionSeq2.second << "]\n";
    file << "¿Existe en otra parte?: " << (result.foundElsewhere ? "Sí" : "No") << "\n\n";

    file << "Matriz de puntuaciones:\n";
    for (const auto& row : result.scoreMatrix) {
        for (int val : row) {
            file << val << "\t";
        }
        file << "\n";
    }

    file.close();
}
