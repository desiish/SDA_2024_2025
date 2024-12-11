class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        for(auto w : stones)
        {
            pq.push(w);
        }

        while(pq.size() > 1)
        {
            int w1 = pq.top();
            pq.pop();

            int res = w1;
            if(!pq.empty())
            {
                int w2 = pq.top();
                pq.pop();
                res -= w2;
            }

            if(res != 0)
                pq.push(res);
        }

        return pq.size() ? pq.top() : 0;
    }
};
