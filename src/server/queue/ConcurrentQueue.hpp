#ifndef BABEL_CONCURRENTQUEUE_HPP
#define BABEL_CONCURRENTQUEUE_HPP

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

template<typename T>
class ConcurrentQueue {
    public:
        void push(T const &item) {
            boost::mutex::scoped_lock locker(this->mutex);
            queue.push(item);
            locker.unlock();
            std::cout << "bite" << std::endl;
            condition_variable.notify_one();
        }

        bool empty() const {
            boost::mutex::scoped_lock locker(this->mutex);
            return queue.empty();
        }

        T &waitAndPop() {
            boost::mutex::scoped_lock lock(this->mutex);
            while(queue.empty())
                condition_variable.wait(lock);
            auto &tes = queue.front();
            queue.pop();
            return tes;
        }
    private:
        std::queue<T> queue;
        mutable boost::mutex mutex;
        boost::condition_variable condition_variable;
};

#endif //BABEL_CONCURRENTQUEUE_HPP
