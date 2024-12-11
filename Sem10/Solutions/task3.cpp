#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n;
    cin >> n;
  
    priority_queue<int, vector<int>, greater<int>> pq;
    int from, to;
  
    size_t maxP = 0;
    vector<pair<int, int>> v;
  
    for(int i = 0; i < n; i++)
    {
        cin >> from >> to;
        v.push_back({from, to});
    }
  
    sort(v.begin(), v.end());
    
    for(int i = 0; i < n; i++)
    {
        if(v[i].first == v[i].second)
            continue;
        
        int currArr = v[i].first;
      
        while(!pq.empty() && pq.top() <= currArr)
            pq.pop();
        
        pq.push(v[i].second);
        maxP = max(maxP, pq.size());
    }
    cout << maxP;
    return 0;
}
