using namespace std;

int main() {
    int first, n, cnt;
    cin >> first >> n;
    set<int> s;
    s.insert(first);
    
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        
        if (s.find(x) != s.end()) {
            s.insert(y);
        }
    }
    
    cout << s.size();
    return 0;
}