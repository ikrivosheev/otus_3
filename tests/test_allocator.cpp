#include <gtest/gtest.h>

#include "allocator.h"

TEST(Allocator, allocate_deallocate) {
    allocator<int> alloc = allocator<int>();
    auto p = alloc.allocate(4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

