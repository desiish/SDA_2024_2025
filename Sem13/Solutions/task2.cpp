#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct DJS
{
    vector<int> parent, size;
    
    int n;

    DJS(int n) : n(n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);

        for(int i = 0; i < n + 1; i++)
        {
            parent[i] = i;
        }
    }

    int my_find(int node)
    {
        if(node == parent[node]) 
        {
            return node;
        }

        return parent[node] = my_find(parent[node]);
    }

    bool my_union(int u, int v)
    {
        int p_u = my_find(u);
        int p_v = my_find(v);

        if(p_u == p_v)
        {
            return false;
        }

        if(size[p_u] > size[p_v])
        {
            parent[p_v] = p_u;
            size[p_u] += size[p_v];
        }
        else
        {
            parent[p_u] = p_v;
            size[p_v] += size[p_u];
        }
            
        n--;
        
        return true;
    }
    
    int get_comps() const
    {
        return n;
    }
};

int main() {
    int n;
    cin >> n;
    
    int u, v;
    DJS s(n);
    
    while(cin >> u >> v)
    {
        if(s.my_union(u, v))
        {
            cout << s.get_comps() << endl;
        }
        else
        {
            cout << s.get_comps() << " CYCLE FORMED!" << endl;
        }
    }
    return 0;
}
