struct TreeNode
{
    vector<TreeNode*> children;
    unsigned int childrenCount = 0;
};

unsigned int fillChildren(TreeNode* root)
{
    root->childrenCount = root->children.size();
    
    unsigned int count = root->children.size();
    for (unsigned int i = 0; i < count; i++)
    {
        root->childrenCount += fillChildren(root->children[i]);
    }
    
    
    return root->childrenCount;
}

TreeNode nodes[1000000];

int main() {
    unsigned int count = 0;
    cin >> count;
    count--;
    for (unsigned int i = 0; i < count; i++)
    {
        unsigned int parent, child;
        cin >> parent >> child;
        
        nodes[parent].children.push_back(&nodes[child]);
    }
    
    fillChildren(&nodes[0]);
    
    count++;
    for (unsigned int i = 0; i < count; i++)
    {
        cout << nodes[i].childrenCount << ' ';
    }
}