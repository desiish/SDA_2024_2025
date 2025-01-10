#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <queue>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
constexpr ll MODULE = 1e9 + 7;

vector<vector<pll>> adj;

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n + 1);
    
    int from, to, w;
    for(int i = 0; i < m; i++)
    {
        cin >> from >> to >> w;
        adj[from].push_back({to, w});
    }
    
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<bool> visited(n + 1, false);
    vector<ll> dists(n + 1, LLONG_MAX);
    vector<ll> paths(n + 1, 0);
    
    int start = 1;
    int end = n;
    
    dists[start] = 0;
    paths[start] = 1;
    
    pq.push({0, start});
    
    while(!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();
        
        int f = curr.second;
                
        if(visited[f]) continue;
        
        visited[f] = true;
        
        for(auto& edge : adj[f])
        {
            if(dists[edge.first] > dists[f] + edge.second)
            {
                dists[edge.first] = dists[f] + edge.second;
                paths[edge.first] = paths[f];
                pq.push({dists[edge.first], edge.first});
            }
            else if(dists[edge.first] == dists[f] + edge.second)
            {
                (paths[edge.first] += paths[f]) %= (MODULE);
                pq.push({dists[edge.first], edge.first});

            }
        }
    }
    
    cout << (dists[end] == LLONG_MAX ? -1 : dists[end]) << " " << paths[end];
    return 0;
}
