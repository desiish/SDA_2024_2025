class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        using p = pair<int, int>; 
        vector<vector<p>> adj(n + 1);

        for(auto& edge : times)
        {
            adj[edge[0]].push_back({edge[1], edge[2]});
            //adj[edge[0]].emplace_back(edge[1], edge[2]);
        }

        priority_queue<p, vector<p>, greater<p>> pq;
        vector<bool> visited(n + 1, false);
        vector<int> dists(n + 1, INT_MAX);

        dists[k] = 0;
        pq.push({0, k});

        while(!pq.empty())
        {
            auto curr = pq.top();
            pq.pop();

            if(visited[curr.second]) 
                continue;

            visited[curr.second] = true;

            for(auto& edge : adj[curr.second])
            {
                if(dists[edge.first] > dists[curr.second] + edge.second)
                {
                    dists[edge.first] = dists[curr.second] + edge.second;
                    pq.push({dists[edge.first], edge.first});
                }
            }
        }

        int ans = *(max_element(dists.begin() + 1, dists.end()));
        if(ans == INT_MAX) 
            return -1;

        return ans;
    }
};
