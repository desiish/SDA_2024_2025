#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    long long minGrade;
    long long n;
    cin >> minGrade >> n;
    long long gr;
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> gr;
        sum += gr;
    }
    
    if(sum < n * minGrade)
        cout << "no";
    else
        cout << "yes";
}
