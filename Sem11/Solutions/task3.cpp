#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& comps, int component, int curr)
{
    if(visited[curr])
        return;
    
    comps[curr] = component;
    visited[curr] = true; 
    
    for(auto& vertex : adj[curr])
    {
        dfs(adj, visited, comps, component, vertex);
    }
}

int main() {
    int v, e;
    cin >> v >> e;
    
    vector<vector<int>> adj(v + 1);
    vector<int> comps(v + 1);
    vector<bool> visited(v + 1, false); 
    
    for(int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    int component = 1;
    for(int i = 1; i <= v; i++)
    {
        if(!visited[i])
            dfs(adj, visited, comps, component++, i);
    }
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << (comps[u] == comps[v]) << " ";
    }
    return 0;
}
