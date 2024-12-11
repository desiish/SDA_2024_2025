#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<unordered_set<int>> &graph, int start, int vCount, vector<int>& dist) {
    vector<bool> isVisited(vCount, false);
    queue<int> q;
    q.push(start);
    isVisited[start] = true;
    int count = 1;
    int v = 1;

    while (!q.empty() && v < vCount) {
    
        for (int j = q.size(); j > 0; j--) {
            if (v == vCount) {
                break;
            }
            int curr = q.front();
            for (int i = 0; i < vCount; ++i) {
                if (graph[curr].find(i) == graph[curr].end() && !isVisited[i]) {
                    isVisited[i] = true;
                    dist[i] = count;
                    q.push(i);
                    v++;
                }
            }
            q.pop();
        }
        count++;
    }
}


void processQuery() {
    int vCount, eCount;
    cin >> vCount >> eCount;
    vector<unordered_set<int>> graph(vCount, unordered_set<int>());

    for (int i = 0; i < eCount; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first - 1].insert(second - 1);
        graph[second - 1].insert(first - 1);
    }

    int start;
    cin >> start;
    --start;
    
    vector<int> dist(vCount,-1);
    bfs(graph, start, vCount, dist);
    for (int i = 0; i < vCount; ++i) {
        if (i == start) {
            continue;
        }
        
        printf("%d ", dist[i]);
    }
    printf("\n");

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        processQuery();
    }
    return 0;
}
