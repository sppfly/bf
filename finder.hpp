#include <string_view>
class Finder {

public:

    Finder();

    void add(std::string_view element);
    
    int find(std::string_view query);
    
    [[nodiscard]] int size() const noexcept; 
    
private:
};
