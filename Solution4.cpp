/******************************************************************************
 * Author      : Gao Peng
 * CreateDate  : 2021/6/15 15:17
 * Modify      : 2021/7/1
 * Version     : 1.0
 * Description : 动态规划为主的题目
 ******************************************************************************/

#include "Solution.h"

// 正则表达式匹配
bool Solution::isMatch(string s, string p){
    // 方法:DP
    uint sCount = s.size();
    uint pCount = p.size();
    // 注意这种bool的vector,位存储,迭代器不能正常使用,使用传统for遍历来更改值
    vector<vector<bool>> dp(pCount + 1,vector<bool>(sCount + 1,false));
    // 全文匹配,空只能匹配空
    // 第一行，除了dp[0][0],其他固定都是false
    // 第一列，空串可能会匹配 c*a* 这种模式
    dp[0][0] = true;

    for (int i = 1; i <= pCount; ++i) {
        for (int j = 0; j <= sCount; ++j) {
            if(p[i - 1] == '*'){
                // 0次: dp[i - 2][j]
                // 1次: dp[i - 1][j]
                // n次: dp[i][j - 1]
                if(j == 0)
                    dp[i][j] = dp[i - 2][j];
                else
                    dp[i][j] = dp[i - 2][j] | dp[i - 1][j] | (dp[i][j - 1] & (p[i - 2] == s[j - 1] | p[i - 2] == '.'));
            }else if(p[i - 1] == '.'){
                if(j == 0) continue;
                dp[i][j] = dp[i - 1][j - 1];
            }else{
                if(j == 0) continue;
                dp[i][j] = dp[i - 1][j - 1] & (p[i - 1] == s[j - 1]);
            }
        }
    }
    return dp[pCount][sCount];
}

// 目标和
int Solution::findTargetSumWays(vector<int>& nums, int target){
    // 初始定义
    // dp[i][j]: 前i个数,和为j的方案数

    // 无优化DP
    /*
    long sum = std::accumulate(nums.begin(),nums.end(),0);
    long upper = 2 * sum + 1;
    vector<vector<long>> dp(nums.size(),vector<long>(upper,0));
    if(!nums[0])
        dp[0][sum] = 2;
    else {
        dp[0][sum + nums[0]] = 1;
        dp[0][sum - nums[0]] = 1;
    }
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < dp[i].size(); ++j) {
            if(j + nums[i] < upper)
                dp[i][j] = dp[i - 1][j + nums[i - 1]];
            if(j > nums[i])
                dp[i][j] += dp[i - 1][j - nums[i - 1]];
        }
    }
    return dp[nums.size() - 1][target + sum];
    */

    // 空间优化
    long sum = std::accumulate(nums.begin(),nums.end(),0);
    long upper = 2 * sum + 1;
    vector<vector<long>> dp(2,vector<long>(upper,0));
    if(!nums[0])
        dp[0][sum] = 2;
    else {
        dp[0][sum + nums[0]] = 1;
        dp[0][sum - nums[0]] = 1;
    }
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = 0; j < dp[i%2].size(); ++j) {
            if(j + nums[i] < upper)
                dp[i%2][j] = dp[(i - 1)%2][j + nums[i - 1]];
            if(j > nums[i])
                dp[i%2][j] += dp[(i - 1)%2][j - nums[i - 1]];
        }
    }
    return dp[(nums.size() - 1) % 2][target + sum];
}

// 传递信息
int Solution::numWays(int n, vector<vector<int>>& relation, int k) {
    // dp[i][j]定义为经过i轮到j的方案数

    // 取余的方法在 += 时就会有问题:非0+=
    /*vector<vector<int>> dp(2,vector<int>(n));
    dp[0][0] = 1;
    for(int i = 0;i < k; ++i){
        for(int j = 0;j < relation.size(); ++j){
            int send = relation[j][0];
            int recv = relation[j][1];
            dp[(i + 1)%2][recv] += dp[i%2][send];
        }
    }
    return dp[k%2][n - 1];*/

    vector<int> dp(n);
    dp[0] = 1;
    for (int i = 0; i < k; i++) {
        vector<int> next(n);
        for (auto& edge : relation) {
            int send = edge[0], recv = edge[1];
            next[recv] += dp[send];
        }
        dp = next;
    }
    return dp[n - 1];
}