/******************************************************************************
 * Author      : Gao Peng
 * CreateDate  : 2021/7/29 13:54
 * Modify      : 2021/7/29
 * Version     : 1.0
 * Description : 二叉树为主的题目
 ******************************************************************************/
#ifndef ASYC_BINARYTREE_H
#define ASYC_BINARYTREE_H

#include "Common.h"

namespace BinaryTree{
    // 二叉树中所有距离为 K 的结点
    // idea1: 哈希表创建图(邻接表结构，信息为当前节点的父节点),dfs的时候注意上层/下层避免重复遍历.
    class Solution2distanceK1{
    private:
        vector<int> m_res;
        int m_k;
        // 因为题目说值唯一
        unordered_map<int, TreeNode *> parents;
        void createAdList(TreeNode *root);
        // 往下找和往上找
        void dfs(TreeNode *node, int depth, TreeNode *lastNode);
    public:
        vector<int> distanceK(TreeNode *root, TreeNode *target, int k);
    };

    // idea2: 将二叉树变换为以target为父节点的二叉树,再dfs.
    class Solution2distanceK2{
    private:
        int m_distance;
        vector<int> res;
        TreeNode *m_tar;
        void dfs(TreeNode *node, int dis);
        // root二叉树变换为以target为父节点,很不错的递归思路
        bool rootChanged(TreeNode *node);
    public:
        vector<int> distanceK(TreeNode *root, TreeNode *target, int k);
    };

    // 二叉树寻路
    vector<int> pathInZigZagTree(int label);
}

#endif //ASYC_BINARYTREE_H


