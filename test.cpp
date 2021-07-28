/*
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <chrono>
#include <algorithm>
#include <sys/syscall.h>
#include <condition_variable>
#include <future>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::thread;

//std::mutex mtx;
//std::condition_variable cv;
//bool ready = false;
#if 0
string DoTimeCostWork(int nId)
{
    std::this_thread::sleep_for(std::chrono::seconds(nId));
    return "www";
}

int main()
{
    std::future<std::string> fut = std::async(DoTimeCostWork, 3);

    // 每100毫秒轮询查看任务执行进度
    std::chrono::milliseconds tSpan(200);
    while (fut.wait_for(tSpan) != std::future_status::ready)
    {
        cout << "......" << endl;
    }
    cout << "exec complete:" << fut.get() << endl;

    return 0;
}
#endif

#if 0
void printId(int id){
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck,[]{return ready;});//[&]???
    cout<<"Thread : "<<id<<endl;
}

void go(){
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

void foo(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<std::this_thread::get_id()<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
void bar(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<std::this_thread::get_id()<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
int main(){
//    thread t[10];
//    for (int i = 0; i < 10; ++i) {
//        t[i] = thread(printId,i);
//    }
//    cout << "10 threads ready to race...\n";
//    go();
//
//    for (auto& i:t) {
//        i.join();
//    }

//    auto f =[]()->void{
//        if (ready)
//            cout<<"true\n";
//        else
//            cout<<"false\n";
//    };
//    f();
    cout<<getpid()<<endl;
    cout<<std::this_thread::get_id()<<endl;
    std::thread t1(foo);
    std::thread t2(bar);

    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;

    std::swap(t1, t2);

    std::cout << "after std::swap(t1, t2):" << std::endl;
    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;

    t1.swap(t2);

    std::cout << "after t1.swap(t2):" << std::endl;
    std::cout << "thread 1 id: " << t1.get_id() << std::endl;
    std::cout << "thread 2 id: " << t2.get_id() << std::endl;

    t1.join();
    t2.join();

    return 0;
}
#endif
#if 0
template<typename T>
void print(T& t){
    cout << "lvalue" << endl;
}
template<typename T>
void print(T&& t){
    cout << "rvalue" << endl;
}

template<typename T>
void TestForward(T && v){
    print(v);
    print(std::forward<T>(v));
    print(std::move(v));
}

int main(){
    TestForward(1);
    int x = 1;
    TestForward(x);
    TestForward(std::forward<int>(x));
    return 0;
}
#endif
#if 0
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
io_service io;
tcp::resolver resolv(io);
tcp::socket tcp_socket(io);
std::array<char, 4096> bytes;

void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout.write(bytes.data(), bytes_transferred);
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}

void connect_handler(const boost::system::error_code &ec)
{
    if (!ec)
    {
        std::string r =
                "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
        write(tcp_socket, buffer(r));
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}
//void print(const boost::system::error_code&){
//    cout<<"hhhhhhhh"<<endl;
//}

void resolve_handler(const boost::system::error_code &ec, tcp::resolver::iterator it)
{
    if (!ec)
        tcp_socket.async_connect(*it, connect_handler);
}
int main_1()
{
//    steady_timer t1(io, std::chrono::seconds(2));
//    t1.async_wait([](const boost::system::error_code &e){
//        cout<<"2 sec\n";
//    });
//    steady_timer t2(io, std::chrono::seconds(2));
//    t2.async_wait([](const boost::system::error_code &e){
//        cout<<"2 sec\n";
//    });
//
//    thread thread1([&io]{io.run();});
//    thread thread2([&io]{io.run();});
//    thread1.join();
//    thread2.join();

    tcp::resolver::query q("theboostcpplibraries.com","80");
    resolv.async_resolve(q,resolve_handler);
    io.run();
    return 0;
}
#endif

#include "FooBar.h"

#if 0
int main(){
    FooBar f(2);
    FooBar f2(3);
//    thread t1 = f.createThread1();
//    thread t2 = f.createThread2();
    thread t1 = thread(&FooBar::foo,&f2,[]{
        cout<<"foo";
    });
    thread t2 = thread(&FooBar::bar,&f2,[]{
        cout<<"bar";
    });
    t1.join();
    t2.join();

    return 0;
}
#endif

//#include <algorithm>
//class Solution {
//public:
//    void getLeastNumbers(vector<int>& arr, int k) {
//        if (arr.size()==0){
//            cout<<"vector are null"<<endl;
//        }else if(arr.size()<=k){
//            return;
//        } else{
//            std::sort(arr.begin(),arr.end());
//            arr.erase(arr.begin()+k,arr.end());
//        }
//    }
//};
#if 0
int main(){
//    vector<int> arr{3,2,1};
//    Solution s;
//    s.getLeastNumbers(arr,2);
//    std::for_each(arr.begin(),arr.end(),[](int x){
//        cout<<x<<" ";
//    });

    using namespace pugi;
    xml_document doc;
    if (!doc.load_file("/root/ShareDir/DRM/test/gen1.xml")) return -1;
//    string l2d = doc.child("task")
    string node = doc.child("task").child("inputlist").child("input").attribute("description").value();
    cout<<node<<endl;

    xml_node input_node = doc.child("task").child("inputlist").child("input");
    for (; input_node; input_node = input_node.next_sibling()) {
        cout<<input_node.attribute("description").value()<<endl;
    }

//    xml_node tools = doc.child("Profile").child("Tools");
//
//    //[code_traverse_base_basic
//    for (xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
//    {
//        std::cout << "Tool:";
//
//        for (xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
//        {
//            string tmp1 = attr.name();
//            string tmp2 = attr.value();
//            std::cout << " " << tmp1 << "=" << tmp2;
//        }
//
//        std::cout << std::endl;
//    }


//    using namespace pugi;
//    xml_document doc;
//    xml_parse_result result = doc.load_file("/root/ShareDir/DRM/smr/smr3.5/xml/tree.xml");//parse解析，无错误则返回1
//    cout << result.description() << endl;//也可以把1描述出来，No error
//    if (!result) return -1; //推荐直接写 if (!doc.load_file("tree.xml")) return -1;
//
//    cout << doc.child("mesh").attribute("name").value() << endl; //节点mesh的属性name的值
//    cout << doc.first_child().child_value() << endl;
//    cout << doc.child("mesh").child("node").attribute("attr1").value() << endl; //节点mesh的节点node的属性attr1的值
//    return 0;
//
//    doc.print(cout); //展示文档内容
}
#endif

#include <boost/filesystem.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <sstream>
//int main_0(){
//    using namespace boost::filesystem;
//    using namespace boost::xpressive;
////    string s = "/root/ShareDir/DRM/smr/smr3.5/L2D/H2B_OPER_SMR_L2D_SG_20200305T155827_20200305T165140_036_0079_01.h5";
////    path p(s);
////    cout<<p.filename()<<endl;
//    string tmp = "/root/ShareDir/DRM/smr/smr3.5/L2D/H2B_OPER_SMR_L2D_SG_20200305T155827_20200305T165140_036_0079_01.h5";
//    string s = path(tmp).filename().string();
//    sregex reg = sregex::compile("_(\\d{8})T\\d{0,6}_(\\d{8})T\\d*");
//    smatch what;
//    if(regex_search(s,what,reg)){
//        string time1 = what[1];
//        string time2 = what[2];
//        if(time1 == time2)
//            cout<<time1<<"="<<time2<<endl;
//        else
//            cout<<time1<<" "<<time2<<endl;
//    } else
//        cout<<"not match."<<endl;
//}

string TupperLower(const string &strName, bool bLower)
{
    string strResult;
    if (bLower)
    {
        std::transform(strName.begin(), strName.end(), back_inserter(strResult), ::tolower);
    }
    else
    {
        std::transform(strName.begin(), strName.end(), back_inserter(strResult), ::toupper);
    }
    return	strResult;
}

int main_s(){
#if 0
    using std::stringstream;

    string s = "  This is life!   ";

    auto t1 = std::chrono::high_resolution_clock::now();
    string tmp,ans;
    stringstream ss(s);

    while(ss>>tmp){
        ans=" "+tmp+ans;
    }
    if(ans!="")
        ans.erase(ans.begin());

    auto t2 = std::chrono::high_resolution_clock::now();

//    整型结果
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
    std::chrono::duration<double,std::milli> duration = t2-t1;
    cout<<ans<<endl;
    cout<<duration.count()<<" ms"<<endl;

    string ddd = "This is an example";
    ddd.erase(ddd.find(' '));
    cout<<ddd<<endl;
#endif
//    using std::shared_ptr;
//    using std::make_shared;
//
//    auto a = make_shared<FooBar>(5);

}








*/







