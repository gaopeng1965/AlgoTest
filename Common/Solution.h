/******************************************************************************
 * Description : algorithm class statement
 * Author      : Gao Peng
 * Date        : 2020-6-2
 * modify      : 2021-7-9
 * version     : 1.0
 ******************************************************************************/
#ifndef ASYC_SOLUTION_H
#define ASYC_SOLUTION_H

#include "Common.h"
//#include <boost/exception/detail/shared_ptr.hpp>

class Solution {
public:
    // 01背包问题
    int packageMaxValue(int capacity,vector<int>& weight,vector<int>& value){
        const int w_size = weight.size();
//        int dp[w_size+1][capacity+1];
        int **dp = new int* [w_size+1];
        for (int i = 0; i < w_size+1; ++i) {
            dp[i] = new int[capacity+1];
        }
        dp[0][0] = {0};
        // std::fill 会影响new的内存释放
//        std::fill(dp[0],dp[0]+(w_size+1)*(capacity+1),0);
        for (int i = 1; i < w_size+1; ++i) {
            for (int j = 1; j < capacity+1; ++j) {
                if(j<weight[i-1])
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = std::max(dp[i-1][j],dp[i-1][j-weight[i-1]] + value[i-1]);
            }
        }
        //回溯查找最大价值方案
        auto findIdea = [&](int id,int j)->string{
            string idea;
            while(id > 0){
                //用内置数组会报错，new的不会，可能与堆栈内存相关
                if(dp[id][j] == dp[id-1][j])
                    idea += 'X';
                else{
                    idea += 'O';
                    j = j - weight[id-1];
                }
                --id;
            }
            std::reverse(idea.begin(),idea.end());
            return idea;
        };
        cout << findIdea(w_size,capacity) << endl;
        int res = dp[w_size][capacity];
        for (int i = 0; i < w_size+1; ++i) {
            delete []dp[i];
        }
        delete []dp;
        return res;
    }
    // 斐波那契数列,节省空间的写法,dp只需两个值不断更新即可
    int fib(int n) {
        int arr[2] = {0, 1};
        for(int i = 2; i <= n; ++i) {
            arr[i & 1] = (arr[0] + arr[1]) % (int)(1e9 + 7);
        }
        return arr[n & 1];
    }
//    int fib(int n){
//        if(n == 1 || n == 2)
//            return 1;
//        int dp[n];
//        dp[0] = dp[1] = 1;
//        for(int i = 2;i < n; ++i)
//            dp[i] = (dp[i-2] + dp[i-1]) % 1000000007;
//        return dp[n-1];
//    }
    /*
     * 青蛙跳台阶问题(初始值为{1，1}的斐波那契数列)
     * 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
     * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
     */
public:
    int res = 0;
    std::unordered_map<int,int> m;
public:
    TreeNode* genTree(ListNode*& head,int left,int right);

    TreeNode* sortedListToBST(ListNode* head);
    //给定值求和路径
    void issum(TreeNode* root, int& sum, int temp);
    //给定值求和路径
    int pathSum(TreeNode* root, int sum);
    //位运算
    int insertBits(int N, int M, int i, int j);
    //小数转二进制形式的字符串
    string printBin(double num);
    //找重复的那个数
    int findDuplicate(vector<int>& nums);
    //找最小正整数
    int firstMissingPositive(vector<int>& nums);
    //最长公共子序列
    int longestCommonSubsequence(string text1, string text2);
    // 最长公共子串
    int longestCommonSubstr(string text1, string text2);
    //层序遍历
    vector<vector<int>> levelOrder(TreeNode* root);
    //1的个数
    int countDigitOne(int n);
    //最长无重复子串
    int lengthOfLongestSubstring(string s);
    //奇数在前偶数在后
    void sortJiOu(vector<int>& nums);
    void sortJiOu2(vector<int>& nums);
    //外观数列
    string countAndSay(int n);
    //大礼包
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs);
    //统计有序矩阵中的负数
    int countNegatives(vector<vector<int>>& grid);
    //新21点
    double new21Game(int N, int K, int W);

    //堆非递归构建
    void buildMaxHeap(vector <int>& vec);
    //堆递归构建
    void recBuildMaxHeap(vector <int>& vec);
    // KMP算法
    int KMP(string s,string p);
    // Sunday算法
    int SundaySearch(string text, string pattern);
    // 增减字符串匹配
    vector<int> diStringMatch(string S);
    // 使数组唯一的最小增量
    int minIncrementForUnique(vector<int>& A);
    // 反转字符串 2
    string reverseStr(string s, int k);
    // 递增子序列
    vector<vector<int>> findSubsequences(vector<int>& nums);
    // leetcode -> cdelotee
    string sortString(string s);
    // 每个元音包含偶数次的最长子字符串
    int findTheLongestSubstring(string s);
    // 口算难题
    bool isSolvable(vector<string>& words, string result);
    // 灯泡开关IV
    int minFlips(string target);
    // 回文子串
    int countSubstrings(string s);
    // 删除子文件夹
    vector<string> removeSubfolders(vector<string>& folder);
    // 扫雷游戏
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click);
    // 最长快乐前缀
    string longestPrefix(string s);
    // 位运算加法
    int addBit(int a,int b);
    // 钥匙和房间
    bool canVisitAllRooms(vector<vector<int>>& rooms);
    // 最短回文串
    string shortestPalindrome(string s);
    // 表示数值的字符串
    bool isNumber(string s);
    // 寻找峰值
    int findPeakElement(vector<int>& nums);
    // N皇后
    vector<vector<string>> solveNQueens(int n);
    // N皇后(只求解数量，用位运算)
    int totalNQueens(int n);
    // 前K个高频元素
    vector<int> topKFrequent(vector<int>& nums, int k);
    // 组合
    vector<vector<int>> combine(int n, int k);
    // 子集
    vector<vector<int>> subsets(vector<int>& nums);
    // 组合总和
    vector<vector<int>> combinationSum(vector<int>& candidates, int target);
    // 组合总和 Ⅱ(结果需要去重，set不能用，因为结果可能是元素相同，排列不同)
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target);
    // 和为s的两个数字
    vector<int> twoSum(vector<int>& nums, int target);
    // 最长回文子串
    string longestSubPalindrome(string s);
    // 组合总和 Ⅲ
    vector<vector<int>> combinationSum3(int k, int n);
    // 分数到小数
    string fractionToDecimal(int numerator, int denominator);
    // 解数独
    void solveSudoku(vector<vector<char>>& board);
    // 单词搜索
    bool exist(vector<vector<char>>& board, string word);
    // 强密码检测器
    int strongPasswordChecker(string s);
    //  全排列
    vector<vector<int>> permuteUnique(vector<int>& nums);
    // 计算器
    int calculate(string s);
    // 形成三的最大倍数
    string largestMultipleOfThree(vector<int>& digits);
    // 和为K的最少斐波那契数字数目
    int findMinFibonacciNumbers(int k);
    // 秋叶收藏集
    int minimumOperations(string leaves);
    // 分割等和子集
    bool canPartition(vector<int>& nums);
    // 数组中第K大元素
    int findKthLargest(vector<int>& nums, int k);
    // 查找常用字符串
    vector<string> commonChars(vector<string>& A);
    // 划分字母区间
    vector<int> partitionLabels(string S);
    // 数组中的最长山脉
    int longestMountain(vector<int>& A);
    // 单词拆分
    bool wordBreak(string s, vector<string>& wordDict);
    // 单词拆分 Ⅱ
    vector<string> wordBreak2(string s, vector<string>& wordDict);
    // 插入区间
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval);
    // 根据数字二进制下1的数目排序
    vector<int> sortByBits(vector<int>& arr);
    // 最接近原点的 K 个点
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K);
    // 自由之路
    int findRotateSteps(string ring, string key);
    // 根据身高重建队列
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people);
    // 不同整数的最少数目
    int findLeastNumOfUniqueInts(vector<int>& arr, int k);
    // 距离顺序排列矩阵单元格
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0);
    // 加油站
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
    // 重构字符串
    string reorganizeString(string S);
    // 将数组拆分成斐波那契序列
    vector<int> splitIntoFibonacci(string S);
    // 找零
    bool lemonadeChange(vector<int>& bills);
    // Dota2 参议院
    string predictPartyVictory(string senate);
    // 字母异位词分组
    vector<vector<string>> groupAnagrams(vector<string>& strs);
    // 分发糖果
    int candy(vector<int>& ratings);
    // 按要求补齐数组
    int minPatches(vector<int>& nums, int n);
    // 无重叠区间
    int eraseOverlapIntervals(vector<vector<int>>& intervals);
    // 旋转数组
    void rotate(vector<int>& nums, int k);
    // 尽可能使字符串相等
    int equalSubstring(string s, string t, int maxCost);
    // 连续1的个数 Ⅲ
    int longestOnes(vector<int>& A, int K);
    // 数组的度
    int findShortestSubArray(vector<int>& nums);
    // 爱生气的书店老板
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X);
    // 翻转图像
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A);
    // 猜字谜
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles);
    // 至少有 K 个重复字符的最长子串
    int longestSubstring(string s, int k);
    // 删除字符串中的重复项
    string removeDuplicates(string S);
    // 基本计算器
    int calculateBase(string s);
    // 基本计算器 Ⅱ
    int calculateBase2(string s);
    // 螺旋矩阵
    vector<int> spiralOrder(vector<vector<int>>& matrix);
    // 螺旋矩阵Ⅱ
    vector<vector<int>> generateMatrix(int n);
    // 删除有序数组中的重复项 II
    int removeDuplicates(vector<int>& nums);
    // 直方图的水量
    int trap(vector<int>& height);
    // 丑数Ⅱ
    int nthUglyNumber(int n);
    // 最大数
    string largestNumber(vector<int>& nums);
    // 青蛙过河
    bool canCross(vector<int>& stones);
    // 正则表达式匹配
    bool isMatch(string s, string p);
    // 目标和
    int findTargetSumWays(vector<int>& nums, int target);
    // 字符串的排列
    vector<string> permutation(string s);
    // Excel表列名称 2021.6.29
    string convertToTitle(int columnNumber);
    // 传递信息
    int numWays(int n, vector<vector<int>>& relation, int k);
    // 根据字符出现频率排序
    string frequencySort(string s);
    // 计数质数
    int countPrimes(int n);
    // 和相同的二元子数组
    int numSubarraysWithSum(vector<int>& nums, int goal);
    // 主要元素
    int majorityElement(vector<int>& nums);
    // 连接词
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words);
    // 天际线问题
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings);
    // 绝对差值和
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2);
    // 最长回文串
    int longestPalindrome(string s);
    // 最高频元素的频数
    int maxFrequency(vector<int>& nums, int k);
    // 检查是否区域内所有整数都被覆盖
    bool isCovered(vector<vector<int>>& ranges, int left, int right);
};

#endif //ASYC_SOLUTION_H
