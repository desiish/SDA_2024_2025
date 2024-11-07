class Solution {
public:
    bool isValid(string str) {
        stack<char> s;
        for(int i = 0; i < str.length(); ++i)
        {
            if(str[i] == '(' || str[i] == '{' || str[i] == '[')
                s.push(str[i]);

            else
            {
                if(s.empty())
                    return false;

                char t = s.top();
                if( (str[i] == '}' && t == '{')
                 || (str[i] == ']' && t == '[') 
                 || (str[i] == ')' && t == '(') )
                 {
                    s.pop();
                    continue;
                 }
                 
                return false;               
            }   
        }

        return s.size() == 0;
    }
};
