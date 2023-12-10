#ifndef SWAN_QUEUE_H_
#define SWAN_QUEUE_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace swam {
    namespace concurrency {
        template <typename T>
        class threadsafe_queue {
           private:
            mutable std::mutex mut_;
            std::queue<T> data_queue_;
            std::condition_variable data_cond_;

           public:
            threadsafe_queue() = default;

            void push(T new_value) {
                std::lock_guard lock(mut_);
                data_queue_.push(std::move(new_value));
                data_cond_.notify_one();
            }

            void wait_and_pop(T& value) {
                std::unique_lock lock(mut_);
                data_cond_.wait(lock, [this] { return !data_queue_.empty(); });
                value = std::move(data_queue_.front());
                data_queue_.pop();
            }

            std::shared_ptr<T> wait_and_pop() {
                std::unique_lock lock(mut_);
                data_cond_.wait(lock, [this] { return !data_queue_.empty(); });
                std::shared_ptr res{std::make_shared<T>(std::move(data_queue_.front()))};
                data_queue_.pop();
                return res;
            }

            bool try_pop(T& value) {
                std::lock_guard lock(mut_);
                if (data_queue_.empty()) {
                    return false;
                }
                value = std::move(data_queue_.front());
                data_queue_.pop();
                return true;
            }

            std::shared_ptr<T> try_pop() {
                std::unique_lock lock(mut_);
                if (data_queue_.empty()) {
                    return std::shared_ptr<T>();
                }
                std::shared_ptr res{std::make_shared<T>(std::move(data_queue_.front()))};
                data_queue_.pop();
                return res;
            }

            bool empty() const {
                std::lock_guard lock(mut_);
                return data_queue_.empty();
            }
        };
    }  // namespace concurrency
}  // namespace swam

#endif  // SWAN_QUEUE_H_