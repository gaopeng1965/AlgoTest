/******************************************************************************
 * Author      : Gao Peng
 * CreateDate  : 2021/7/2 14:03
 * Modify      : 2021/7/2
 * Version     : 1.0
 * Description : 多线程练习集合
 ******************************************************************************/
#ifndef ASYC_CLASSSET_H
#define ASYC_CLASSSET_H

#include "Common.h"
/*
 * @author gp
 * @date   2021/7/9
 * @desc   "01020304" 多线程正确打印
 */
class ZeroEvenOdd {
private:
    int n;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    unsigned char m_status;
//    int count;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        m_status = 1;
//        count = 0;
    }
    /*
     * @param  func
     * @return
     * @desc   间隔打印0
     */
    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        int count = 0;
        while(count < n){
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait(lck,[this](){
                return (m_status & 5) != 0;
            });
            printNumber(0);
            m_status = m_status == 1 ? 8 : m_status >> 1;
            m_cv.notify_all();
            ++count;
        }
    }
    /*
     * @param  func
     * @return
     * @desc   间隔打印偶数。
     * @notes  特别要注意边界,要避免线程条件变量不满足一直阻塞。
     */
    void even(function<void(int)> printNumber) {
        int count = 2;
        while(count <= n){
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait(lck,[this](){
                return m_status == 2;
            });
            printNumber(count);
            m_status = 1;
            m_cv.notify_all();
            count += 2;
        }
    }
    /*
     * @param  func
     * @return
     * @desc   间隔打印奇数。
     * @notes  同上。
     */
    void odd(function<void(int)> printNumber) {
        int count = 1;
        while(count <= n){
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait(lck,[this](){
                return m_status == 8;
            });
            printNumber(count);
            m_status = 4;
            m_cv.notify_all();
            count += 2;
        }
    }
};

/*
 * @author gp
 * @date   2021/7/9
 * @desc   前缀树
 */
class Trie{
private:
    bool m_isWord = false;
    vector<Trie*> m_trie;
public:
    Trie(){
        // 只含小写字母
        // ascii码是128个
        m_trie.resize(26, nullptr);
    }
    void insert(string word){
        Trie* node = this;
        for (int i = 0; i < word.size(); ++i) {
            auto idx = word[i] - 'a';
            if(!node->m_trie[idx]){
                node->m_trie[idx] = new Trie();
            }
            node = node->m_trie[idx];
        }
        node->m_isWord = true;
    }
    bool search(string word){
        Trie* node = this;
        for (int i = 0; i < word.size(); ++i) {
            auto idx = word[i] - 'a';
            if(!node->m_trie[idx])
                return false;
            else
                node = node->m_trie[idx];
        }
        return node->m_isWord;
    }
    bool startsWith(string prefix){
        Trie* node = this;
        for (int i = 0; i < prefix.size(); ++i) {
            auto idx = prefix[i] - 'a';
            if(!node->m_trie[idx])
                return false;
            else
                node = node->m_trie[idx];
        }
        return true;
    }
};
#endif //ASYC_CLASSSET_H
