#include <limits>
#include <deque>
#include <vector>

template<typename T, int step = 10>
class allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    template<typename U> struct rebind {
        using other = allocator<U>;
    };

    allocator() = default;
    ~allocator() {
    for (auto& block: blocks) {
        std::free(block);
        }
    }

    pointer allocate(size_type n) {
        while (pool.size() < n) {
            auto block = std::malloc(step * sizeof(T));
            if (!block) throw std::bad_alloc();
            blocks.push_back(block);
            auto buffer =  reinterpret_cast<pointer>(block);
            for (int i = 0; i < step; ++i) {
                pool.push_back(buffer);
                buffer++;
            }
        }
        pointer result = pool.front();
        for (int i = 0; i < n; ++i) {
            pool.pop_front();
        }
        return result;
    }

    void deallocate(pointer p, size_type n) {
        for (int i = 0; i < n; i++) {
            pool.push_front(p);
            p++;
        }
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

private:
    std::deque<pointer> pool;
    std::vector<void*> blocks;

};
