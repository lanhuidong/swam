#ifndef SWAN_RANDOM_UTIL_H_
#define SWAN_RANDOM_UTIL_H_

#include <functional>

namespace swam::util {
    class RandomUtil {
       public:
        RandomUtil(int min, int max);

        int operator()() {
            return g_();
        }

       private:
        using Generator = std::function<int()>;
        Generator g_;
    };
}  // namespace swam::util

#endif