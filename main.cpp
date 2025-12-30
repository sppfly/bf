#include <cstddef>
#include <format>
#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "checker.hpp"

int main() {
    // constexpr int BIN_COUNT = 10;
    for (int i = 0; i < 1; i++) {

        std::string sequence_file = std::format("/data/projects/bf/dna_sequences/dna_sequence_{}.txt", i + 1);
        std::ifstream ifs{sequence_file};
        if (!ifs.is_open()) {
            std::println("{} is not open", sequence_file);
            return 1;
        }
        std::string line;
        std::getline(ifs, line);
        std::string sequence{};
        while (std::getline(ifs, line)) {
            sequence.append_range(line);
        }
        Checker checker {sequence};

        std::string query_file = std::format("/data/projects/bf/dna_queries/queries_from_sequence_{}.txt", i + 1);
        std::ifstream qfs {query_file};
        if (!qfs.is_open()) {
            std::println("{} is not open", query_file);
            return 1;
        }
        bool last_is_comment = false;
        while (std::getline(qfs, line)) {
            if (line.starts_with(">")) {
                last_is_comment = true;
            } else if (last_is_comment) {
                last_is_comment = false;
                std::println("{}", line);
                if (!checker.contains(line)) {
                    std::println("ERROR: {}", line);
                }
            }
        }
    }




}
