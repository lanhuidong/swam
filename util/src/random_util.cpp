#include <util/random_util.h>

#include <ctime>
#include <iostream>
#include <random>

namespace swam::util {
    RandomUtil::RandomUtil(int min, int max) {
        std::random_device seeder;
        const auto seed{seeder.entropy() ? seeder() : time(nullptr)};
        std::mt19937 engine{std::random_device{}()};
        std::uniform_int_distribution distribution{min, max};
        g_ = std::bind(distribution, engine);
    }
}  // namespace swam::util