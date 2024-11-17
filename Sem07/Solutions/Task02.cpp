class Solution {
public:
     int minDepth(TreeNode* root) {
        if(root==nullptr)
            return 0;
        int minDepth=0;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int size = q.size();
            minDepth++;

            while(size--){
                TreeNode* cur = q.front();
                q.pop();
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
                if(cur->left == nullptr && cur->right == nullptr)
                    return minDepth;
            }
        }
        return minDepth;
    }
};