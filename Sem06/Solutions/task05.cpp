#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    
    for(int i = 0; i < n; i++)
        cin >> v[i];
    
    stack<int> s;
    int maxLen = 1;
    int idx = n - 1;
    
    for(int i = n - 1; i >= 0; i--)
    {
        while(!s.empty() && v[i] >= s.top())
            s.pop();
        
        s.push(v[i]);
        
        if(s.size() >= maxLen)
        {
            maxLen = s.size();
            idx = i;
        }
    }
    
    cout << idx;
    return 0;
}
