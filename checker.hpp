
#include <string>

#include "bf.hpp"
#include "util.hpp"

template <int K = 10>
class Checker {
public:
    Checker(std::string const& string) {
        bf = BloomFilter<std::string>{string.size() - K, FALSE_RATE};
        for (int i = 0; i < string.size() - K; i++) {
            bf.add(string.substr(i, K));
        }
    }
    
    [[nodiscard]] bool contains(std::string const& query) const noexcept {
        bool found;
        for (int i = 0; i < query.size(); i++) {
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
