/******************************************************************************
 * Description : leetcode website algorithm to practice 1
 * Author      : Gao Peng
 * Date        : 2020-6-2
 * modify      : 2021-3-12
 * version     : 1.0
 ******************************************************************************/
#include "Solution.h"
#include <numeric>

// 增减字符串匹配
vector<int> Solution::diStringMatch(string S){
    size_t n = S.size();
    if(!n)
        return vector<int>();
    vector<int> ans(n+1);
    int min = 0,max = n;
    for (int i = 0; i < n; ++i) {
        if(S[i] == 'I'){
            ans[i] = min;
            ++min;
        }else{
            ans[i] = max;
            --max;
        }
    }
    ans[n] = min;
    return ans;
}
TreeNode* Solution::sortedListToBST(ListNode* head) {
    if(!head)
        return nullptr;
    auto getSize = [&]{
        ListNode *p = head;
        size_t n = 0;
        if(p){
            ++n;
            p = p->next;
        }
        return n;
    };
    size_t n = getSize();
    return genTree(head,0,n-1);
}

TreeNode* Solution::genTree(ListNode*& head,int left,int right){
    if(left > right)
        return nullptr;
    int mid = (left + right)/2;
    TreeNode* left_node = genTree(head,left,--mid);
    TreeNode* node = new TreeNode(head->val);
    node->left = left_node;
    head = head->next;
    if(head)
        node->right = genTree(head,++mid,right);
    else
        node->right = nullptr;
    return node;
}


int Solution::SundaySearch(string text, string pattern){
    int i = 0, j = 0, k;
    int m = pattern.size();

    if(pattern.size() <= 0 || text.size() <= 0)
        return -1;

    for(; i<text.size();) {
        if(text[i] != pattern[j]) {
            for(k=pattern.size() - 1; k>=0; k--) {
                if(pattern[k] == text[m])
                    break;
            }
            i = m-k;
            j = 0;
            m = i+pattern.size();
        }
        else {
            if(j == pattern.size()-1)
                return i-j;
            i++;
            j++;
        }

    }
    return -1;
}

// KMP算法
int Solution::KMP(string s, string p) {
    int n = p.size();
    int next[n], i = 0, j = 0;
    auto GetNext = [&](){
        int j = 0,k = -1;
        next[0] = -1;
        while(j < n-1){
            if(k < 0 || p[j] == p[k]){
                ++j;
                ++k;
                next[j] = k;
            } else
                k = next[k];
        }
    };
    GetNext();
    while (i < s.size() && j < n) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else j = next[j];  //j回退。。。
    }
    if (j == n)
        return (i - n);  //匹配成功，返回子串的位置
    else
        return -1;
};
/*
void Solution::Getnext(int next[], string p) {
    int j = 0, k = -1;
    next[0] = -1;
    while (j < p.size() - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++j;
            ++k;
//            if (p[j] == p[k])//当两个字符相同时，就跳过
//                next[j] = next[k];
//            else
            next[j] = k;
        } else k = next[k];
    }
};
*/

// 堆非递归构建
void Solution::buildMaxHeap(vector <int>& vec)
{
    /*
     * 非递归构建
     */
    size_t n = vec.size();
    for (int i = n/2 - 1; i >= 0; --i){
        int left = i*2 + 1;
        int largest = i;
        int parent = i;
        for (; left < n;) {
            int right = left + 1;
            if(left < n && vec[left] > vec[largest])
                largest = left;
            if(right < n && vec[right] > vec[largest])
                largest = right;
            if(largest != parent)
                std::swap(vec[largest],vec[parent]);
            else
                break;
            parent = largest;
            left = largest*2 + 1;
        }
    }
}
// 堆递归构建
void maxHeapIfy(vector <int>& vec, int i)  //将i节点为根的堆中小的数依次上移,n表示堆中的数据个数
{
    size_t n = vec.size();
    int l = 2 * i + 1;   //i的左儿子
    int r = 2 * i + 2;  //i的右儿子
    int largest = i;   //先设置父节点和子节点三个节点中最大值的位置为父节点下标
    if (l < n && vec[l] > vec[largest])
        largest = l;
    if (r < n && vec[r] > vec[largest])
        largest = r;
    if (largest != i)    //最大值不是父节点，交换
    {
        std::swap(vec[i],vec[largest]);
        maxHeapIfy(vec, largest);  //递归调用，保证子树也是最大堆
    }
}
void Solution::recBuildMaxHeap(vector <int>& vec)  //建立最大堆
{
    /*
     * 递归构建
     * 从最后一个非叶子节点（n/2-1）开始自底向上构建
     */
    size_t n = vec.size();
    for (int i = n / 2-1; i >= 0; i--)
        maxHeapIfy(vec, i);
}

// 新21点
//double Solution::new21Game(int N, int K, int W) {
//
//}
// 统计有序矩阵中的负数
int Solution::countNegatives(vector<vector<int>>& grid){
    int rows = grid.size();
    if(rows == 0)
        return 0;
    int cols = grid[0].size();

    size_t count = 0;
    for (int i = 0; i < rows; ++i) {
        if(grid[i].back() >= 0)
            continue;
        else if(grid[i][0] < 0){
            count += cols*(rows - i);
            break;
        } else{
            /*
             * 二分查找
             */
            int left = 0;
            int right = cols - 1;
            while(left <= right){
                int middle = (left + right)/2;
                if(grid[i][middle] >= 0)
                    left = middle + 1;
                else{
                    if(grid[i][middle-1] >= 0){
                        count += cols - middle;
                        break;
                    }
                    else
                        right = middle - 1;
                }
            }
//            if (grid[i][middle] >= 0) {
//                ++middle;
//                while (grid[i][middle] >= 0)
//                    ++middle;
//                count += cols - middle;
//            } else {
//                --middle;
//                while (grid[i][middle] < 0)
//                    --middle;
//                count += cols - middle - 1;
//            }
        }
    }
    return count;
}
// 大礼包
int Solution::shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
    int valid_index = 0;
    for (int i = 0; i < special.size(); ++i) {
        bool valid_special = true;
        int cost_price = 0;
        for (int j = 0; j < price.size(); ++j) {
            if(needs[j] < special[i][j]){
                valid_special = false;
                break;
            }
            cost_price += special[i][j] * price[j];
        }
        if(valid_special && cost_price > special[i].back()){
            special[valid_index++] = special[i];
        }
    }
    special.erase(special.begin() + valid_index,special.end());
    return 0;
}
// 外观数列
string Solution::countAndSay(int n){
    if (n == 1 )
        return "1";

    string ans = "1";
    size_t count = 1;
    for (int i = 1; i < n; ++i) {
        string tmp = "";
        for (int j = 0; j < ans.length()-1; ++j) {
            if(ans[j] == ans[j+1])
                ++count;
            else{
                tmp = tmp + std::to_string(count) + ans[j];
                count = 1;
            }
        }
        ans = tmp + std::to_string(count) + ans[ans.size()-1];
        count = 1;
    }
    return ans;
}
// 奇数在前偶数在后
void Solution::sortJiOu(vector<int>& nums){
    if(nums.size()<2)
        return;

    /*
     * 此方法下
     * 迭代器速度和整型变量作下标迭代速度基本一致
     */
    vector<int>::iterator left = nums.begin();
    vector<int>::iterator right = nums.end()-1;

    std::function<void()> f_loop = [&]{
        while (*left%2 == 1) {
            ++left;
        }
        while (*right%2 == 0){
            --right;
        }
    };

    f_loop();
    do{
        std::swap(*left,*right);
        f_loop();
    }while (left < right);
}
void Solution::sortJiOu2(vector<int>& nums){
    if(nums.size()<2)
        return;
    /*
     * 整型变量作下标迭代
     */
    size_t left = 0;
    size_t right = nums.size()-1;

    std::function<void(vector<int>&)> f_loop = [&](vector<int>& x){
        while (x[left]%2 == 1) {
            ++left;
        }
        while (x[right]%2 == 0){
            --right;
        }
    };

    f_loop(nums);
    do{
        std::swap(nums[left],nums[right]);
        f_loop(nums);
    }while (left < right);
}
// 无重复最长子串
int Solution::lengthOfLongestSubstring(string s) {
    size_t length = s.size();
    if(length < 2)
        return length;

    std::unordered_set<char> set_s;
    set_s.emplace(s[0]);
    int k = 1;
    int max_length = 0;
    for (int i = 0; i < length; ++i) {
        while(k<length && set_s.find(s[k]) == set_s.end()){
            set_s.emplace(s[k]);
            ++k;
        }
//        int size = set_s.size();
//        max_length = std::max(max_length,size);
        max_length = std::max(max_length,k-i);
        set_s.erase(s[i]);
    }
    return max_length;
}
// 1的个数
int Solution::countDigitOne(int n) {

    if(n<0)
        return 0;
    size_t count = 0;
    long long per = 0;
    long long mod = 0;

    /* i<=n
     * 没有=,1,10等等会出现错误
     */
    for (long long i = 1; i <= n; i *= 10) {
        per = n/(10*i);
        mod = n%(10*i);
        count += per*i;
        if(mod/i > 1)
            count += i;
        else if(mod/i == 1)
            count += mod%i + 1;
        if(per ==0)
            return count;
    }
}
// 找重复的那个数
int Solution::findDuplicate(vector<int>& nums) {

    size_t count = nums.size();
    int left = 1;
    int right = count - 1;
    if(count == 2)
        return nums[0];
    else if(count > 2){
        while (left < right){
            int mid = left + (right - left)/2;
            int cnt = 0;
            for (int &num:nums) {
                if(num <= mid)
                    cnt++;
            }
            if(cnt > mid)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
    else
        return 0;
}

// 找最小正整数
int Solution::firstMissingPositive(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] != i + 1) {
            if (nums[i] <= 0 || nums[i] > nums.size() || nums[i] == nums[nums[i] - 1])
                break;
            std::swap(nums[i],nums[nums[i]-1]);
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != (i + 1)) {
            return (i + 1);
        }
    }
    return (nums.size() + 1);
}
// 最长公共子序列
int Solution::longestCommonSubsequence(string text1, string text2) {

    if(text1.size() == 0 || text2.size() == 0)
        return 0;
    int n1 = text1.size() + 1;
    int n2 = text2.size() + 1;

    int dp[n1][n2];
//    char lcs[n1][n2];
    vector<vector<char>> lcs(n1,vector<char>(n2,0));
//    memset(dp,0, sizeof(dp));
//    memset(lcs,0, sizeof(lcs));
    std::fill(dp[0],dp[0]+n1*n2,0);

    for (int i = 1; i < n1; ++i) {
        for (int j = 1; j < n2; ++j) {
            if(text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                lcs[i][j] = 0;
            }
            else if(dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                lcs[i][j] = 1;
            } else{
                dp[i][j] = dp[i][j-1];
                lcs[i][j] = 2;
            }
        }
    }

    /*
     * 回溯最长序列部分
     */
    /*----------------------------------------------------------------*/
    string s;
    std::function<void(int,int)> printLCS = [&](size_t a,size_t b){
        if(a == 0 || b == 0)
            return;
        if(lcs[a][b] == 0){
            //dp长度比字符串多1，所以要减回去才是对应的序列
            s += text1[a-1];
            printLCS(--a,--b);
        } else if(lcs[a][b] == 1)
            printLCS(--a,b);
        else
            printLCS(a,--b);
    };

    printLCS(n1-1,n2-1);
    std::reverse(s.begin(), s.end());
    cout << s << endl;
    /*----------------------------------------------------------------*/
    return dp[n1-1][n2-1];

}

// 最长公共子串
int Solution::longestCommonSubstr(string text1, string text2){
    int n1 = text1.size();
    int n2 = text2.size();
    if(!n1 || !n2)
        return 0;
    int res = 0;
    vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if(text1[i-1] == text2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                if(dp[i][j] > res)
                    res = dp[i][j];
            }
        }
    }
    return res;
}
// 层序遍历
vector<vector<int>> Solution::levelOrder(TreeNode* root) {
    vector<vector<int>> ret;
    if (!root) return ret;

    /*
     * 队列实现
     */
    std::queue < TreeNode * > q;
    q.push(root);
    while (!q.empty()) {
        int currentLevelSize = q.size();
        ret.push_back(vector<int>());
        for (int i = 1; i <= currentLevelSize; ++i) {
            auto node = q.front();
            q.pop();
            ret.back().push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    return ret;
}
// 给定值求和路径
void Solution::issum(TreeNode *root, int &sum, int temp) {
    if (!root) return;
    if (m.find(temp + root->val - sum) != m.end()) res += m[temp + root->val - sum];
    ++m[temp + root->val];
    if (temp + root->val == sum) ++res;
    issum(root->left, sum, temp + root->val);
    issum(root->right, sum, temp + root->val);
    --m[temp + root->val];
}
// 给定值求和路径
int Solution::pathSum(TreeNode* root, int sum) {
//    issum(root,sum,0);
//    return res;

    int count = 0;
    std::unordered_map<int,int> um;
    auto issum = [&](TreeNode* root, const int& sum, int sum_prefix){
        if(!root)
            return 0;
        //
    };
    return 0;
}

// 位运算
int Solution::insertBits(int N, int M, int i, int j) {
    int tmp = (1<<j-i+1)-1<<i;
    if(i == 0 && j == 31)
        tmp = ~tmp;
    return N&~tmp|M<<i;
}
// 小数转二进制形式的字符串
string Solution::printBin(double num) {

    if(num < 0)
        return "ERROR";
    string str = "0.";
    int loop = 30;
    while (num >0 && --loop){
        num *= 2;
        if(num >= 1) {
            str += '1';
            --num;
        }
        else
            str += '0';
    }
    return num > 0 ? "ERROR" : str;
}
