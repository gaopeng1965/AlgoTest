/******************************************************************************
 * Author      : Gao Peng
 * CreateDate  : 2021/7/29 0:33
 * Modify      : 2021/7/29
 * Version     : 1.0
 * Description : 二叉树为主的题目
 ******************************************************************************/

#include "Solution.h"

namespace BinaryTree{
    /**************************************************************************/
    // 二叉树中所有距离为 K 的结点
    // idea1: 哈希表创建图(邻接表结构，信息为当前节点的父节点),dfs的时候注意上层/下层避免重复遍历.
    class Solution2distanceK1 {
    private:
        vector<int> m_res;
        int m_k;
        // 因为题目说值唯一
        unordered_map<int,TreeNode*> parents;
        void createAdList(TreeNode* root){
            if(!root) return;
            if(root->left){
                parents[root->left->val] = root;
                createAdList(root->left);
            }
            if(root->right){
                parents[root->right->val] = root;
                createAdList(root->right);
            }
        }
        // 往下找和往上找
        void dfs(TreeNode* node, int depth, TreeNode* lastNode){
            if(!node) return;
            if(depth == m_k){
                m_res.emplace_back(node->val);
                return;
            }
            if(node->left != lastNode) dfs(node->left, depth + 1, node);
            if(node->right != lastNode) dfs(node->right, depth + 1, node);
            if(parents[node->val] != lastNode) dfs(parents[node->val], depth + 1, node);
        }
    public:
        vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
            if(k == 0)
                return {target->val};
            createAdList(root);
            m_k = k;
            dfs(target, 0, nullptr);
            return m_res;
        }
    };
    // idea2: 将二叉树变换为以target为父节点的二叉树,再dfs.
    class Solution2distanceK2 {
    private:
        int m_distance;
        vector<int> res;
        TreeNode* m_tar;
        void dfs(TreeNode* node,int dis){
            if(!node)
                return;
            if(dis == m_distance){
                res.emplace_back(node->val);
                return;
            }
            dfs(node->left,dis + 1);
            dfs(node->right,dis + 1);
        }
        // root二叉树变换为以target为父节点,很不错的递归思路
        bool rootChanged(TreeNode* node){
            if(!node) return false;
            if(node == m_tar) return true;
            if(rootChanged(node->left)){
                if(!node->left->left)
                    node->left->left = node;
                else if(!node->left->right)
                    node->left->right = node;
                node->left = nullptr;
                return true;
            }else if(rootChanged(node->right)){
                if(!node->right->left)
                    node->right->left = node;
                else if(!node->right->right)
                    node->right->right = node;
                node->right = nullptr;
                return true;
            }
            return false;
        }
    public:
        vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
            if(k == 0)
                return {target->val};
            m_distance = k;
            m_tar = target;
            dfs(target,0);
            if(root != target){
                target->left = nullptr;
                target->right = nullptr;
                rootChanged(root);
                dfs(target,0);
            }
            return res;
        }
    };

}