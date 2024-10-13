//Time complexity O(n^2)

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    
    for(int i = 0; i < n; i++)
        cin >> v[i];
    
    long long maxArea = 0;
    for(int i = 0; i < n; i++) {
        int curr = v[i];
        for(int j = i + 1; j < n; j++)  {
            long long currArea = min(v[i], v[j]) * (j - i);
            maxArea = max(maxArea, currArea);
        }
    }
    
    cout << maxArea;
    
    return 0;
}
