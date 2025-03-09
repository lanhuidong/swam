#include <gtest/gtest.h>
#include <util/random_util.h>

#include <iostream>
#include <memory>

TEST(random_test, random_test) {
    swam::util::RandomUtil r{0, 100};
    for (int i = 0; i < 10; ++i) {
        std::cout << "random number: " << r() << std::endl;
    }
}
