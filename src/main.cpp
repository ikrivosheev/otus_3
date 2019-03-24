#include <iostream>
#include <map>

#include "allocator.h"
#include "container.h"
#include "version.h"

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}


template<typename... Args>
void fill(std::map<Args...>& map, int count = 10) {
    for (int i = 0; i < count; ++i) {
        map[i] = factorial(i);        
    }
}

template<typename... Args>
void fill(List<Args...>& lst, int count = 10) {
    for(int i = 0; i < count; ++i) {
        lst.push_back(i);
    }
}

template<typename... Args>
std::ostream& operator << (std::ostream& out, const std::map<Args...>& map) {
    for (const auto& it: map) {
        out << it.first << "=" << it.second << std::endl;
    }
    return out;
}

template<typename... Args >
std::ostream& operator << (std::ostream& out, List<Args...> lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        out << *it << std::endl;
    }
    return out;
}


int main() {
    std::map<int, int> map;
    auto alloc1 = allocator<std::pair<const int, int>>();
    std::map<int, int, std::less<int>, decltype(alloc1)> new_map;
    auto alloc2 = allocator<int>();
    auto lst = List<int, decltype(alloc2)>();

    fill(map);
    std::cout << map << std::endl;

    fill(new_map);
    std::cout << new_map << std::endl;

    fill(lst);
    std::cout << lst << std::endl;
    return 0;
}
