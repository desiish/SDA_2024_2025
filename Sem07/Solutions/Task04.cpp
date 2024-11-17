class Solution {
public:
    bool isValidBSTRec(const TreeNode* root, long min, long max) {
	    if (root == nullptr)
		    return true;

	    if (root->val <= min || root->val >= max)
		    return false;

	    return isValidBSTRec(root->left, min, root->val) 
            && isValidBSTRec(root->right, root->val, max);
    }

    bool isValidBST(const TreeNode* root) {
        return isValidBSTRec(root, LONG_MIN, LONG_MAX);
    }
};