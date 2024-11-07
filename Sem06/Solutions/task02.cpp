class Solution {
public:
    bool isOperation(const string& ch) {
        return (ch=="+" || ch=="-" || ch=="/" || ch=="*");
    }

    int calculate(int ftop, int stop, const string& op) {
        if(op=="+")
        {
            return stop+ftop;
        }
        if(op=="-")
        {
            return stop-ftop;
        }
        if(op=="*")
        {
            return stop*ftop;
        }
        return stop/ftop;
    }
    
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(int i=0;i<tokens.size();i++)
        {
            if(!isOperation(tokens[i]))
            {
                stk.push(stoi(tokens[i]));
                continue;
            }

            long long ftop=stk.top();
            stk.pop();
            long long stop=stk.top();
            stk.pop();
            stk.push(calculate(ftop, stop, tokens[i]));
        }
        return stk.top();

    }
};
