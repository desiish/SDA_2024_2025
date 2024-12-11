class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);

        for(auto& edge : prerequisites)
        {
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> res;
        vector<bool> visited(numCourses, false), pathVisited(numCourses, false);

        for(int i = 0; i < numCourses; i++)
        {
            if(!visited[i] && hasCycle(graph, visited, pathVisited, res, i))
                return {};
        }

        reverse(res.begin(), res.end());

        return res;
    }

private:
    bool hasCycle(const vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& pathVisited,
                  vector<int>& res, int node) {

        if(pathVisited[node])
        {
            return true;
        }
        if(visited[node])
        {
            return false;
        }

        visited[node] = true;
        pathVisited[node] = true;

        for(auto& adj : graph[node])
        {
            if(hasCycle(graph, visited, pathVisited, res, adj))
                return true;
        }

        pathVisited[node] = false;
        res.push_back(node);
        return false;
    }
};
