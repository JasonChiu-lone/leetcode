/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        stack<TreeNode*> s;
        queue<TreeNode*> q;
        s.push(root);
        q.push(root);
        while(!q.empty()){
            TreeNode* tn = q.front();
            q.pop();
            if (tn->left){
                s.push(tn->left);
                q.push(tn->left);
            }
            if (tn->right){
                s.push(tn->right);
                q.push(tn->right);
            }
        }
        int ans = -10000001;
        while(!s.empty()){
            TreeNode* tn = s.top();
            s.pop();
            int leftval = 0;
            int rightval = 0;
            if (tn->left) leftval = tn->left->val;
            if (tn->right) rightval = tn->right->val;
            if (max(leftval, rightval) > 0){
                ans = max(ans, tn->val + max(leftval, rightval) + (min(leftval, rightval)>0)*min(leftval, rightval));
                tn->val += max(leftval, rightval);
            }
            else{
                ans = max(ans, tn->val);
            }
        }
        return ans;
    }
};