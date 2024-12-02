#include <map>
#include <unordered_map>
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> sM;
        unordered_map<char, char> tM;
        for(int i = 0; i < s.size(); i++)
        {
            if(sM.count(s[i]) == 0 && tM.count(t[i]) == 0)
            {
                sM.insert({s[i], t[i]});
                tM.insert({t[i], s[i]});
            }
            else
            {
                if(sM[s[i]] != t[i] || tM[t[i]] != s[i])
                    return false;

            }
        }

        return true;
    }
};