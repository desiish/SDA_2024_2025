class Solution {
public:
    int findMin(vector<int>& nums) {
        int beg = 0, end = nums.size() - 1;

        int ans = nums[0];

        while(beg <= end)
        {
            if(nums[beg] < nums[end])
            {
                ans = min(nums[beg], ans);
                break;
            }
            int mid = beg + (end - beg) / 2;
            ans = min(ans, nums[mid]);
            if(nums[beg] > nums[mid])
            {
                end = mid - 1;
            }
            else
            {
                beg = mid + 1;
            }
        }

        return ans;
    }
};
