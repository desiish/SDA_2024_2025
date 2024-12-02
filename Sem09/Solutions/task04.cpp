// Техника - префиксни суми
// Пазим в map-а какви суми сме намерили до момента.
// При получаване на сума X, към броят достигания на сума K, добавяме броят срещания на X-K
class Solution {
public:
 int subarraySum(vector<int>& nums, int k) {
        int sum=0;
        int count=0;
        unordered_map<int,int>m;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            if(sum==k)
                count++;
            if(m.find(sum-k)!=m.end())
                count+=m[sum-k];
            m[sum]++;
        }
        return count;
    }
};