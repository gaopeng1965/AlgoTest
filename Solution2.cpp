/******************************************************************************
 * Description : leetcode website algorithm to practice 2
 * Author      : Gao Peng
 * Date        : 2020-7-23
 * modify      : 2021-3-12
 * version     : 1.0
 ******************************************************************************/
#include "Solution.h"

// 测试用例
//FizzBuzz fb(15);
//thread th[4];
//function<void()> printFizz = []{cout << "fizz ";};
//function<void()> printBuzz = []{cout << "buzz ";};
//function<void()> printFizzBuzz = []{cout << "fizzbuzz ";};
//function<void(int)> printNum = [](int x){cout << x << " ";};

//th[0] = thread(&FizzBuzz::fizz,&fb,printFizz);
//th[1] = thread(&FizzBuzz::buzz,&fb,printBuzz);
//th[2] = thread(&FizzBuzz::fizzbuzz,&fb,printFizzBuzz);
//th[3] = thread(&FizzBuzz::number,&fb,printNum);
//for(auto &t:th) {
//    if(t.joinable())
//        t.join();
//}
class FizzBuzz {
private:
    int n;
    int cur;
    sem_t sem_fizz;
    sem_t sem_buzz;
    sem_t sem_fizz_buzz;
    sem_t sem_num;

public:
    FizzBuzz(int n) {
        this->n = n;
        cur = 0;
        sem_init(&sem_fizz, 0, 0);
        sem_init(&sem_buzz, 0, 0);
        sem_init(&sem_fizz_buzz, 0, 0);
        sem_init(&sem_num, 0, 1);
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while (cur <= n) {
            sem_wait(&sem_fizz);
            if (cur > n) break;
            printFizz();
            sem_post(&sem_num);
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while (cur <= n) {
            sem_wait(&sem_buzz);
            if (cur > n) break;
            printBuzz();
            sem_post(&sem_num);
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz) {
        while (cur <= n) {
            sem_wait(&sem_fizz_buzz);
            if (cur > n) break;
            printFizzBuzz();
            sem_post(&sem_num);
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while (cur <= n) {
            sem_wait(&sem_num);
            if (++cur > n) break;
            if (cur % 3 == 0 && cur % 5 == 0) {
                sem_post(&sem_fizz_buzz);
            } else if (cur % 3 == 0) {
                sem_post(&sem_fizz);
            } else if (cur % 5 == 0) {
                sem_post(&sem_buzz);
            } else {
                printNumber(cur);
                sem_post(&sem_num);
            }
        }

        // 以下三个post通过更新sem_fizz等信号量，调动其他线程运行，进而结束所有线程
        sem_post(&sem_fizz);
        sem_post(&sem_buzz);
        sem_post(&sem_fizz_buzz);
    }
};

// 使数组唯一的最小增量
int Solution::minIncrementForUnique(vector<int> &A) {
    /*
     * 排序后遍历
     */
    /*
    uint n = A.size();
    if(!n)
        return 0;
    std::sort(A.begin(),A.end());
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        if(A[i] >= A[i+1]){
            int t = A[i+1];
            A[i+1] = A[i]+1;
            ans += A[i+1] - t;
        }
    }
    return ans;
     */

    /*
     * 不排序,
     */
    uint n = A.size();
    if (!n)
        return 0;
    int index = 40000;
    int multi[index + 1];
    int ans = 0;
    std::fill(multi, multi + index + 1, 0);
    for (int i = 0; i < n; ++i) {
        ++multi[A[i]];
    }
    for (int i = 0; i < index; ++i) {
        if (multi[i] > 1) {
            ans += multi[i] - 1;
            multi[i + 1] += multi[i] - 1;
        }
    }
    if (multi[index] > 1) {
        ans = ans + multi[index] * (multi[index] - 1) / 2;
    }
    return ans;
}

// 反转字符串 2
string Solution::reverseStr(string s, int k) {
    int max = s.size() / (2 * k);
    int mod = s.size() % (2 * k);
    bool reverse_all = false;
    if (mod < k)
        reverse_all = true;
    for (int i = 0; i < max; ++i) {

    }
}

// 递增子序列
vector<vector<int>> Solution::findSubsequences(vector<int> &nums) {
    int n = nums.size();
    if (n < 2)
        return {};
    vector<vector<int>> res;
    vector<int> res_one;
    function<void(int)> dfs = [&](int idx) {
        if (res_one.size() > 1)
            res.emplace_back(res_one);
        int mul = -101;
        for (int i = idx; i < n; ++i) {
            if (res_one.empty() || res_one.back() <= nums[i]) {
                if (nums[i] == mul)
                    continue;
                res_one.emplace_back(nums[i]);
                mul = nums[i];
                dfs(i + 1);
                res_one.pop_back();
            }
        }
    };
    dfs(0);
    return res;
}

// leetcode -> cdelotee
string Solution::sortString(string s) {
    /*
     * int alpha[26] = {1}；
     * 这种形式会直接初始化第一个元素为1，后续元素默认初始化为0
     */
    int alpha[26] = {0};
    //std::fill(alpha, alpha + 26, 0);
    for (int i = 0; i < s.size(); ++i) {
        int tmp = s[i] - 'a';
        ++alpha[tmp];
    }
    int count = 0;
    string ans;
    while (count < s.size()) {
        for (int i = 0; i < 26; ++i) {
            if (alpha[i] > 0) {
                --alpha[i];
                char tmp = 'a' + i;
                ans += tmp;
                ++count;
            }
        }
        for (int i = 25; i >= 0; --i) {
            if (alpha[i] > 0) {
                --alpha[i];
                char tmp = 'a' + i;
                ans += tmp;
                ++count;
            }
        }
    }
    return ans;
}

// 每个元音包含偶数次的最长子字符串
int Solution::findTheLongestSubstring(string s) {
    map<char, vector<int>> yuan_yin;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
            yuan_yin[s[i]].emplace_back(i);
    }

}

// 口算难题(未完成)
bool Solution::isSolvable(vector<string> &words, string result) {
    // 前导不能为0
    std::unordered_set<char> not_zero;
    for (auto &t:words)
        not_zero.emplace(t[0]);

    // 字母-数字映射
    std::unordered_map<char, int> rules;
    std::list<int> list_int;
    for (int i = 0; i < 10; ++i) {
        list_int.emplace_back(i);
    }
    for (int i = 0; i < words.size(); ++i) {
        for (int j = 0; j < words[i].size(); ++j) {
            rules.emplace(words[i][j], -1);
        }
    }
//    for (auto &t:rules) {
//        if(not_zero.find(t.first) == not_zero.end()){
//            t.second = list_int.front();
//            list_int.erase(list_int.begin());
//        }
//    }


}

// 灯泡开关IV
int Solution::minFlips(string target) {
    const size_t n = target.size();
    vector<size_t> light(n, 0);
    int count_turn = 0;
    for (int i = 0; i < n; ++i) {
        if ((count_turn + (target[i] - '0')) % 2) {
            ++count_turn;
        }
    }
    return count_turn;
}

// 回文子串
int Solution::countSubstrings(string s) {
    int n = s.size();
    int res = 0;
    for (int i = 0; i < 2 * n - 1; ++i) {
        int left = i / 2;
        int right = left + i % 2;
        while (left >= 0 && right < n && s[left] == s[right]) {
            ++res;
            ++right;
            --left;
        }
    }
    return res;
}

// 删除子文件夹
vector<string> Solution::removeSubfolders(vector<string> &folder) {
    sort(folder.begin(), folder.end());
    vector<string> res;
    res.emplace_back(folder[0]);
    for (int i = 1; i < folder.size(); ++i) {
        if (folder[i].substr(0, res.back().size() + 1) != res.back() + '/')
            res.emplace_back(folder[i]);
    }
    return res;
}

// 扫雷游戏
vector<vector<char>> Solution::updateBoard(vector<vector<char>> &board, vector<int> &click) {

    vector<std::pair<int, int>> circum = {{-1, -1},
                                          {-1, 0},
                                          {0,  -1},
                                          {0,  1},
                                          {1,  0},
                                          {1,  1},
                                          {-1, 1},
                                          {1,  -1}};
    std::function<void(int, int)> dfs = [&](int x, int y) {
        int mine_num = 0;
        for (auto &t:circum) {
            int x_circum = x + t.first;
            int y_circum = y + t.second;
            if (x_circum < 0 || y_circum < 0 || x_circum >= board.size() || y_circum >= board[0].size())
                continue;
            mine_num += board[x_circum][y_circum] == 'M';
        }
        if (mine_num)
            //周边有炸弹
            board[x][y] = mine_num + '0';
        else {
            //周边无炸弹
            board[x][y] = 'B';
            for (auto &t:circum) {
                int x_circum = x + t.first;
                int y_circum = y + t.second;
                if (x_circum < 0 || y_circum < 0 || x_circum >= board.size() || y_circum >= board[0].size() ||
                    board[x_circum][y_circum] != 'E')
                    continue;
                //递归周边的格子
                dfs(x_circum, y_circum);
            }
        }
    };
    //click为炸弹
    if (board[click[0]][click[1]] == 'M')
        board[click[0]][click[1]] = 'X';
    else
        dfs(click[0], click[1]);
    return board;
}

// 最长快乐前缀(字符串hash)
string Solution::longestPrefix(string s) {
    if (s.size() < 2)
        return "";
    typedef unsigned long long ull;
    ull mod = 1000000007;
    int base = 131;
    ull prefix = 0, suffix = 0, power = 1;
    int index = 0;
    for (int i = 1; i < s.size(); ++i) {
        prefix = (prefix * base + s[i - 1] - 'a') % mod;
        /*
         * 为了降低幂次运算时间，保存上一轮的幂次结果
         */
        // suffix = (suffix + (s[s.size() - i] - 'a')*(ull)pow(base,i-1)) % mod;
        suffix = (suffix + (s[s.size() - i] - 'a') * power) % mod;
        if (prefix == suffix)
            index = i;
        power = power * base % mod;
    }
    return s.substr(0, index);
}

// 位运算加法
int Solution::addBit(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a ^= b;
        b = carry;
    }
    return a;
}

// 钥匙和房间(BFS/DFS)
bool Solution::canVisitAllRooms(vector<vector<int>> &rooms) {
    // 自己写的很low，其实是BFS的原理
    int n = rooms.size();
    char status[n];
    std::fill(status, status + n, 0);
    status[0] = 1;
    --n;
    vector<int> all;
    all.emplace_back(0);
    for (int i = 0; i < all.size(); ++i) {
        int k = all[i];
        if (status[k] != 1)
            continue;
        for (int j = 0; j < rooms[k].size(); ++j) {
            switch (status[rooms[k][j]]) {
                case 0: {
                    ++status[rooms[k][j]];
                    all.emplace_back(rooms[k][j]);
                    --n;
                    break;
                }
                case 1: {
                    break;
                }
            }
        }
        ++status[k];
        if (!n)
            return true;
    }
    return false;
}

// 最短回文串(字符串hash/KMP)
string Solution::shortestPalindrome(string s) {

}

// 表示数值的字符串
bool Solution::isNumber(string s) {
    // (?i)会提示异常括号
    // (?i)[+-]?(\d+|\d*\.\d*)(e[+-]?\d+)?
    // ?: 不存储中间结果
    std::regex reg("[+-]?(?:\\d+\\.?\\d*|\\.\\d+)(?:[eE][+-]?\\d+)?");
    return std::regex_match(s,reg);
}

// 寻找峰值
int Solution::findPeakElement(vector<int> &nums) {

}

// N皇后
vector<vector<string>> Solution::solveNQueens(int n) {
    if (!n)
        return {};
    vector<vector<string>> res;
    vector<string> res_one(n, string(n, '.'));
    int cols[64] = {0};
    int ldia[64] = {0};
    int rdia[64] = {0};

    function<void(int, int)> queenBackTrack = [&](int row, int n) {
        if (row == n) {
            res.emplace_back(res_one);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!cols[i] && !ldia[row - i + n] && !rdia[row + i]) {
                res_one[row][i] = 'Q';
                cols[i] = ldia[row - i + n] = rdia[row + i] = 1;
                queenBackTrack(row + 1, n);
                res_one[row][i] = '.';
                cols[i] = ldia[row - i + n] = rdia[row + i] = 0;
            }
        }
    };
    queenBackTrack(0, n);
    return res;
}

// N皇后(只求解数量，用位运算)
int Solution::totalNQueens(int n) {
    if (!n)
        return 0;
    int mask = (1 << n) - 1;
    int res = 0;
    function<void(int, int, int, int)> queenBackTrack = [&](int row, int col, int left, int right) {
        if (row == n) {
            ++res;
            return;
        }
        int bitmap = mask & ~(col | left | right);
        while (bitmap) {
            int pos = bitmap & -bitmap;
            bitmap ^= pos;
            queenBackTrack(row + 1, (col | pos), (left | pos) << 1, (right | pos) >> 1);
        }
    };
    queenBackTrack(0, 0, 0, 0);
    return res;
}

// 前K个高频元素
vector<int> Solution::topKFrequent(vector<int> &nums, int k) {
    auto cmp = [](pair<int, int> &x, pair<int, int> &y) {
        return x.second > y.second;
    };
    unordered_map<int, int> count_map;
    for (int i = 0; i < nums.size(); ++i)
        ++count_map[nums[i]];
    priority_queue<pair<int, int>, vector<pair<int, int >>, decltype(cmp)> s_heap(cmp);
    auto it = count_map.begin();
    vector<int> res;
    for (auto it = count_map.begin(); it != count_map.end(); ++it) {
        if (s_heap.size() < k)
            s_heap.push(*it);
        else {
            if (s_heap.top().second < it->second) {
                s_heap.pop();
                s_heap.push(*it);
            }
        }
    }
    while (!s_heap.empty()) {
        res.emplace_back(s_heap.top().first);
        s_heap.pop();
    }
    return res;
}

// 组合
vector<vector<int>> Solution::combine(int n, int k) {
    if (k > n)
        return {};
    vector<vector<int>> res;
    vector<int> single_res;
    function<void(int, int)> dfs = [&](int m, int index) {
        if (single_res.size() == k) {
            res.emplace_back(single_res);
            return;
        }
        const int idx = index;
        for (int i = index; i < n - k + 1; ++i) {
            single_res.emplace_back(i + m - idx);
            dfs(i - idx + m + 1, index);
            single_res.pop_back();
            ++index;
        }
    };
    dfs(1, 0);
    return res;
}

// 子集
vector<vector<int>> Solution::subsets(vector<int> &nums) {
    int n = nums.size();
    if (!n)
        return {{}};
    vector<vector<int>> res;
    vector<int> single_res;
    function<void(int)> dfs = [&](int idx) {
        for (int i = idx; i < n; ++i) {
            single_res.emplace_back(nums[i]);
            res.emplace_back(single_res);
            dfs(i + 1);
            single_res.pop_back();
        }
    };
    dfs(0);
    res.emplace_back(vector<int>());
    return res;
}

// 组合总和
vector<vector<int>> Solution::combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> res_one;
    int n = candidates.size();
    function<void(int, int)> dfs = [&](int index, int target_now) {
        if (target_now < 0)
            return;
        else if (!target_now) {
            res.emplace_back(res_one);
            return;
        }
        for (int i = index; i < n; ++i) {
            res_one.emplace_back(candidates[i]);
            dfs(i, target_now - candidates[i]);
            res_one.pop_back();
        }
    };
    dfs(0, target);
    return res;
}

// 和为s的两个数字
vector<int> Solution::twoSum(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    int i = 0, j = left;
    while (i < j) {
        int tmp = nums[i] + nums[j];
        if (tmp > target)
            --j;
        else if (tmp == target)
            return {nums[i], nums[j]};
        else
            ++i;
    }
    return {};
}

// 组合总和 Ⅱ(结果需要去重，set不能用，因为结果可能是元素相同，排列不同)
vector<vector<int>> Solution::combinationSum2(vector<int> &candidates, int target) {
    // 排序后循环稍作处理即可
    std::sort(candidates.begin(), candidates.end());
    int n = candidates.size();
    vector<vector<int>> res;
    vector<int> res_one;
    function<void(int, int)> dfs = [&](int index, int target_now) {
        if (target_now < 0)
            return;
        else if (target_now == 0) {
            res.emplace_back(res_one);
            return;
        }
        for (int i = index; i < n; ++i) {
            int tmp = candidates[i];
            // 屏蔽同层递归的相同元素
            if (i > index && tmp == candidates[i - 1])
                continue;
            res_one.emplace_back(tmp);
            dfs(i + 1, target_now - tmp);
            res_one.pop_back();
        }
    };
    dfs(0, target);
    return res;
}

// 最长回文子串
string Solution::longestSubPalindrome(string s) {
    int n = s.size();
    if (n < 2)
        return s;
    auto extendFromMid = [&](int left, int right) -> string {
        while (left >= 0 && right < n && s[left] == s[right]) {
            --left;
            ++right;
        }
        return s.substr(left + 1, right - left - 1);
    };

    string res;
    int max_size = 0;
    for (int i = 0; i < n - 1; ++i) {
        string str1 = extendFromMid(i, i);
        string str2 = extendFromMid(i, i + 1);
        string max_str = str1.size() > str2.size() ? str1 : str2;
        if (max_str.size() > max_size) {
            max_size = max_str.size();
            res = max_str;
        }
    }
    return res;
}

// 组合总和 Ⅲ
vector<vector<int>> Solution::combinationSum3(int k, int n) {
    vector<vector<int>> res;
    vector<int> res_one;
    function<void(int, int, int)> dfs = [&](int index, int k_now, int n_now) {
        if (k_now == k && n_now == 0) {
            res.emplace_back(res_one);
            return;
        } else if (k_now >= k || n_now < 0)
            return;
        for (int i = index; i < 10; ++i) {
            res_one.emplace_back(i);
            dfs(i + 1, k_now + 1, n_now - i);
            res_one.pop_back();
        }
    };
    dfs(1, 0, n);
    return res;
}

// 分数到小数
string Solution::fractionToDecimal(int numerator, int denominator) {
    if (denominator == 0)
        return "";
    string res;
    long long int_part = ((long long) numerator / (long long) denominator);
    long long remainder_part = abs(((long long) numerator % (long long) denominator));
    res = to_string(int_part);

    if (remainder_part != 0) {
        if (int_part == 0 && ((numerator & INT32_MIN) ^ (denominator & INT32_MIN)))
            res = "-0";
        res += ".";
    } else
        return res;

    denominator = abs(denominator);
    // remainder 余数
    // <余数，下标>
    unordered_map<int, int> remainder_umap;
    // decimals 小数
    vector<int> decimals_vec;
    remainder_umap.emplace(remainder_part, 0);
    int index = 0;
    while (1) {
        remainder_part *= 10;
        int_part = remainder_part / denominator;
        remainder_part = remainder_part % denominator;
        decimals_vec.emplace_back(int_part);
        if (remainder_umap.find(remainder_part) != std::end(remainder_umap)) {
            auto tmp = remainder_umap.find(remainder_part);
            int loop_start = tmp->second;
            for (int i = 0; i < loop_start; ++i) {
                res += to_string(decimals_vec[i]);
            }
            if (remainder_part == 0)
                break;
            res += "(";
            for (int i = loop_start; i < decimals_vec.size(); ++i) {
                res += to_string(decimals_vec[i]);
            }
            res += ")";
            break;
        }
        remainder_umap.emplace(remainder_part, ++index);
    }
    return res;
}

// 解数独(类似N皇后，只不过更复杂)
void Solution::solveSudoku(vector<vector<char>> &board) {
    vector<std::bitset<9>> rows(9);
    vector<std::bitset<9>> cols(9);
    vector<std::bitset<9>> block(9);
    int index_count = 0;
    vector<pair<int, int>> index;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] != '.') {
                rows[i][board[i][j] - '1'] = 1;
                cols[j][board[i][j] - '1'] = 1;
                block[i / 3 * 3 + j / 3][board[i][j] - '1'] = 1;
            } else {
                ++index_count;
                index.emplace_back(i, j);
            }
        }
    }
    function<int(int)> dfs = [&](int idx) -> int {
        if (idx == index_count)
            return 0;
        int row = index[idx].first;
        int col = index[idx].second;
        int blk_idx = row / 3 * 3 + col / 3;
        std::bitset<9> tmp = rows[row] | cols[col] | block[blk_idx];
        if (tmp == std::bitset<9>().set())
            return -1;
        for (int i = 0; i < 9; ++i) {
            if (tmp[i] == 0) {
                board[row][col] = i + '1';
                rows[row][i] = cols[col][i] = block[blk_idx][i] = 1;
                if (dfs(idx + 1) == 0)
                    return 0;
                rows[row][i] = cols[col][i] = block[blk_idx][i] = 0;
                board[row][col] = '.';
            }
        }
    };
    dfs(0);
}

// 单词搜索
bool Solution::exist(vector<vector<char>> &board, string word) {
    int row = board.size();
    int col = board[0].size();
    int n = word.size();
    if (row * col < n)
        return false;
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    std::pair<int, int> pos[4] = {{1,  0},
                                  {0,  1},
                                  {-1, 0},
                                  {0,  -1}};
    function<bool(int, int, int)> findPos = [&](int i, int j, int idx) -> bool {
        if (idx == n)
            return true;
        int x, y;
        for (int k = 0; k < 4; ++k) {
            x = i + pos[k].first;
            y = j + pos[k].second;
            if (x < 0 || y < 0 || x >= row || y >= col)
                continue;
            if (!visited[x][y] && board[x][y] == word[idx]) {
                visited[x][y] = true;
                if (findPos(x, y, idx + 1))
                    return true;
                visited[x][y] = false;
            }
        }
        return false;
    };
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (board[i][j] == word[0]) {
                visited[i][j] = true;
                if (findPos(i, j, 1))
                    return true;
                visited[i][j] = false;
            }
        }
    }
    return false;
}

// 强密码检测器
int Solution::strongPasswordChecker(string s) {
    return 0;
}

//  全排列 Ⅱ
vector<vector<int>> Solution::permuteUnique(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> res_one;
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    /*
     * 标准库竟然有全排列的函数，使用前先排序。
     */
//    do{
//        res.emplace_back(nums);
//    }while(std::next_permutation(nums.begin(),nums.end()));

    vector<bool> visited(n, false);
    function<void()> dfs = [&]() {
        if (res_one.size() == n) {
            res.emplace_back(res_one);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (visited[i] || (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]))
                continue;
            visited[i] = true;
            res_one.emplace_back(nums[i]);
            dfs();
            res_one.pop_back();
            visited[i] = false;
        }
    };
    dfs();
    return res;
}

// 计算器
int Solution::calculate(string s) {
    int res = 0;
    char op = '+';
    std::stringstream ss(s);
    int num;
    std::stack<int> stk_num;
    while (ss >> num) {
        if (op == '+')
            stk_num.push(num);
        else if (op == '-')
            stk_num.push(-num);
        else {
            int tmp = stk_num.top();
            stk_num.pop();
            if (op == '*')
                stk_num.push(tmp * num);
            else
                stk_num.push(tmp / num);
        }
        ss >> op;
    }
    while (!stk_num.empty()) {
        res += stk_num.top();
        stk_num.pop();
    }
    return res;
}

// 形成三的最大倍数
string Solution::largestMultipleOfThree(vector<int> &digits) {
    int count[10] = {0};
    int sum = 0;
    string res;
    for (int &i:digits) {
        ++count[i];
        sum += i;
    }

    auto findMod = [&](int x) {
        for (int i = x; i < 10; i += 3) {
            if (count[i] > 0) {
                --count[i];
                return true;
            }
        }
        bool is_twice = false;
        for (int i = 3 - x; i < 10; i += 3) {
            if (count[i] > 0) {
                --count[i];
                if (is_twice)
                    return true;
                if (count[i] > 0) {
                    --count[i];
                    return true;
                } else
                    is_twice = true;
            }
        }
        return false;
    };
    int mod = sum % 3;
    if (mod == 1 && !findMod(1))
        return "";
    else if (mod == 2 && !findMod(2))
        return "";
    for (int i = 9; i >= 0; --i) {
        if (count[i] != 0)
            res += string(count[i], '0' + i);
    }
    if (res.size() && res[0] == '0')
        return "0";
    return res;
}

// 和为K的最少斐波那契数字数目
int Solution::findMinFibonacciNumbers(int k) {
    // 贪心的证明属实妙哉
    // 官方：
    // 第一步：证明 我们不会选取连续两个斐波那契数。
    // 第二步：证明 我们不会选取同一个斐波那契数超过一次。
    // 第三步：证明我们需要的结论，即 对于任意给定的k，我们需要选择不超过k的最大斐波那契数。

    int a = 1, b = 1;
    vector<int> fib = {a, b};
    while (a + b <= k) {
        int tmp = a + b;
        fib.emplace_back(tmp);
        a = b;
        b = tmp;
    }
    int res = 1;
    k -= b;
    for (int i = fib.size() - 2; i >= 0; --i) {
        if (k == 0)
            break;
        if (k >= fib[i]) {
            ++res;
            k -= fib[i];
        }
    }
    return res;
}

// 秋叶收藏集
int Solution::minimumOperations(string leaves) {

}

// 分割等和子集
bool Solution::canPartition(vector<int> &nums) {
    int n = nums.size();
    if (n < 2)
        return false;
    // 计算累加和，初始值为0
    // 可以使用内置数组，STL容器，自定义类型数据数组(需要写第四个参数:回调函数)
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    int max_val = *std::max_element(nums.begin(), nums.end());
    //int sum = 0, max_val = INT32_MIN;
    for (int &t:nums) {
        sum += t;
        max_val = std::max(max_val, t);
    }
    if (sum & 1 || max_val > sum / 2)
        return false;
    /*
    vector<vector<bool>> dp(n,vector<bool>(sum/2+1,false));
    for (auto &t:dp) {
        t[0] = true;
    }
    dp[0][nums[0]] = true;
    for (int i = 1; i < n; ++i) {
        int num = nums[i];
        for (int j = 1; j <= sum/2; ++j) {
            if(j >= num)
                dp[i][j] = dp[i-1][j] | dp[i-1][j - num];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    */
    // dp优化
    vector<bool> dp(sum / 2 + 1, false);
    dp[0] = true;
    dp[nums[0]] = true;
    for (int i = 1; i < n; ++i) {
        for (int j = sum / 2; j > nums[i]; --j) {
            if (j >= nums[i])
                dp[j] = dp[j] | dp[j - nums[i]];
        }
    }
    return dp[sum / 2];
}

// 数组中第K大元素
int Solution::findKthLargest(vector<int> &nums, int k) {
    // K总是有效的
    int n = nums.size();
    int left = 0, right = n - 1;
    auto quickSort = [&](int l, int r) -> int {
        return 0;
    };

//    while(left < right){
//        int mid = quickSort(left,right);
//        if(mid == n - k + 1)
//            return nums[mid];
//        else if(mid > n - k + 1)
//            quickSort();
//    }
}

// 查找常用字符串
vector<string> Solution::commonChars(vector<string> &A) {
    vector<string> res;
    int n = A.size();
    if (!n)
        return res;
    unordered_map<char, int> common_umap;
    for (auto &t:A[0]) {
        ++common_umap[t];
    }
    for (int i = 1; i < A.size(); ++i) {
        unordered_map<char, int> tmp_umap;
        for (int j = 0; j < A[i].size(); ++j) {
            if (common_umap.find(A[i][j]) != common_umap.end()) {
                ++tmp_umap[A[i][j]];
            }
        }
        for (auto &t:tmp_umap) {
            t.second = std::min(t.second, common_umap[t.first]);
        }
        common_umap = std::move(tmp_umap);
    }
    for (auto &t:common_umap) {
        for (int i = 0; i < t.second; ++i)
            res.emplace_back(string(1, t.first));
    }
    return res;
}

// 划分字母区间
vector<int> Solution::partitionLabels(string S) {
    int n = S.size();
    int last[26] = {0};
    for (int i = 0; i < n; ++i) {
        last[S[i] - 'a'] = i;
    }
    vector<int> res;
    int start = 0, end = 0;
    for (int i = 0; i < n; ++i) {
        end = std::max(end, last[S[i] - 'a']);
        if (i == end) {
            res.emplace_back(i - start + 1);
            start = end + 1;
        }
    }
    return res;
}

// 数组中的最长山脉
int Solution::longestMountain(vector<int> &A) {
    int n = A.size();
    if (n < 3)
        return 0;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] > A[i - 1]) {}
    }
}

// 单词拆分 Ⅱ
vector<string> Solution::wordBreak2(string s, vector<string> &wordDict) {
    if (!wordBreak(s, wordDict))
        return {};
    int n = s.size();
    vector<string> ans;
    unordered_set<string> dict;
    for (string &t:wordDict)
        dict.emplace(t);
    function<void(string, string)> dfs = [&](string s_right, string ans_one) {
        string str;
        for (int i = 0; i < s_right.size(); ++i) {
            str += s_right[i];
            if (dict.find(str) != dict.end()) {
                string ans_;
                if (ans_one.empty())
                    ans_ = str;
                else
                    ans_ = ans_one + ' ' + str;
                if (i == s_right.size() - 1) {
                    ans.emplace_back(ans_);
                }
                dfs(s_right.substr(i + 1), ans_);
            }
        }
    };
    dfs(s, "");
    return ans;
}

// 单词拆分
bool Solution::wordBreak(string s, vector<string> &wordDict) {
    /*
     * 此解法在特殊样例测试下会超时
     */
    /*
    unordered_set<string> wordSet;
    ulong minSize = ULONG_MAX,maxSize = 0;
    for (string& t:wordDict) {
        wordSet.emplace(t);
        minSize = std::min(minSize,t.size());
        maxSize = std::max(maxSize,t.size());
    }
    function<bool(string)> dfs = [&](string s_right){
        string str = s_right.substr(0,minSize-1);
        for (int i = minSize-1; i < maxSize; ++i) {
            str += s_right[i];
            if(wordSet.find(str) != wordSet.end()){
                if(i == s_right.size()-1)
                    return true;
                if(dfs(s_right.substr(i+1)))
                    return true;
            }
        }
        return false;
    };
    return dfs(s);
    */

    unordered_set<string> word_set(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1);
    dp[0] = true;
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && word_set.find(s.substr(j, i - j)) != word_set.end()) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.size()];
}

// 插入区间
vector<vector<int>> Solution::insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
    if (newInterval.back() < intervals[0][0]) {
        intervals.insert(intervals.begin(), newInterval);
        return intervals;
    }
    if (newInterval[0] > intervals.back().back()) {
        intervals.emplace_back(newInterval);
        return intervals;
    }
    for (int i = 0; i < intervals.size(); ++i) {
        if (newInterval[0] > intervals[i].back())
            continue;
        if (newInterval.back() < intervals[i][0])
            break;
        else {

        }
    }
}

// 根据数字二进制下1的数目排序
vector<int> Solution::sortByBits(vector<int> &arr) {
    map<int, std::multiset<int>> ans_map;
    std::bitset<32> bit;
    for (int &t:arr) {
        bit = t;
        ans_map[bit.count()].emplace(t);
    }
    vector<int> ans;
    for (auto &i:ans_map) {
        for (auto &j:i.second)
            ans.emplace_back(j);
    }
    return ans;
}

vector<vector<int>> Solution::kClosest(vector<vector<int>> &points, int K) {
//    int min_k = INT_MAX;
//    vector<vector<int>> res;
//    std::list<std::pair<int,int>> list_k;
//    list_k.push_back({0,pow(points[0][0],2) + pow(points[0][1],2)});
//    for(int i = 1;i < points.size(); ++i){
//        int tmp = pow(points[i][0],2) + pow(points[i][1],2);
//        int nums = list_k.size();
//        if(nums < K){
//            for(auto it = list_k.begin();it != list_k.end(); ++it){
//                if(tmp < it->second) {
//                    list_k.insert(it, {i, tmp});
//                    break;
//                }
//            }
//            if(nums == list_k.size())
//                list_k.push_back({i,tmp});
//            continue;
//        }
//        if(tmp < list_k.back().second){
//            for(auto it = list_k.begin();it != list_k.end(); ++it){
//                if(tmp < it->second) {
//                    list_k.insert(it, {i, tmp});
//                    break;
//                }
//            }
//            list_k.pop_back();
//        }
//    }
//    for(auto& t:list_k)
//        res.emplace_back(points[t.first]);
//    return res;
    priority_queue<std::pair<int, int>> pq;
    vector<vector<int>> res;
    for (int i = 0; i < points.size(); ++i) {
        int value = pow(points[i][0], 2) + pow(points[i][1], 2);
        if (pq.size() < K) {
            pq.push({value, i});
            continue;
        }
        if (value < pq.top().first) {
            pq.pop();
            pq.push({value, i});
        }
    }
    while (!pq.empty()) {
        res.emplace_back(points[pq.top().second]);
        pq.pop();
    }
    return res;
}

// 自由之路
int Solution::findRotateSteps(string ring, string key) {

}

// 根据身高重建队列
vector<vector<int>> Solution::reconstructQueue(vector<vector<int>> &people) {
    /*
     * 关键是思路:排序(高度降序,k升序排列),然后遍历,插入位置k.
     * 思考:为什么位置k是符合要求的?
     */
    std::sort(people.begin(), people.end(), [](vector<int> &p1, vector<int> &p2) {
        if (p1[0] > p2[0] || (p1[0] == p2[0] && p1[1] < p2[1]))
            return true;
        else
            return false;
    });
    int n = people.size();
    std::list<vector<int>> res_list;
    for (int i = 0; i < n; ++i) {
        auto it = res_list.begin();
        std::advance(it, people[i][1]);
        res_list.insert(it, people[i]);
    }
    return vector<vector<int>>(res_list.begin(), res_list.end());
}

// 不同整数的最少数目
int Solution::findLeastNumOfUniqueInts(vector<int> &arr, int k) {
    unordered_map<int, int> arr_umap;
    for (int &t:arr) {
        arr_umap[t]++;
    }
    vector<int> arr1(arr.size(), 0);
    int max = 0;
    for (auto &t:arr_umap) {
        max = std::max(max, t.second);
        arr1[t.second - 1]++;
    }
    vector<int> arr2(arr1.begin(), arr1.begin() + max);
    for (auto &t:arr2)
        cout << t << ",";
    arr1.clear();
    arr1.shrink_to_fit();
    int remove = 0, arr2_size = arr2.size();
    int diff = arr_umap.size();
    for (int i = 0; i < arr2_size; ++i) {
        remove += arr2[i] * (i + 1);
        diff -= arr2[i];
        if (remove > k) {
            int tmp = (remove - k) / (i + 1);
            if ((remove - k) % (i + 1) > 0)
                tmp++;
            return diff + tmp;
        }
    }
    return 0;
}

// 距离顺序排列矩阵单元格
vector<vector<int>> Solution::allCellsDistOrder(int R, int C, int r0, int c0) {
    vector<vector<int>> res;
    map<int, vector<vector<int>>> distance;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            distance[abs(r0 - i) + abs(c0 - j)].emplace_back(vector<int>{i, j});
        }
    }
    for (auto &t:distance)
        res.insert(res.end(), t.second.begin(), t.second.end());
    return res;
}

// 加油站
int Solution::canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();
    /*
     * 暴力解法,时间复杂度O(n²)
     */
    /*
    for (int i = 0; i < n; ++i) {
        int rest_gas = gas[i];
        if(cost[i] > gas[i])
            continue;
        int j = 0;
        for (; j < n; ++j) {
            int idx = (i+j)%n;
            rest_gas -= cost[idx];
            if(rest_gas < 0)
                break;
            rest_gas += gas[(idx+1)%n];
        }
        if(j == n)
            return i;
    }
    return -1;
     */

    /*
     * 一次遍历即可,因为从开始出发到某一站无法到达时,这之间的任何一站作起点也是无法到达这一站的
     */
    int rest_gas = 0;
    int min = INT32_MAX;
    int start;
    for (int i = 0; i < gas.size(); ++i) {
        rest_gas += gas[i] - cost[i];
        if (rest_gas < min) {
            min = rest_gas;
            start = i;
        }
    }
    return rest_gas < 0 ? -1 : (start + 1) % gas.size();
}

// 重构字符串
string Solution::reorganizeString(string S){
    int n = S.size();
    int count[26] = {0};
    for (char& i:S) {
        count[i - 'a']++;
    }
    int max = 0;
    int maxIndex = 0;
    int maxCount = (n + 1) / 2;
    for (int i = 0; i < 26; ++i) {
        if(count[i] > maxCount)
            return "";
        if(max < count[i]){
            max = count[i];
            maxIndex = i;
        }
    }
    string res(n,' ');
    if(max == maxCount){
        for (int i = 0; i < n; i += 2) {
            res[i] = 'a' + maxIndex;
        }
        count[maxIndex] = 0;
    }
    int j = 0;
    for (int i = 1; i < n; i += 2) {
        while(count[j] == 0){
            ++j;
        }
        res[i] = 'a' + j;
        count[j]--;
    }
    for (int i = 0; i < n; i += 2) {
        while(count[j] == 0){
            ++j;
            if(j == 26)
                return res;
        }
        res[i] = 'a' + j;
        count[j]--;
    }
    return res;
}

// 将数组拆分成斐波那契序列
vector<int> Solution::splitIntoFibonacci(string S){
    int n = S.size();
    vector<int> res;
    auto str2num = [](string& s)->long{
        long val = 0;
        if(s.size() > 1 && s[0] == '0')
            return -1;
        for(int i = 0;i < s.size(); ++i){
            val = val*10 + s[i] - '0';
        }
        return val > INT32_MAX ? -1:val;
    };
    function<bool(int)> dfs = [&](int index)->bool{
        if(index == n)
            return res.size() >= 3;
        string numStr = "";
        for (int i = index; i < n; ++i) {
            numStr += S[i];
            long tmp1 = str2num(numStr);
            if(tmp1 == -1)
                break;
            res.emplace_back(std::move(tmp1));
            int k = res.size();
            if(k < 3){
                if(dfs(i + 1))
                    return true;
            }else{
                long tmp2 = (long)res[k-2] + (long)res[k-3];
                if(tmp2 < INT32_MAX && res[k-1] == tmp2) {
                    if(dfs(i + 1))
                        return true;
                }
            }
            res.pop_back();
        }
        return false;
    };
    dfs(0);
    return res;
}

// 找零
bool Solution::lemonadeChange(vector<int>& bills){
    map<int,int> extra = {{5,0},{10,0}};
    for(int i = 0;i < bills.size(); ++i){
        switch(bills[i]){
            case 5:
                ++extra[5];
                break;
            case 10:
                ++extra[10];
        }
        switch(bills[i] - 5){
            case 5:
                if(extra[5] > 0)
                    --extra[5];
                else
                    return false;
                break;
            case 15:
                if(extra[5] > 0 && extra[10] > 0) {
                    --extra[5];
                    --extra[10];
                } else if(extra[5] >= 3){
                    extra[5] -=3;
                } else
                    return false;
        }
    }
    return true;
}

// Dota2 参议院
string Solution::predictPartyVictory(string senate){
    int n = senate.size();
    std::queue<int> queueR,queueD;
    for(int i = 0;i < n; ++i){
        if(senate[i] == 'R')
            queueR.push(i);
        else
            queueD.push(i);
    }
    string res;
    while(!queueD.empty() && !queueR.empty()){
        if(queueD.front() < queueR.front())
            queueD.push(queueD.front() + n);
        else
            queueR.push(queueR.front() + n);
        queueD.pop();
        queueR.pop();
    }
    return queueD.empty() ? "Radiant" : "Dire";
}

// 字母异位词分组
vector<vector<string>> Solution::groupAnagrams(vector<string>& strs){
    int n = strs.size();
    vector<string> resSingle;
#define ALLBIT 27*5
    unordered_map<std::bitset<ALLBIT>,vector<string>> resMap;
    for (int i = 0; i < n; ++i) {
        std::bitset<ALLBIT> strBit;
        int strCount[26] = {0};
        for (int j = 0; j < strs[i].size(); ++j) {
            ++strCount[strs[i][j] - 'a'];
        }
        for (int j = 0; j < 26; ++j) {
            strBit |= strCount[j];
            strBit <<= 5;
        }
        resMap[strBit].emplace_back(strs[i]);
    }
    vector<vector<string>> res;
    for (auto& t:resMap)
        res.emplace_back(t.second);
    return res;
}

// 分发糖果
int Solution::candy(vector<int>& ratings){
    int n = ratings.size();
    int res = 0;
    vector<int> leftRule(n,1);
//    vector<int> rightRule(n,1);
    for(uint i = 1;i < n; ++i){
        if(ratings[i] > ratings[i-1])
            leftRule[i] = leftRule[i-1] + 1;
    }
    int right = 0;
    for(int i = n-1;i >= 0; --i){
        if(i < n-1 && ratings[i] > ratings[i+1])
            ++right;
        else
            right = 1;
        res += std::max(leftRule[i],right);
    }
//    for(uint i = 0;i < n; ++i)
//        res += std::max(leftRule[i],rightRule[i]);
    return res;
}

// 按要求补齐数组
int Solution::minPatches(vector<int>& nums, int n){
    int res = 0;
    uint range = 0;
    uint current = 1;
    int k = nums.size();
    uint i = 0;
    while(range < n){
        if(i >= k || nums[i] > current){
            ++res;
            range += current;
        }else{
            range += nums[i];
            ++i;
        }
        current = range + 1;
    }
    return res;
}

// 无重叠区间
int Solution::eraseOverlapIntervals(vector<vector<int>>& intervals){
    std::sort(intervals.begin(),intervals.end(),[](vector<int>& a,vector<int>& b){
            return a.back() <= b.back();
    });
    int res = 0;
    int j = 0;
    for(int i = 1;i < intervals.size(); ++i){
        if(intervals[i].at(0) < intervals[j].back())
            ++res;
        else
            j = i;
    }
    return res;
}

// 旋转数组
void Solution::rotate(vector<int>& nums, int k) {
    int n = nums.size();
    if(!n)
        return;
    for(int i = 0;i < k; ++i){
        int last = nums[0];
        for(int j = 0;j < n; ++j){
            int idx = (j + 1)%n;
            int tmp = nums[idx];
            nums[idx] = last;
            last = tmp;
        }
    }
}

// 尽可能使字符串相等
int Solution::equalSubstring(string s, string t, int maxCost){
    int left = 0,right = 0;
    int res = 0;
    int cost = 0;
    for (int i = 0; i < s.size(); ++i) {
        cost += abs(t[i] - s[i]);
        ++right;
        if(cost > maxCost){
            while(cost > maxCost){
                cost -= abs(t[left] - s[left]);
                ++left;
            }
        }
        res = std::max(res,right - left);
    }
    return res;
}