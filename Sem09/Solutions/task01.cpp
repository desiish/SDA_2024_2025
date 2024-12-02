#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

// Generate all submasks of N
void addMasks(int n, set<int>& s) {
    for(int i = 0; i <= n; ++i) {
        if ((n | i) == n) {
            s.insert(i);
        }
    }
}

int main() {
    int n;
    cin >> n;
    // CAN BE REPLACED WITH UNORDERED_SET!!!
    set<int> s;

    for(int i = 0; i < n; ++i) {
        int curr;
        cin >> curr;
        addMasks(curr, s);
    }

    cout << s.size();

    return 0;
}