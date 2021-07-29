/******************************************************************************
 * Description : main func
 * Author      : Gao Peng
 * Date        : 2020-6-2
 * modify      : 2021-7-14
 * version     : 1.0
 ******************************************************************************/
#include "Solution.h"
#include "BinaryTree.h"
#include "ClassSet.hpp"
#include "ThreadPool.hpp"

#include <functional>
#include <sys/time.h>
//#include "nlohmann_json.hpp"

void getSum(){
    auto calSum = [](vector<float>& x){
        float sum = 0.0;
        std::for_each(x.begin(),x.end(),[&sum](const float& a){
            if(a >= 2000)
                sum += a;
        });
        return sum;
    };
    vector<float> v1 = {11380.92,102.74,11380.91,1647.0,10942.41,1207.00,1500.0,
                    33734.57,11380.90,1500.00,76.35,11380.90,10912.76,500.00,10912.76,105.00,
                    56.94,11226.14,10632.51,18.00,10912.76,302.00,45.94,11564.25,10912.76,9102.26};
    vector<float> v2 = {40.25,9753.49,9102.26,16156.15,9223.61,35.43,9102.26,10.00,9102.26,500.00};
//    float sum1 = std::accumulate(v1.begin(),v1.end(),0.0);
//    float sum2 = std::accumulate(v2.begin(),v2.end(),0.0);
    auto sum1 = calSum(v1);
    auto sum2 = calSum(v2);
    printf("%.2f\n",sum1);
    printf("%.2f\n",sum2);
    printf("%.2f\n",sum1 + sum2);
}

ulong getHours(long inpurYear) {
    string dateStr;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::for_each(month, month + 12, [](int &x) {
        x *= 24;
    });
    uint months = 1, days = 1, hours = 0;
    constexpr uint leapYearHours = 24 * 366;
    // 基准时间 1900年1月1日0点
    uint year = 1900;
    ulong allHours = 0;
    for (; year < 1970; ++year) {
        int yearHours;
        if (year > 0 && !(year % 4) && (year % 100 || !(year % 400)))
            yearHours = leapYearHours;
        else
            yearHours = leapYearHours - 24;
        allHours += yearHours;
    }
    return allHours;
}

std::mutex mtx;

int main() {
#if 0 //boost::filesystem   test.
    using  namespace boost::filesystem;
//    path p("/root/ShareDir/a.txt");
    path p = current_path();
//    cout << p.string() <<endl;
//    cout << p.root_direcstory().string() <<endl;
//
//    cout << p.root_name() << endl;
//    cout << p.root_directory() << endl;
//    cout << p.root_path() << endl;
//    cout << p.relative_path() << endl;
//    cout << p.parent_path() << endl;
//    cout << p.filename() << endl;

//has_root_name(), has_root_directory(), has_root_path(), has_relative_path(),
//has_parent_path() 和 has_filename()。 各个方法都是返回一个 bool 类型的值

//    if(is_directory(p)){
//        p /= "test.txt";
//    } else{
//        if(p.has_filename()){
//            cout<< p.stem() <<endl;//"a"
//            cout<< p.filename() <<endl;//"a.txt"
//            cout<< p.extension() <<endl;//".txt"
//        }
//    }
    //迭代器,并不是迭代目录,只是操作字符串
//    for (auto &t :p) { //const boost::filesystem::path &
//        cout<<t<<endl;
//    }
//    for (path::iterator it = p.begin(); it != p.end() ; ++it) { //boost::filesystem::path::iterator
//        cout<<*it<<endl;
//    }

    vector<string> file_list;
//    listDir(file_list,dir);
    Common::listDir(file_list,p.string());
    cout << "-------------" << endl;
    for(auto &t:file_list)
        cout << t << endl;
//    path op("/home/gp/tmp/cuda笔记.cpp");
//    boost::filesystem::ofstream ofs(op,std::ios::app);
//    if(ofs.is_open()){
//        cout << "cpp is open.";
//        ofs << "hhhahahahahh\n5655" << endl;
//    }
//    ofs.close();
#endif

#if 0 //matlab重复测试
    //    DIR *df = opendir("/root/ShareDir/source") ;
    //    struct dirent *filename;
    //
    //    if (df != NULL) {
    //        while ((filename = readdir(df)) != NULL) {
    //            cout << filename->d_name << endl;
    //        }
    //    }

    //    array<float,6> gmi_time = {2020,1,1,8,0,0};
    //    array<float,6> time_2016 = {2016,1,1,0,0,0};
    //    double tmp = Date2ri(gmi_time)*24*3600 - Date2ri(time_2016)*24*3600 - 126257095.935250;
    //    printf("%.8lf\n",tmp);
    //
    //    int iret = 0;
    //    time_t gmi_cxx,hy2_cxx;
    //    time_t temp_scantime = static_cast<time_t>(126257095.935250);
    //    iret = formatHy2Time(temp_scantime,"20160101000000",hy2_cxx);
    //    iret = formatTimeFrom1970(8*3600,"20200101000000",gmi_cxx);
    //    time_t abs_time = gmi_cxx - hy2_cxx;
    //    printf("%ld - %ld = %ld\n",gmi_cxx,hy2_cxx,abs_time);

    //    array<double,4> a = {-31.5151000000000,-15.1764000000000, -31.6250000000000,-15.3750000000000};
    //    double result = LatLon2Distance(a[0],a[1],a[2],a[3]);
    //    printf("%lf\n",result);


    //    using namespace boost::xpressive;
    //
    //    auto num2str = [](int x){
    //        std::stringstream ss;
    //        ss << x;
    //        return ss.str();
    //    };
    //    std::array<int,28> no_repeat_num;
    //    size_t allcount = 0;
    //    for (int i = 1; i < 29; ++i) {
    //
    //        std::set<string> no_repeat;
    //        std::stringstream all_row_ss ;
    //        string all_row;
    //
    //        std::ifstream f_read("/root/ShareDir/index/rc_" + num2str(i) + ".txt");
    //        if(f_read.is_open()){
    //            string s_row;
    //            while (f_read >> s_row){
    //                no_repeat.emplace(s_row);
    //                allcount ++;
    //            }
    //        }
    //        f_read.close();
    //        all_row_ss.clear();
    //        cout << "/root/ShareDir/DRM/20200101/index/rc/rc_" + num2str(i) + ".txt matlab不重复匹配点数:" << no_repeat.size();
    //        cout << endl;
    //        no_repeat_num[i-1] = no_repeat.size();
    //    }
    //
    //    size_t count = 0;
    //    for (auto &t:no_repeat_num) {
    //        count += t;
    //    }
    //    cout<< "总匹配点数:" << allcount << endl;
    //    cout<< "不重复总匹配点数:" << count << endl;
    //    cout<< "重复点数:" << allcount - count << endl;
#endif

#if 0 //元素找min,max
    //    srand((unsigned)time(NULL));
    //    vector<int> vec_str;
    //    for (int i = 0; i < 10; ++i) {
    //        int a = rand()%100;
    //        cout << a << endl;
    //        vec_str.push_back(a);
    //    }
    //    cout << endl;
    //    int min = *std::min_element(vec_str.begin(),vec_str.end());
    //    int max = *std::max_element(vec_str.begin(),vec_str.end());
    //    cout << min << "," << max << endl;

    //    std::mt19937_64 gen(43);
    //    char buf[64];
    //    snprintf(buf, sizeof buf, "%016lx", gen());

    //    std::ifstream ifs;
    //    string s;
    //    double tmp = 1.0;
    //    std::stringstream ss;
    //    size_t count;
    //
    //    ifs.open("/root/ShareDir/data.txt",std::ios::in);
    //    if(ifs.is_open()){
    //        while (getline(ifs,s)){
    //            ss << s;
    //            ss >> tmp;
    //            cout << tmp << endl;
    //            count++;
    //            ss.clear();
    //        }
    //
    //        ifs.clear();
    //        ifs.seekg(0,std::ios::beg);
    //        while (getline(ifs,s)){
    //            cout << s << endl;
    //        }
    //        ifs.close();
    //    }else{
    //        cout << "open file defeat." << endl;
    //    }
#endif

//    Solution **s = new Solution*[5];
//    s[0] = new Solution();

//    vector<vector<int>> grid = {{1,3},{3,0,1},{2},{}};
    vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                  {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                  {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                  {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                  {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                  {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                  {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                  {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                  {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    vector<string> words = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    vector<string> puzzles = {"aboveyz", "abrodyz", "abslute", "absoryz", "actresz", "gaswxyz"};
//    vector<int> nums{1,6,9,6,3,5,5,2,10,22,14,12,4,7};
    vector<int> nums{1,4,8,13};

    vector<vector<char>> board1 = {{'A', 'B', 'C', 'E'},
                                   {'S', 'F', 'C', 'S'},
                                   {'A', 'D', 'E', 'E'}};
    try {
        shared_ptr<Solution> sol = make_shared<Solution>();
        auto begin = std::chrono::high_resolution_clock::now();
//        auto result = sol->maxFrequency(nums,5);
        auto result = BinaryTree::pathInZigZagTree(14);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        cout << "time duration:" << elapsedTime.count() / 1000.0 << "ms" << endl;
//        string beginTime = std::to_string(
//                std::chrono::duration_cast<std::chrono::nanoseconds>(begin.time_since_epoch()).count());
//        cout << result << endl;
        std::for_each(result.begin(),result.end(),[](const int& x){
            gpDebug(x);
        });
    } catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
    gpDebug("---------------------");
//    string word = "apple",prefix = "app";
//    Trie* obj = new Trie();
//    obj->insert(word);
//    bool param_2 = obj->search(word);
//    bool param_1 = obj->search(prefix);
//    bool param_3 = obj->startsWith(prefix);


//    getSum();


    gpDebug("---------------------");
}








