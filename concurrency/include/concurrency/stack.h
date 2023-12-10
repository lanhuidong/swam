#ifndef SWAN_STACK_H_
#define SWAN_STACK_H_

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

namespace swam {
    namespace concurrency {
        struct empty_stack : std::exception {
            const char* what() const throw();
        };
        template <typename T>
        class threadsafe_stack {
           private:
            std::stack<T> data;
            mutable std::mutex m;

           public:
            threadsafe_stack() = default;

            threadsafe_stack(const threadsafe_stack& other) {
                std::lock_guard lock(other.m);
                data = other.data;
            }

            threadsafe_stack& operator=(const threadsafe_stack&) = delete;

            void push(T new_value) {
                std::lock_guard lock(m);
                data.push(std::move(new_value));
            }

            std::shared_ptr<T> pop() {
                std::lock_guard lock(m);
                if (data.empty()) {
                    throw empty_stack();
                }
                std::shared_ptr<t> const res{std::make_shared<T>(std::move(data.top()))};
                data.pop();
                return res;
            }

            void pop(T& value) {
                std::lock_guard lock(m);
                if (data.empty()) {
                    throw empty_stack();
                }
                value = std::move(data.top());
                data.pop();
            }

            bool empty() const {
                std::lock_guard lock(m);
                return data.empty();
            }
        };
    }  // namespace concurrency
}  // namespace swam

#endif  // SWAN_STACK_H_