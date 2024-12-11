/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        for(int i = 0; i < lists.size(); i++)
        {
            if(lists[i])
            {
                pq.push({lists[i]->val, i});
            }
        }

        if(pq.empty())
        {
            return nullptr;
        }

        ListNode* head = new ListNode();
        ListNode* curr = head;

        while(!pq.empty())
        {
            auto currP = pq.top();
            pq.pop();

            ListNode* toDelete = lists[currP.second];
            lists[currP.second] = lists[currP.second]->next;

            if(lists[currP.second])
            {
                pq.push({lists[currP.second]->val, currP.second});
            }

            delete toDelete;

            curr->val = currP.first;

            if(!pq.empty())
                curr->next = new ListNode();
            
            curr = curr->next;
        }
        
        return head;
    }
};
