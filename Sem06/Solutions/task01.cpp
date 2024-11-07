class Solution {
    public :
    stack<char> processString(const string& s) {
        stack<char> result; 

            for (char c : s) 
            {
                if (c != '#') 
                    result.push(c); 
                else if (!result.empty())
                    result.pop(); 
            }
      
            return result;
    } 

    bool backspaceCompare(string s, string t) {
        
        stack<char> processedS = processString(s);
        stack<char> processedT = processString(t);

        while (!processedS.empty() && !processedT.empty()) 
        {
            if (processedS.top() != processedT.top()) 
                return false;
          
            processedS.pop();
            processedT.pop();
        }
      
        return processedS.empty() && processedT.empty();
    }
};
