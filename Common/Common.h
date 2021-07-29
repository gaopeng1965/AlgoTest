/******************************************************************************
 * Description : common headers and types
 * Author      : gaopeng
 * Date        : 2020-7-15
 * modify      : 2021-6-2
 * version     : 1.0
 ******************************************************************************/
#ifndef ASYC_COMMON_H
#define ASYC_COMMON_H

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/date_time/gregorian/gregorian.hpp>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <random>
#include <cstdlib>
//#include <limits>
/* 容器 */
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <stack>
/* 异步 */
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>
//#include <shared_mutex>
#include <regex>
#include <algorithm>
#include <functional>
#include <semaphore.h>
#include <dirent.h>
#include <sys/stat.h>
//#include <armadillo>
//
//using namespace arma;

#define GP_DEBUG_DEFINE

#ifdef GP_DEBUG_DEFINE
#define gpDebug(a) std::cout << a << std::endl
#else
#define gpDebug(a)
#endif

typedef unsigned int uint;
typedef unsigned long long ull;

using std::to_string;
using std::unordered_set;
using std::unordered_map;
using std::set;
using std::array;
using std::pair;
using std::priority_queue;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::function;
using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::bitset;

typedef vector<std::pair<string, string>> FileList;
namespace bfs = boost::filesystem;

//简单二叉树
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    bool operator==(TreeNode* node){
        return this->val == node->val;
    }
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//简单链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Common {
public:
    string getTime();
    static void listDir(vector<string>& file_list,string path);
    static void listDir(vector<string>& file_list,char *path);

    void txt2xml();
    void getMessages(const string& file);
    void middleFilter(vector<vector<double>>&);
    // 根据年和当年第x日，得到日期字符串
    string getDateStr(int year,int allDay);
    // 读取fortran生成的二进制文件
    void getDataFromF90Bin(const char* fileName);
    // 1900年至某个时刻的小时数转为格式化字符串,例如:2021041200
    string hour2dateStr(long allHours);

    static Common* instance(){
        static Common com;
        return &com;
    }
    // 随机数生成
    template <typename T>
    static T getRandom(T t1,T t2){
        std::random_device rd;
        // std::mt19937_64 64位的数据
        std::mt19937 gen(rd());
        // 指定随机范围
        // 整数
        // std::uniform_int_distribution<> u(0, 100);
        // std::cout<<u(gen) << endl;
        // 浮点数
        // std::uniform_real_distribution<> f(t1, t2);
        if(typeid(T).name() == typeid(float).name() || typeid(T).name() == typeid(double).name())
            return std::uniform_real_distribution<>(t1, t2)(gen);
        else
            return std::uniform_int_distribution<>(t1, t2)(gen);
    }

    /*
     * @param  源数组nums,左右边界,调用就是 0 和 len - 1
     * @return void,数据原地修改
     * @desc   快速排序
     */
    template <typename T>
    static void quickSort(vector<T>& nums,int left,int right){
        if(left >= right)
            return;
        auto randIndex = getRandom(left,right);
        // 切记 std::swap 参数不是指针/迭代器
        std::swap(nums[left],nums[randIndex]);
        auto base = nums[left];
        int i = left, j = right;
        while(i < j){
            while(i < j && nums[j] >= base)
                --j;
            if(i < j)
                nums[i] = nums[j];
            while(i < j && nums[i] <= base)
                ++i;
            if(i < j)
                nums[j] = nums[i];
        }
        nums[i] = base;

        quickSort(nums,left,i - 1);
        quickSort(nums,i + 1,right);
    };
    /*
     * @param
     * @return string
     * @desc   获取格式化系统时间
     */
    static string GetSysTime()
    {
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        struct tm* ptm = localtime(&t);
        char date[60] = { 0 };
        sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
                (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
                (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
        return string(date);
    }
};

// 如果返回值和参数有关,C++11必须要decltype查询指明返回类型
// c++14可以自动推断，多种输入类型计算的返回结果也可以
template <typename T1,typename T2>
auto testFunc(T1 a,T2 b)->decltype(a + b){
    return a + b;
}
#endif //ASYC_COMMON_H
