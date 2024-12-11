#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

int main() { 
    cout << fixed << setprecision(1);
  
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
  
    int n;
    cin >> n;
    int num;
    for(int i = 0; i < n; i++)
    {
        cin >> num;
      
        if(maxHeap.empty() || num <= maxHeap.top())
            maxHeap.push(num);
        else
            minHeap.push(num);
        
        if(maxHeap.size() > minHeap.size() + 1)
        {
            int curr = maxHeap.top();
            maxHeap.pop();
            minHeap.push(curr);
        }
        else if(minHeap.size() > maxHeap.size() + 1)
        {
            int curr = minHeap.top();
            minHeap.pop();
            maxHeap.push(curr);            
        }
        
        if(maxHeap.size() > minHeap.size())
            cout << 1.0 * maxHeap.top() << endl;
        else if(minHeap.size() > maxHeap.size())
            cout << 1.0 * minHeap.top() << endl;
        else
            cout << ((minHeap.top() + maxHeap.top()) / 2.0) << endl;
    }
    return 0;
}
