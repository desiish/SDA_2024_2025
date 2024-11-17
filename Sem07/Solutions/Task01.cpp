class Solution {
public:
    int maxDepth(const TreeNode* root) {
        if(!root) 
            return 0;
        int maxDepthLeft = maxDepth(root->left);
        int maxDepthRight = maxDepth(root->right);
        return max(maxDepthLeft, maxDepthRight) + 1;
    }
};