#include <iostream>
#include <map>

#include "allocator.h"
#include "version.h"

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}


template<int count = 10, typename... Args>
void fill(std::map<Args...>& map) {
    for (int i = 0; i < count; ++i) {
        map[i] = factorial(i);        
    }
}

template<typename... Args>
std::ostream& operator << (std::ostream& out, const std::map<Args...>& map) {
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        out << it->first << "=" << it->second << std::endl;
    }
    return out;
}


int main() {
    std::map<int, int> map;
    auto alloc = allocator<std::pair<const int, int>>();
    std::map<int, int, std::less<int>, decltype(alloc)> new_map;

    fill(map);
    std::cout << map << std::endl;

    fill(new_map);
    std::cout << new_map << std::endl;

    return 0;
}
