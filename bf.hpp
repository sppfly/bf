#include <cmath>
#include <cstddef>
#include <functional>
#include <print>
#include <vector>

template <typename T, typename Hasher = std::hash<T>>
class BloomFilter {

public:
    BloomFilter() = delete;
    
    [[nodiscard]] BloomFilter(size_t expected_items, double false_positive_prob) :
        n(expected_items),
        p(false_positive_prob),
        _size(0) {
        m = optimal_m(n, p); // number of bits
        k = optimal_k(n, m); // number of hash functions
        bits.resize(m);
    }

    void add(T const& value) {
        auto [h1, h2] = hash_pair(value);
        for (size_t i = 0; i < k; ++i) {
            bits[(h1 + i * h2) % m] = true;
        }
        ++_size;
    }

    void clear() {
        std::fill(bits.begin(), bits.end(), false);
        _size = 0;
    }

    [[nodiscard]] bool possibly_contains(T const& value) const {
        auto [h1, h2] = hash_pair(value);
        for (size_t i = 0; i < k; ++i) {
            if (!bits[(h1 + i * h2) % m]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] size_t bit_size() const noexcept {
        return m;
    }

    [[nodiscard]] size_t size() const noexcept {
        return _size;
    }

    [[nodiscard]] size_t hash_count() const noexcept {
        return k;
    }

    [[nodiscard]] double false_positive_rate() const noexcept {
        return std::pow(1 - std::exp(-double(k) * n / m), k);
    }

    void info() const noexcept {
        std::println("size: {}", _size);
        std::println("bit_size: {}", m);
        std::println("hash_count: {}", k);
        std::println("false_positive_rate: {}", false_positive_rate());
    }

private:
    size_t n; // expected elements
    double p; // false positive rate
    size_t m; // number of bits
    size_t k; // hash count

    size_t _size;

    std::vector<bool> bits;

    static size_t optimal_m(size_t n, double p) {
        return static_cast<size_t>(std::ceil(-(double)n * std::log(p) / (std::log(2) * std::log(2))));
    }

    static size_t optimal_k(size_t n, size_t m) {
        return std::max<size_t>(1, std::round(double(m) / n * std::log(2)));
    }

    std::pair<size_t, size_t> hash_pair(T const& value) const {
        Hasher h{};
        size_t h1 = h(value);
        size_t h2 = std::rotl(h1, 17) ^ 0x9e'37'79'b9'7f'4a'7c'15ULL;
        return {h1, h2 | 1}; // ensure h2 is odd
    }
};
