#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct frnd
{
    int arr;
    int l;
    int index;
    
    bool operator<(const frnd& other) const
    {
        if(arr == other.arr)
            return l < other.l;
        
        return arr < other.arr;
    }
};

class FriendComparator
{
public:
    bool operator()(const pair<frnd, int>& lhs, const pair<frnd, int>& rhs) const
    {
        return lhs.first.l > rhs.first.l;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    
    vector<frnd> friends(n);
    
    for(int i = 0; i < n; i++)
    {
        cin >> friends[i].arr >> friends[i].l;
        friends[i].index = i;
    }
    
    sort(friends.begin(), friends.end());
    
    priority_queue<pair<frnd, int>, vector<pair<frnd, int>>, FriendComparator> pq;
    priority_queue<int, vector<int>, greater<int>> chairs;
    
    for(int i = 0; i < 500000; i++)
        chairs.push(i);
    
    int index;
    cin >> index;
    
    for(int i = 0; i < n; i++)
    {
        while(!pq.empty() && pq.top().first.l < friends[i].arr)
        {
            chairs.push(pq.top().second);
            pq.pop();
        }
        
        if(friends[i].index == index)
            break;
        
        pq.push({friends[i], chairs.top()});
        chairs.pop();
    }
    
    cout << chairs.top();
    return 0;
}
