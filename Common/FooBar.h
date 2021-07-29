/******************************************************************************
 * Description : multithreading practice
 * Author      : Gao Peng
 * Date        : 2020-1-15
 * modify      : 2021-3-12
 * version     : 1.0
 ******************************************************************************/
#ifndef ASYC_FOOBAR_H
#define ASYC_FOOBAR_H

#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

const int x = 5;
class FooBar {
private:
    int n;
    int status = 1;
    std::mutex mtx;
    std::condition_variable cv;
public:

    FooBar(int n) {
        this->n = n;
    }

    void foo(std::function<void()> printFoo) {

        for (int i = 0; i < n; i++) {

            // printFoo() outputs "foo". Do not change or remove this line.
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck,[this]{return status == 1;});
            printFoo();
            status = 2;
            lck.unlock();
            cv.notify_one();
        }
    }

    void bar(std::function<void()> printBar) {

        for (int i = 0; i < n; i++) {

            // printBar() outputs "bar". Do not change or remove this line.
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck,[this]{return status == 2;});
            printBar();
            status = 1;
            lck.unlock();
            cv.notify_one();
        }
    }
//    std::thread createThread1(){
//        return std::thread(&FooBar::foo,this,[]{
//            std::cout<<"foo";
//        });
//    }
//    std::thread createThread2(){
//        return std::thread(&FooBar::bar,this,[]{
//            std::cout<<"bar";
//        });
//    }
};
//void printFoo(){
//    std::cout << "Foo";
//};
//void printBar(){
//    std::cout << "Bar";
//};

#endif //ASYC_FOOBAR_H
