/******************************************************************************
 * Description : leetcode website algorithm to practice 3
 * Author      : Gao Peng
 * Date        : 2021-2-19
 * modify      : 2021-4-11
 * version     : 1.0
 ******************************************************************************/
#include "Solution.h"

// 连续1的个数 Ⅲ
int Solution::longestOnes(vector<int> &A, int K) {
    int res = 0, count = 0, left = 0, right = 0;
    for (; right < A.size(); ++right) {
        if (A[right] == 0) ++count;
        while (count > K) {
            if (A[left++] == 0) --count;
        }
        res = std::max(res, right - left + 1);
    }
    return res;
}

// 数组的度
int Solution::findShortestSubArray(vector<int>& nums){
    unordered_map<int,vector<int>> hashMap;
    for (int i = 0; i < nums.size(); ++i) {
        if(hashMap.find(nums[i]) == hashMap.end()){
            hashMap.emplace(nums[i],vector<int>{1,i,i});
        }else{
            ++hashMap[nums[i]][0];
            hashMap[nums[i]][2] = i;
        }
    }
    int maxNums = 0,minLen = 0;
    for (auto& [_,vec]:hashMap) {
        if(maxNums < vec[0]){
            maxNums = vec[0];
            minLen = vec[2] - vec[1] + 1;
        }else if(maxNums == vec[0]){
            minLen = std::min(minLen,vec[2] - vec[1] + 1);
        }
    }
    return minLen;
}

// 爱生气的书店老板
int Solution::maxSatisfied(vector<int> &customers, vector<int> &grumpy, int X) {
    int noAngry = 0;
    int maxChanges = 0;
    int changes = 0;
    // 可以不使用队列来降低空间复杂度
    std::queue<int> qChange;
    for (int i = 0; i < customers.size(); ++i) {
        int change = 0;
        if(grumpy[i] == 0){
            noAngry += customers[i];
        }else{
            change = customers[i];
        }
        qChange.push(change);
        changes += change;
        if(qChange.size() > X){
            changes -= qChange.front();
            qChange.pop();
        }
        maxChanges = std::max(changes,maxChanges);
    }
    return noAngry + maxChanges;
}

// 翻转图像
vector<vector<int>> Solution::flipAndInvertImage(vector<vector<int>>& A){
    for (int i = 0; i < A.size(); ++i) {
        int n = A[i].size();
        for (int j = 0; j < (n+1)/2; ++j) {
            int tmp = A[i][j];
            A[i][j] = 1 ^ A[i][n - 1 - j];
            A[i][n - 1 - j] = 1 ^ tmp;
        }
    }
    return A;
}

// 猜字谜
vector<int> Solution::findNumOfValidWords(vector<string>& words, vector<string>& puzzles){
    vector<int> res(puzzles.size(),0);
    unordered_map<int,int> hashWords;
    for (auto& word:words) {
        int mask = 0;
        for (int i = 0; i < word.size(); ++i) {
            mask |= (1 << word[i] - 'a');
        }
        if(__builtin_popcount(mask) <= 7)
            ++hashWords[mask];
    }
    for (int i = 0;i < puzzles.size(); ++i) {
        int mask = 0;
        for (int j = 1; j < 7; ++j) {
            mask |= (1 << puzzles[i][j] - 'a');
        }
        int subMask = mask;
        int count = 0;
        do{
            int readSubMask = subMask | (1 << puzzles[i][0] - 'a');
            if(hashWords.count(readSubMask))
                count += hashWords[readSubMask];
            /*
             * 求子集新方式 n = (n - 1) & mask
             */
            subMask = (subMask - 1) & mask;
        }while(subMask != mask);
        res[i] = count;
    }
    return res;
}

// 至少有 K 个重复字符的最长子串
int Solution::longestSubstring(string s, int k){
    unordered_map<char,size_t> hashMap;
    int mask = 0;
    int kMask = 0;
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        char index = s[i] - 'a';
        mask |= (1 << index);
        ++hashMap[index];
        if(hashMap[index] >= k)
            kMask |= (1 << index);
        if(mask & kMask == mask)
            res = std::max(res,0);
    }
}

// 删除字符串中的重复项
string Solution::removeDuplicates(string S){
    string res;
    for(auto& s:S){
        if(!res.empty() && res.back() == s)
            res.pop_back();
        else
            res += s;
    }
    return res;
}

// 基本计算器
int Solution::calculateBase(string s) {
    /*
     * 可以换一种通用思维兼容所有四则运算
     * 首先将中缀表达式转换为逆波兰表达式，再对其解析
     */
    std::stack<int> ops;
    ops.push(1);
    int sign = 1;

    int ret = 0;
    int n = s.length();
    int i = 0;
    while (i < n) {
        if (s[i] == ' ') {
            i++;
        } else if (s[i] == '+') {
            sign = ops.top();
            i++;
        } else if (s[i] == '-') {
            sign = -ops.top();
            i++;
        } else if (s[i] == '(') {
            ops.push(sign);
            i++;
        } else if (s[i] == ')') {
            ops.pop();
            i++;
        } else {
            long num = 0;
            while (i < n && s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
                i++;
            }
            ret += sign * num;
        }
    }
    return ret;
}

// 基本计算器 Ⅱ
int Solution::calculateBase2(string s){

    std::stack<int> numStk;
    std::stack<char> opStk;
    int n = s.size();
    int i = 0;
    int res = 0;
    auto getNumber = [&](){
        int res = 0;
        while(i < n){
            if(s[i] >= '0' && s[i] <= '9'){
                // 注意这个括号，避免2147483647计算溢出
                res = res*10 + (s[i] - '0');
                ++i;
            }else if(s[i] == ' ') {
                ++i;
                continue;
            }
            else
                break;
        }
        if(!opStk.empty() && opStk.top() == '-')
            res = -res;
        return res;
    };
    while(i < n){
        if(s[i] == ' '){
            ++i;
        }else if(s[i] == '+'){
            opStk.push('+');
            ++i;
        }else if(s[i] == '-'){
            opStk.push('-');
            ++i;
        }else if(s[i] == '*'){
            opStk.push('*');
            int tmp = numStk.top();
            numStk.pop();
            ++i;
            numStk.push(tmp * getNumber());
            opStk.pop();
        }else if(s[i] == '/'){
            opStk.push('/');
            int tmp = numStk.top();
            numStk.pop();
            ++i;
            numStk.push(tmp / getNumber());
            opStk.pop();
        }else{
            numStk.push(getNumber());
        }
    }

    while(!numStk.empty()){
        res += numStk.top();
        numStk.pop();
    }
    return res;
}

// 螺旋矩阵
vector<int> Solution::spiralOrder(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> res;
    res.reserve(rows*cols);
    int d = rows - 1, r = cols - 1;
    int u = 0, l = 0;
    while(1){
        for(int i = l;i <= r; ++i)
            res.emplace_back(matrix[u][i]);
        if(++u > d) break;
        for(int i = u;i <= d; ++i)
            res.emplace_back(matrix[i][r]);
        if(--r < l) break;
        for(int i = r;i >= l; --i)
            res.emplace_back(matrix[d][i]);
        if(--d < u) break;
        for(int i = d;i >= u; --i)
            res.emplace_back(matrix[i][l]);
        if(++l > r) break;
    }
    return res;
}

// 螺旋矩阵Ⅱ
vector<vector<int>> Solution::generateMatrix(int n){
    vector<vector<int>> res(n,vector<int>(n));
    int i = 0;
    int u = 0, l = 0, r = n - 1, d = n - 1 ;
    while(i < n*n){
        for (int j = l; j <= r; ++j)
            res[u][j] = ++i;
        if(++u > d) break;
        for (int j = u; j <= d; ++j)
            res[j][r] = ++i;
        if(--r < l) break;
        for (int j = r; j >= l; --j)
            res[d][j] = ++i;
        if(--d < u) break;
        for (int j = d; j >= u; --j)
            res[j][l] = ++i;
        if(++l > r) break;
    }
    return res;
}

// 删除有序数组中的重复项 II
int Solution::removeDuplicates(vector<int>& nums) {
//    int val = 10001;
//    int count = 1;
//    auto it = nums.end() - 1;
//    for (; it >= nums.begin(); --it) {
//        if(*it != val){
//            if(count > 2){
//                nums.erase(it + 3,it + count + 1);
//            }
//            count = 1;
//            val = *it;
//        } else{
//            ++count;
//        }
//    }
//    if(count > 2)
//        nums.erase(it + 3,it + count + 1);
//    return nums.size();

    int n = nums.size();
    if(n < 3)
        return n;
    int fast = 2;
    int slow = 2;
    while(fast < n){
        if(nums[fast] != nums[slow - 2]){
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

// 直方图的水量
int Solution::trap(vector<int>& height){
    int left = 0;
    int right = height.size() - 1;
    int level = 1;
    int sum = 0;
    int heightSum = std::accumulate(height.begin(),height.end(),0);
    while(left <= right){
        while(left <= right && height[left] < level){
            ++left;
        }
        while(right >= left && height[right] < level){
            --right;
        }
        sum += (right - left + 1);
        ++level;
    }
    return sum - heightSum;
}

// 丑数Ⅱ
int Solution::nthUglyNumber(int n) {
    int* dp = new int[n + 1];
    dp[1] = 1;
    int p2 = 1, p3 = 1, p5 = 1;
    for(int i = 2;i <= n; ++i){
        int tmp2 = dp[p2] * 2;
        int tmp3 = dp[p3] * 3;
        int tmp5 = dp[p5] * 5;
        dp[i] = std::min(tmp2,std::min(tmp3,tmp5));
        if(dp[i] == tmp2)
            ++p2;
        if(dp[i] == tmp3)
            ++p3;
        if(dp[i] == tmp5)
            ++p5;
    }
    int res = dp[n];
    delete[] dp;
    return res;
}

// 最大数
string Solution::largestNumber(vector<int>& nums){
    int n = nums.size();
    vector<string> numsStr(n);
    for(int i = 0;i < n; ++i)
        numsStr[i] = std::to_string(nums[i]);
    std::sort(numsStr.begin(),numsStr.end(),[](string& a,string& b){
        return a + b > b + a;
    });
    if(numsStr[0] == "0")
        return "0";
    string res;
    for(auto& s:numsStr)
        res += s;
    return res;
}

// 青蛙过河
bool Solution::canCross(vector<int>& stones){
    //bool dp[m][n]，第m个石头，跳过来的上一步长为n的状态
    vector<vector<bool>> dp(2001,vector<bool>(2001,false));
    dp[1][1] = true;
    int n = stones.size();
    // 根据第一步长1，每次最多增长1，有如下判断
    for (int i = 1; i < n; ++i) {
        if(stones[i] - stones[i - 1] > i)
            return false;
    }
    for (int i = 2; i < n; ++i) {
        for (int j = 1; j < i; ++j) {
            int t = stones[i] - stones[j];
            if(t <= j + 1)
                dp[i][t] = dp[j][t - 1] || dp[j][t] || dp[j][t + 1];
        }
    }
    // vector<bool>特殊性:并不是用单字节的bool实现，而是位，导致了引用这类指针操作不能正常使用
    for(auto t : dp[n - 1]){
        if(t)
            return true;
    }
    return false;
//    // 纯DFS，需要优化:记忆化查询
//    if(stones[1] != 1)
//        return false;
//    bool res = false;
//    int n = stones.size();
//    std::function<void(int,int)> dfs = [&](int idx,int step){
//        if(idx == n - 1) {
//            res = true;
//            return;
//        }
//        for (int i = idx + 1; i < n; ++i) {
//            int t = stones[i] - stones[idx];
//            if(t == step || t == step - 1 || t == step + 1){
//                dfs(i,t);
//            }else if(t > step + 1)
//                break;
//        }
//    };
//    dfs(1,1);
//    return res;
}

// 字符串的排列
vector<string> Solution::permutation(string s){
    typedef unsigned char uchar;
    std::sort(s.begin(),s.end());
    vector<string> res;
    string resOne;
    int n = s.size();
    std::function<void(uchar)> dfs = [&](uchar bit) {
        if (bit == 0) {
            res.emplace_back(resOne);
            return;
        }
        for (int i = 0; i < n; ++i) {
            char ibit = 1 << i;
            // 如果s[i]和s[i-1]相同,那么 i-1 位必须为0(使用过),未使用过则会产生重复结果
            if (bit & ibit && (i == 0 || s[i] != s[i - 1] || (s[i] == s[i - 1] && !(bit & ibit >> 1)))) {
                resOne += s[i];
                dfs(bit & ~ibit);
                resOne.pop_back();
            }
        }
    };
    dfs(0b11111111 >> (8 - s.size()));
    return res;
}

// Excel表列名称 2021.6.29
string Solution::convertToTitle(int columnNumber){
    string s;
    int mod;
    while(columnNumber > 0){
        --columnNumber;
        mod = columnNumber % 26;
        columnNumber = columnNumber / 26;
        s += ('A' + mod);
    }
    std::reverse(s.begin(),s.end());
    return s;
}

// 根据字符出现频率排序
string Solution::frequencySort(string s){
    auto big2small = [](const int a,const int b){
        return a > b;
    };
    unordered_map<char,int> charMap;
    map<int,vector<char>,decltype(big2small)> frequencyMap(big2small);
    for(auto& i:s)
        ++charMap[i];
    for(auto& i:charMap)
        frequencyMap[i.second].emplace_back(i.first);
    string res;
    for(auto& i:frequencyMap){
        for (auto& j:i.second) {
            res += string(i.first,j);
        }
    }
    return res;
}

// 计数质数
int Solution::countPrimes(int n){
    // 埃氏筛
    vector<bool> isPrime(n,true);
    int res = 0;
    for (int i = 2; i < n; ++i) {
        if(isPrime[i]){
            ++res;
            for (auto j = (long long)i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return res;
}

// 和相同的二元子数组
int Solution::numSubarraysWithSum(vector<int>& nums, int goal){
    // 哈希表，前缀和
    unordered_map<int,int> hashMap;
    // hashMap[0]首先初始化为1,想想为什么
    hashMap[0] = 1;
    int sum = 0, res = 0;
    for(auto& t:nums){
        sum += t;
        if(hashMap.count(sum - goal))
            res += hashMap[sum - goal];
        ++hashMap[sum];
    }
    return res;
}

// 主要元素
int Solution::majorityElement(vector<int> &nums) {
    // Boyer-Moore(摩尔投票算法)
    int count = 0;
    int lastVal = 0;
    for (auto& t:nums) {
        if(count == 0) {
            lastVal = t;
            count = 1;
        }
        else if(t == lastVal)
            ++count;
        else if(t != lastVal)
            --count;
    }
    if(count == 0)
        return -1;
    count = 0;
    for (auto& t:nums) {
        if(t == lastVal)
            ++count;
    }
    return count > nums.size()/2 ? lastVal : -1;
}

// 连接词
vector<string> Solution::findAllConcatenatedWordsInADict(vector<string>& words){
    // 先构建前缀树
    struct Trie{
        bool m_isWord = false;
        vector<Trie*> m_trie;
        Trie(){
            m_trie.resize(26, nullptr);
        }
        ~Trie(){
            for (auto& p:m_trie) {
                // delete自己会判断空指针
                delete p;
                p = nullptr;
            }
        }
        void insert(string& word){
            Trie* node = this;
            for(auto& t:word){
                auto idx = t - 'a';
                if(!node->m_trie[idx])
                    node->m_trie[idx] = new Trie();
                node = node->m_trie[idx];
            }
            node->m_isWord = true;
        }
//        bool search(string& word){
//            Trie* node = this;
//            for(auto& t:word){
//                node = node->m_trie[t - 'a'];
//                if(!node)
//                    return false;
//            }
//            return node->m_isWord;
//        }
    };
    Trie root;
    for (auto& t:words) {
        root.insert(t);
    }
    vector<string> res;
    std::function<bool(const string&,int,int)> dfs = [&](const string& s,int idx,int count){
        if(idx == s.size()) {
            if(count > 1) {
                res.emplace_back(s);
                return true;
            }
        }
        Trie* node = &root;
        for (int i = idx; i < s.size(); ++i) {
            if(!node->m_trie[s[i] - 'a'])
                return false;
            if(node->m_trie[s[i] - 'a']->m_isWord){
                // 这里返回false也要记得node下一个
                if(dfs(s,i + 1,count + 1))
                    // 只要有能连接的就返回,防止多余的查找
                    return true;
            }
            // node下一个
            node = node->m_trie[s[i] - 'a'];
        }
        return false;
    };
    for (auto& s:words)
        dfs(s,0,0);
    return res;
}

// 天际线问题
vector<vector<int>> Solution::getSkyline(vector<vector<int>>& buildings){
    using std::pair;
    // 这里是刻意手写，熟练一下，和默认排序规则一样。
    auto cmp = [](const pair<int,int>& a,const pair<int,int>& b){
        if(a.first != b.first){
            return a.first < b.first;
        }else{
            return a.second <= b.second;
        }
    };
    vector<vector<int>> res;
    std::multiset<pair<int,int>, decltype(cmp)> city(cmp);
    for(auto& t:buildings){
        city.emplace(t[0],-t[2]);
        city.emplace(t[1],t[2]);
    }

    // 记录高度序列，因为当前高度如果发生变化，不一定是修改为当前点的高度
    // 0是在最后删掉所有高度后保留的最后一个数据(题目要求)
    std::multiset<int> heights{0};
    vector<int> lastPoint{0,0};
    for(auto& t:city){
        if(t.second < 0)
            heights.emplace(-t.second);
        else
            // 注意必须使用迭代器删除一个,使用key值会删除所有重复的
            heights.erase(heights.find(t.second));

        auto maxHeight = *heights.rbegin();
        if(lastPoint[1] != maxHeight){
            lastPoint[0] = t.first;
            lastPoint[1] = maxHeight;
            res.emplace_back(lastPoint);
        }
    }
    return res;
}

// 绝对差值和
int Solution::minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2){
    vector<int> nums(nums1.begin(),nums1.end());
    std::sort(nums.begin(),nums.end());
    long long sum = 0;
    int maxChange = 0;
    const int mod = 1e9 + 7;
    for (int i = 0; i < nums1.size(); ++i) {
        auto diff = abs(nums1[i] - nums2[i]);
        auto it = std::lower_bound(nums.begin(),nums.end(),nums2[i]);
        int minDiff = INT32_MAX;
        if(it == nums.begin())
            minDiff = std::min(minDiff,abs(*it - nums2[i]));
        else if(it == nums.end())
            minDiff = std::min(minDiff,abs(*nums.rbegin() - nums2[i]));
        else {
            minDiff = std::min(minDiff, abs(*it - nums2[i]));
            minDiff = std::min(minDiff, abs(*(--it) - nums2[i]));
        }
        maxChange = std::max(maxChange, diff - minDiff);
        sum += abs(nums1[i] - nums2[i]);
    }
    return (sum - maxChange) % mod;
}

// 最长回文串
int Solution::longestPalindrome(string s) {
    // 最长回文串
    // 偶数个相同字符可以直接放在两边
    // 奇数个只能有一个可以完全使用,其余各自必须少用一个
    int res = 0;
    map<char, int> m;
    for (char &c:s)
        ++m[c];
    bool isAdd = false;
    for (auto& [_, i]:m) {
        res += i / 2 * 2;
        if (!isAdd && i % 2 == 1) {
            ++res;
            isAdd = true;
        }
    }
    return res;
}

// 最高频元素的频数
int Solution::maxFrequency(vector<int>& nums, int k){
    std::sort(nums.begin(),nums.end());
    int left = 0;
    long long sum = 0;
    int res = 1;
    for (int i = 1; i < nums.size(); ++i) {
        sum += (long long)(nums[i] - nums[i - 1]) * (i - left);
        while(sum > k){
            sum -= (nums[i] - nums[left]);
            ++left;
        }
        res = std::max(res, i - left + 1);
    }
    return res;
}

// 检查是否区域内所有整数都被覆盖
bool Solution::isCovered(vector<vector<int>>& ranges, int left, int right){
    // 差分数组
    // 52是题目区间限制 [0,50]
    vector<int> diff(52,0);
    for (int i = 0; i < ranges.size(); ++i) {
        ++diff[ranges[i][0]];
        --diff[ranges[i][1] + 1];
    }
    // 计算前缀和,不大于0的就是没覆盖
    long prefixSum = 0;
    // 1和50是题目定死的区间
    for (int i = 1; i <= 50; ++i) {
        prefixSum += diff[i];
        if(i >= left && i <= right && prefixSum <= 0)
            return false;
    }
    return true;
}

// 两整数之和
int Solution::getSum(int a, int b){
    while(b != 0){
        unsigned int c = (a & b) << 1;
        a ^= b;
        b = c;
    }
    return a;
}

// 密钥格式化
string Solution::licenseKeyFormatting(string s, int k){
    int count = 0;
    for(char& c:s){
        if(c != '-')
            ++count;
    }
    if(!count) return "";
    int mod = count % k;
    int n = count / k;
    int bytes = n * (k + 1) + mod;
    if(!mod) --bytes;
    string res(bytes,' ');
    int i = 0;
    int ii = 0;

    while(count){
        int j = 0;
        int kk = k;
        if(mod) kk = mod;
        while(j != kk){
            char tmp = s[i++];
            if(tmp != '-'){
                ++j;
                // tmp <= 'z'实际不需要写
                if(tmp >= 'a')
                    tmp -= 32;
                res[ii++] = tmp;
            }
        }
        count -= kk;
        if(mod) mod = 0;
        if(ii != bytes)
            res[ii++] = '-';
    }
    return res;
}