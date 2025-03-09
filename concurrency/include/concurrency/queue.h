#ifndef SWAN_QUEUE_H_
#define SWAN_QUEUE_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace swam {
    namespace concurrency {
        template <typename T>
        class queue {
           private:
            class node {
                T data_;
                std::unique_ptr<node> next;
                node(T data) : data_{std::move(data)} {}
            };
            std::unique_ptr<node> head_;
            node* tail_;

           public:
            queue() : tail_(nullptr) {}
            queue(const queue& other) = delete;
            queue& operator=(const queue& other) = delete;

            std::shared_ptr<T> try_pop() {
                if (!head_) {
                    return std::shared_ptr<T>();
                }
                std::shared_ptr<T> const res(std::make_shared<T>(std::move(head_->data_)));
                std::unique_ptr<node> const old_head = std::move(head_);
                head_ = std::move(old_head->next);
                if (!head_) {
                    tail_ = nullptr;
                }
                return res;
            }

            void push(T new_value) {
                std::unique_ptr<node> p{new node(std::move(new_value))};
                node* const new_tail = p.get();
                if (tail_) {
                    tail_->next = std::move(p);
                } else {
                    head_ = std::move(p);
                }
                tail_ = new_tail;
            }
        };
    }  // namespace concurrency
}  // namespace swam

#endif  // SWAN_QUEUE_H_