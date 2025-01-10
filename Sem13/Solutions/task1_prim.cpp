//using Prim
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        vector<bool> visited(points.size(), 0);

        pq.push({0, 0});
        int sum = 0;

        while(!pq.empty())
        {
            int dist = pq.top().first;
            int to = pq.top().second;

            pq.pop();

            if(!visited[to])
            {
                visited[to] = true;
                sum += dist;

                for(int adj = 0; adj < points.size(); adj++)
                {
                    if(!visited[adj])
                    {
                        int wt = abs(points[adj][0] - points[to][0])
                        + abs(points[adj][1] - points[to][1]);

                        pq.push({wt, adj});
                    }
                }
            }
        }

        return sum;
    }
};
