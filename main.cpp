#include <cstddef>
#include <format>
#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "bf.hpp"
int main() {
    constexpr int BIN_COUNT = 10;
    constexpr int K = 10;
    std::vector<BloomFilter<std::string>> vec{};
    for (int i = 0; i < BIN_COUNT; i++) {

        std::string filename = std::format("/data/projects/bf/dna_sequences/dna_sequence_{}.txt", i + 1);
        std::ifstream ifs{filename};
        if (!ifs.is_open()) {
            std::println("{} is not open", filename);
            return 1;
        }
        std::string line;
        std::getline(ifs, line);
        std::string sequence{};
        while (std::getline(ifs, line)) {
            sequence.append_range(line);
            // std::println("{}", sequence);
        }
        BloomFilter<std::string> bf{sequence.size() - K, 0.05};
        for (size_t i = 0; i < sequence.size() - K; i++) {
            bf.add(sequence.substr(i, K));
        }
        vec.push_back(bf);
        vec.at(i).info();
    }



    // Test code
    for (int i = 0; i < BIN_COUNT; i++) {
        std::string filename = std::format("/data/projects/bf/dna_queries/queries_from_sequence_{}.txt", i+1);
        std::ifstream ifs {filename};

        if (!ifs.is_open()) {
            std::println("{} is not open", filename);
            return 1;
        }
        std::println("Testing for sequence {}", i + 1);
        std::string line;
        bool last_is_comment = false;
        while(std::getline(ifs, line)) {
            if (line.starts_with(">")) {
                last_is_comment = true;
                continue;
            }
            if (last_is_comment) {
                last_is_comment = false;
                // std::println("{}", line);
                std::vector<std::string> kmers;
                for (size_t k = 0; k < line.size() - K; k++) {
                    kmers.push_back(line.substr(k, K));
                }
                // std::println("{}", kmers);

                bool find = false;
                for (int j = 0; j < BIN_COUNT; j++) {

                    auto& bf = vec.at(j);


                    // std::println("{}", bf.sets);

                    for (auto& kmer : kmers) {
                        if (bf.possibly_contains(kmer)) {
                            find = true;
                        } else {
                            // std::println("{}", kmer);
                            find = false;
                            break;
                        }
                    }

                    if (i == j && find) {
                        std::println("nice");
                    } else if (i== j && !find){
                        std::println("false neg");
                    } else if (find && i !=j) {
                        std::println("false posi");
                    }



                }
            }
        }
    }

}
