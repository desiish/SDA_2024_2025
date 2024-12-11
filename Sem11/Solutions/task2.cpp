class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        unordered_map<int, vector<int>> bmap, rmap;

        for(auto& edge : redEdges)
        {
            rmap[edge[0]].push_back(edge[1]);
        }
        
        for(auto& edge : blueEdges)
        {
            bmap[edge[0]].push_back(edge[1]);
        }

        vector<bool> rvisited(n), bvisited(n);
        vector<int> res(n, INT_MAX);

        queue<pair<int, char>> q;
        q.push({0, '#'});

        int steps = 0;
        while(!q.empty())
        {
            int size = q.size();

            for(int i = 0; i < size; i++)
            {
                auto p = q.front();
                q.pop();

                res[p.first] = min(res[p.first], steps);
                if(p.second == '#')
                {
                    for(int j = 0; j < rmap[p.first].size(); j++)
                    {
                        auto v = rmap[p.first][j];
                        if(!rvisited[v])
                        {
                            q.push({v, 'r'});
                            rvisited[v] = true;
                        }
                    }
                    for(int j = 0; j < bmap[p.first].size(); j++)
                    {
                        auto v = bmap[p.first][j];
                        if(!bvisited[v])
                        {
                            q.push({v, 'b'});
                            bvisited[v] = true;
                        }
                    }
                }

                else if(p.second == 'r')
                {
                    for(int j = 0; j < bmap[p.first].size(); j++)
                    {
                        auto v = bmap[p.first][j];
                        if(!bvisited[v])
                        {
                            q.push({v, 'b'});
                            bvisited[v] = true;
                        }
                    }
                }

                else
                {
                    for(int j = 0; j < rmap[p.first].size(); j++)
                    {
                        auto v = rmap[p.first][j];
                        if(!rvisited[v])
                        {
                            q.push({v, 'r'});
                            rvisited[v] = true;
                        }
                    }                
                }
            }

            steps++;
        }

        for(int i = 0; i < res.size(); i++)
        {
            if(res[i] == INT_MAX)
                res[i] = -1;
        }

        return res;
    }
};
