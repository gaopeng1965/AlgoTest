/******************************************************************************
 * Description : thread pool class definition
 * Author      : GaoPeng
 * Date        : 2020-6-2
 * modify      : 2021-3-12
 * version     : 1.0
 ******************************************************************************/
#ifndef ThreadPool_hpp
#define ThreadPool_hpp
#include <vector>               // std::vector
#include <queue>                // std::queue
#include <memory>               // std::make_shared
#include <stdexcept>            // std::runtime_error
#include <thread>               // std::thread
#include <mutex>                // std::mutex,        std::unique_lock
#include <condition_variable>   // std::condition_variable
#include <future>               // std::future,       std::packaged_task
#include <functional>           // std::function,     std::bind
#include <utility>              // std::move,         std::forward

class ThreadPool {
public:
    inline ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i)
            workers.emplace_back([this] {
                for (;;)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                                             [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }
    // c++11写法
    // -> std::future<typename std::result_of<F(Args...)>::type>
    // 14就不需要->指明返回类型,可以自动推断
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args){
        // typename的另一个作用:
        // 指明后续字段为类型名,而非成员函数/变量
        // 如果没有这个关键字,编译器无法知道其到底是什么
        using return_type = typename std::result_of<F(Args...)>::type;
        // 任务封装,把所有参数绑定到可调用对象,然后可以无参调用
        // return_type() 就是指明返回类型和无参
        // packaged_task其实是简化promise的使用
        // std::packaged_task类似于std::function,但是会自动将其结果传递给std::future对象.
        auto task = std::make_shared< std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task] { (*task)(); });
        }
        condition.notify_one();
        return res;
    }
    inline ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

#endif /* ThreadPool_hpp */

