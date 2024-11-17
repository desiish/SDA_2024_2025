#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode
{
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    unsigned int leftCount = 0;
    unsigned int rightCount = 0;

    unsigned int value;
};

const size_t MAX_NODES = 1e6;
TreeNode nodes[MAX_NODES];

void fillCounts(TreeNode* root)
{
    if (root->left == nullptr)
    {
        root->leftCount = 0;
    }
    else
    {
        fillCounts(root->left);
        root->leftCount = root->left->leftCount + root->left->rightCount + 1;
    }

    if (root->right == nullptr)
    {
        root->rightCount = 0;
    }
    else
    {
        fillCounts(root->right);
        root->rightCount = root->right->leftCount + root->right->rightCount + 1;
    }
}

long long getMaxScore(TreeNode* root, long long upperCounts)
{
    long long currCounts = 1;

    if (upperCounts != 0)
    {
        currCounts *= upperCounts;
    }

    if (root->leftCount != 0)
    {
        currCounts *= root->leftCount;
    }

    if (root->rightCount != 0)
    {
        currCounts *= root->rightCount;
    }

    if (root->left != nullptr)
    {
        currCounts = max(currCounts, getMaxScore(root->left, upperCounts + 1 + root->rightCount));
    }

    if (root->right != nullptr)
    {
        currCounts = max(currCounts, getMaxScore(root->right, upperCounts + 1 + root->leftCount));
    }

    return currCounts;
}

long long getMaxScore(TreeNode* root)
{
    if (root == nullptr || (root->leftCount + root->rightCount) == 0)
    {
        return 0;
    }

    return getMaxScore(root, 0);
}


int main()
{
    size_t count = 0;
    cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        int left, right;
        cin >> left >> right;

        nodes[i].value = i;

        if (left != -1)
        {
            nodes[i].left = &nodes[left];
        }

        if (right != -1)
        {
            nodes[i].right = &nodes[right];
        }
    }

    fillCounts(&nodes[0]);

    cout << getMaxScore(&nodes[0]);
}