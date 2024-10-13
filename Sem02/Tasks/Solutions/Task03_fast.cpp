//Time complexity O(n)
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
    int beg = 0, end = n - 1;
    
    while(beg < end) {
        long long currArea = min(v[beg], v[end]) * (end - beg);
        maxArea = max(maxArea, currArea);
        
        if(v[beg] < v[end]) {
            beg++;
        }
        else {
            end--;
        }
    }
    
    cout << maxArea;
    
    return 0;
}
