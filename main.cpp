#include "pch.h"
#include <iostream>
#include <fstream>
#include "alignment_local.h"

std::string readFastaSequence(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, sequence;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '>') continue;
        sequence += line;
    }
    return sequence;
}
//Comentar main para ejecutar pruebas unitarias

int main() {
    std::string seq1 = readFastaSequence("seq1.fasta");
    std::string seq2 = readFastaSequence("seq2.fasta");

    AlignmentLocalResult result = localAlignment(seq1, seq2, -2);
    saveLocalAlignmentToFile(result, "result_local.txt");

    std::cout << "Resultado guardado.\n";
    return 0;
}
