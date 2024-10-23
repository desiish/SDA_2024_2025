#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

bool check(vector<long long>& v, long long ans, long long goal)
{
    long long papers = 0;
    for(auto x : v)
    {
        papers += ans / x;
    }
    
    return papers >= goal;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    long long n, k;
    cin >> n >> k;
    vector<long long> v(k);
    
    
    long long minTime = LLONG_MAX, maxTime = LLONG_MIN; 
    for(int i = 0; i < k; i++)
    {
        cin >> v[i];
        minTime = min(minTime, v[i]);
        maxTime = max(maxTime, v[i]);
    }

    long long beg = (n / k) * minTime;
    long long end = (n / k + 1) * maxTime;

    long long ans = end;
    
    while(beg <= end)
    {
        long long mid = beg + (end - beg) / 2;
        
        if(check(v, mid, n))
        {
            ans = min(ans, mid);
            end = mid - 1;
        }
        else
            beg = mid + 1;
    }
    
    cout << ans;
    
    return 0;
}
