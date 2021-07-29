/******************************************************************************
 * Description : common headers and types definition
 * Author      : Gao Peng
 * Date        : 2020-7-15
 * modify      : 2021-4-14
 * version     : 1.0
 ******************************************************************************/
#include "Common.h"

// 1900年至某个时刻的小时数转为格式化字符串,例如:2021041200
string Common::hour2dateStr(long allHours) {
    string dateStr;
    int month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    std::for_each(month,month + 12,[](int &x){
        x *= 24;
    });
    uint months = 1,days = 1,hours = 0;
    constexpr uint leapYearHours = 24 * 366;
    // 基准时间 1900年1月1日0点
    uint year = 1900;
    while (allHours > 0){
        int yearHours;
        if (year > 0 && !(year % 4) && (year % 100 || !(year % 400)))
            yearHours = leapYearHours;
        else
            yearHours = leapYearHours - 24;
        long tmp1 = allHours - yearHours;
        if(tmp1 >= 0){
            ++year;
            allHours = tmp1;
        }else{
            for(int i = 0;i < 12; ++i){
                if(allHours >= month[i]){
                    allHours -= month[i];
                    ++months;
                }else{
                    if(yearHours == leapYearHours)
                        month[1] = 29 * 24;
                    for (int j = 0; j < 31; ++j) {
                        int tmp2 = allHours - 24;
                        if(tmp2 >= 0){
                            allHours = tmp2;
                            ++days;
                        }else{
                            hours = allHours;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    auto date2Str = [](uint x){
        string s = to_string(x);
        if(s.size() < 2)
            s = '0' + s;
        return s;
    };
    return to_string(year) + date2Str(months) + date2Str(days) + date2Str(hours);
}

void middleFilter(vector<vector<double>>& src_data){
    auto src(src_data);
    for (int i = 1; i < src.size()-1; ++i) {
        for (int j = 1; j < src[i].size()-1; ++j) {
            double window[9];
            int col = j-1;
            for (int k = 0; k < 3; ++k,++col) {
                window[k]   = src[i-1][col];
                window[k+3] = src[i][col];
                window[k+6] = src[i+1][col];
            }
            std::sort(window,window+9);
            src_data[i][j] = window[4];
        }
    }
}
// 高分三信息提取
void getMessages(const string& file){
    std::stringstream ss;
    std::ifstream ifs;
    ifs.open(file,std::ios::in);
    string all_data;
    if(ifs.is_open()){
        string line_str;
        while(getline(ifs,line_str)){
            ss << line_str;
            string s;
            vector<string> vec;
            while(ss >> s){
                vec.emplace_back(s);
            }
            ss.clear();
            if(vec.size() == 6){
                string tmp;
                vec.erase(vec.begin()+1,vec.begin()+3);
                for (int i = 0; i < vec.size(); ++i)
                    tmp += (string(8-vec[i].size(),' ') + vec[i]);
                all_data += (tmp + '\n');
//                    for(auto& t:vec)
//                        tmp += t + " ";
//                    all_data += (string(tmp.begin(),tmp.end()-1) + '\n');
            } else
                all_data += ("数据不全,原来的行信息:" + line_str);
        }
        ifs.close();
        ifs.clear();
        cout << "done." << endl;
    } else
        cout << "open file err." << endl;
    std::ofstream ofs;
    ofs.open(file,std::ios::out);
    if(ofs.is_open()){
        ofs << all_data;
        ofs.close();
    }
};

string Common::getTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char now_time[16];
    /*
     * 注意前面的0不能省略
     */
    snprintf(now_time, 16, "%4d%02d%02d%02d%02d%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon,
             ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    return now_time;
};

void Common::listDir(vector<string>& file_list,char *path) {
    DIR *pDir;
    struct dirent *ent;
    int i = 0;
    char childpath[512];
    pDir = opendir(path);
    memset(childpath, 0, sizeof(childpath));
    while ((ent = readdir(pDir)) != NULL) {
        if (ent->d_type & DT_DIR) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            sprintf(childpath, "%s/%s", path, ent->d_name);
            printf("path:%s/n", childpath);
            listDir(file_list,childpath);
        } else {
            sprintf(childpath, "%s/%s", path, ent->d_name);
            file_list.emplace_back(childpath);
            cout << ent->d_name << endl;
        }
    }
}

void Common::listDir(vector<string>& file_list,string path){
    DIR *pDir;
    struct dirent *ent;
    string file_path;
    pDir = opendir(path.c_str());
    while ((ent = readdir(pDir)) != NULL) {
        file_path = path + '/' + ent->d_name;
        if (ent->d_type & DT_DIR) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            listDir(file_list, file_path);
        } else
            file_list.emplace_back(file_path);
    }
}

string Common::getDateStr(int year, int allDay) {
    string dateStr;
    int monthDay[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (year > 0 && !(year % 4) && (year % 100 || !(year % 400)))
        monthDay[1] = 29;
    int month = 1,day = 1;
    for(int i = 0;i < 12; ++i){
        if(allDay > monthDay[i]){
            allDay -= monthDay[i];
            ++month;
        }else{
            day = allDay;
            break;
        }
    }
    string monthStr = to_string(month);
    if(monthStr.size() < 2)
        monthStr = '0' + monthStr;
    string dayStr = to_string(day);
    if(dayStr.size() < 2)
        dayStr = '0' + dayStr;
    return to_string(year) + monthStr + dayStr;
}

void Common::getDataFromF90Bin(const char* fileName) {
    /*
     * C风格写法
     */
    FILE* fid;
    fid = fopen(fileName,"rb");
    if(fid == NULL){
        printf("open bin file err.\n");
        return;
    }
    int i = 0;
    while(1){
        char dstNameLen,dataType,perDataSize;
        unsigned long long dims[2];
        void* data;
        fread(&dstNameLen, sizeof(char),1,fid);
        if(feof(fid))
            break;
        printf("dstNameLen: %d\n",dstNameLen);
        char* dstName = (char*)malloc(sizeof(char) * dstNameLen + 1);
//        void* dstName = (char*)malloc((sizeof(char) * 32));
        fread(dstName, sizeof(char),dstNameLen,fid);
        dstName[dstNameLen] = '\0';
        printf("dstName: %s,size:%d\n",(char*)dstName, strlen(dstName));
//        cout << dstName << endl;
        // dataType : 1 整型 2 浮点数
        fread(&dataType, sizeof(char),1,fid);
        printf("dataType: %d\n",dataType);
        fread(&perDataSize, sizeof(char),1,fid);
        printf("perDataSize: %d\n",perDataSize);
        fread(&dims[0], sizeof(unsigned long long),1,fid);
        printf("dims[0]: %d\n",dims[0]);
        fread(&dims[1], sizeof(unsigned long long),1,fid);
        printf("dims[1]: %d\n",dims[1]);
        unsigned long long nums = 0;
        nums = dims[0] * dims[1];
#define READ_DATA(x) \
        data = malloc(sizeof(x) * nums);\
        fread(data, sizeof(x),nums,fid);
        if(dataType == 1){
            if(perDataSize == 1) {READ_DATA(char)}
            else if(perDataSize == 2){READ_DATA(short)}
            else if(perDataSize == 4){READ_DATA(int)}
            else if(perDataSize == 8){READ_DATA(long long)}
        }else if(dataType == 2){
            if(perDataSize == 4){READ_DATA(float)}
            else if(perDataSize == 8){READ_DATA(double)}
        }else{
            printf("read data err.\n");
            return;
        }
        ++i;
        free(dstName);
        free(data);
        dstName = NULL;
        data = NULL;
    };
    fclose(fid);
    cout << i << endl;
}

#if 0 //filesystem 1.72/1.73 fs::directory_iterator iter(path)迭代器编译不过
FileList readAllFile(const string& dir ,const string& rule)
{
    fs::path path(dir);
    if (!fs::exists(path))
        return FileList();

    FileList file_list;
    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(path); iter != end_iter; ++iter)
    {
        if (fs::is_regular_file(iter->status()))
        {
            string file_name = iter->path().filename().string();
            std::regex reg(rule + ".+\\.txt");
            /*
             * 7服务器的gcc4.8.5的search不会获得预期的结果
             */
            if (std::regex_search(file_name, reg)) {
                file_list.push_back({ iter->path().string(),file_name });
            }
        }

        if (fs::is_directory(iter->status()))
            //get_filenames(iter->path().string(), filenames);
            continue;
    }

    return file_list;
}
#endif

string getPath(string full_path){
    if(full_path.back() == '/')
        return string(full_path.begin(),full_path.end()-1);
    else{
        auto it = full_path.find_last_of('/');
        return string(full_path.begin(),full_path.begin() + it);
    }
}
vector<string> readAllFile(string dir_str)
{
    if (dir_str.at(dir_str.size() - 1) != '/')
        dir_str.push_back('/');

    // check if dir_name is a valid dir
    struct stat s;
    lstat(dir_str.c_str(), &s);
    if (!S_ISDIR(s.st_mode))
    {
        cout << "dir_name is not a valid directory !" << endl;
        return vector<string>();
    }

    struct dirent * filename;    // return value for readdir()
    DIR * dir;                   // return value for opendir()
    dir = opendir(dir_str.c_str());
    if (NULL == dir)
    {
        cout << "Can not open dir " << dir_str << endl;
        return vector<string>();
    }

    vector<string> file_list;
    while ((filename = readdir(dir)) != NULL)
    {
        if (strcmp(filename->d_name, ".") == 0 ||
            strcmp(filename->d_name, "..") == 0)
            continue;
        string filePathName = filename->d_name;
        std::regex reg("boo.+\\.gz");
        /*
         * gcc 4.8.5 的search达不到预期的结果
         */
        if(std::regex_search(filePathName,reg)){
            filePathName = dir_str + filePathName;
            file_list.push_back(filePathName);
        }
    }
    return file_list;
}

double Date2ri(array<float,6> &date){
    if(date[1]<=2){
        date[0] -= 1.0;
        date[1] += 12.0;
    }
    double ri = 0;
    ri = floor(365.25*(date[0]+4716.0)) + floor(30.6001*(date[1]+1.0)) + 2.0 - floor(date[0]/100.0) + \
    floor(floor(date[0]/100.0)/4.0) + date[2] - 1524.5 + (date[3] + date[4]/60 + date[5]/3600)/24;
    return ri - 1721058.5;

}

class A {
public:
    A() {indexa = 0;}

    A(int x) : indexa(x) {}

    virtual void print() {
        cout << "This is A:" << indexa << endl;
    }

private:
    int indexa;
};

class B : public A {
public:
    B(int x = 0) : indexb(x) {}

    void print() {
        cout << "This is B:" << indexb << endl;
    }
    void show(){
        cout << "B own." << endl;
    }

private:
    int indexb;
};


int mmdd2dnum(size_t year, size_t month, int day) {
    size_t yday[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    size_t sum = 0;
    if (year > 0 && !(year % 4) && (year % 100 || !(year % 400)))
        yday[1] = 29;
    std::for_each(yday, yday + month - 1, [&sum](size_t &x) {
        sum += x;
    });
    return sum + day;
}

string date2weeks(string file_time){
    int days = 0;
    int year = std::stoi(file_time.substr(0,4));
    int month = std::stoi(file_time.substr(4,2));
    int day = std::stoi(file_time.substr(6,2));
    auto isLeapYear = [](int year)->bool{
        if (year > 0 && !(year % 4) && (year % 100 || !(year % 400)))
            return true;
        else
            return false;
    };
    int yday[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if(isLeapYear(year))
        yday[1] = 29;
    std::for_each(yday, yday + month - 1, [&days](int &x) {
        days += x;
    });
    days += day;
    while (year != 2001){
        if(isLeapYear(--year))
            days += 366;
        else
            days += 365;
    }
    return std::to_string((days-1)/7 + 1);
}

//ListNode* mergeKLists(vector<ListNode*>& lists) {
//    auto greater_node = [](ListNode* l1,ListNode* l2){
//        return l1->val > l2->val;
//    };
//    /*
//     * 强行使用lambda
//     */
//    std::priority_queue<ListNode*, vector<ListNode*>, decltype(greater_node)> pri_queue(greater_node);
//    // 建立大小为k的小根堆
//    for(auto elem : lists){
//        if(elem) pri_queue.push(elem);
//    }
//    // 可以使用哑节点/哨兵节点
//    ListNode dummy(-1);
//    ListNode* p = &dummy;
//    // 开始出队
//    while(!pri_queue.empty()){
//        p->next = pri_queue.top();
//        pri_queue.pop();
//        p = p->next;
//        if(p->next)
//            pri_queue.emplace(p->next);
//    }
//    return dummy.next;
//}

/*
 * 提取txt配置，转为buoy.xml
 */
void txt2xml() {
    using namespace boost::property_tree;
    ptree pt_all;
    ptree pt_lld, pt_buoy;

    std::ifstream ifs("/home/gp/ndbc/ndbc_buoy_post.txt", std::ios::in);
    string line_str;
    unordered_set<string> ndbc_id;
    if (ifs.is_open()) {
        while (getline(ifs, line_str)) {
            std::stringstream ss;
            ss << line_str;
            string station[4];
            ss >> station[0];
            if (ndbc_id.find(station[0]) != ndbc_id.end())
                continue;
            else
                ndbc_id.emplace(station[0]);
            for (int i = 1; i < 4; ++i) {
                if (!(ss >> station[i]))
                    cout << "stream >> fail." << endl;
            }
            pt_lld.add("lon", station[2]);
            pt_lld.add("lat", station[1]);
            pt_lld.add("depth", station[3]);
            pt_buoy.add_child("buoy", pt_lld).put("<xmlattr>.header", station[0]);
            pt_lld.clear();
        }
        pt_all.add_child("data", pt_buoy);
        boost::property_tree::xml_writer_settings<string> settings(' ', 2);
        write_xml("/home/gp/ndbc/buoy2.xml", pt_all, std::locale(), settings);
        ifs.close();
    } else
        cout << "txt open fail." << endl;
}