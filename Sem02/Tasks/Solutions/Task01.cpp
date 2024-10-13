#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    string str;
    cin >> str;
    char curr = str[0];
    int cnt = 0;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == curr) 
            cnt++;
        else{
            cout << cnt << curr;
            cnt = 1;
            curr = str[i];
        }
    }
    cout << cnt << curr;
    return 0;
}
