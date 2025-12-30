#pragma once

#include <cstddef>
#include <string>

#include "bf.hpp"
#include "util.hpp"

template <int K = 10>
class Checker {
public:
    Checker() = delete;

    Checker(std::string const& string) : bf{string.size() - K, FALSE_RATE} {
        for (size_t i = 0; i < string.size() - K; i++) {
            bf.add(string.substr(i, K));
        }
    }

    [[nodiscard]] bool contains(std::string const& query) const noexcept {
        bool found = true;
        for (size_t i = 0; i < query.size(); i++) {
            if (!bf.possibly_contains(query.substr(i, K))) {
                found = false;
                break;
            }
        }
        return found;
    }

private:
    BloomFilter<std::string> bf;
};
