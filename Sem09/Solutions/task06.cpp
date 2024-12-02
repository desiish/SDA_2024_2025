class Solution {
public:
    // Theta(N) - Всеки елемент го броим най-много 2 пъти
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set;
        for(int num : nums){
            set.insert(num);
        }
        int longestSequence = 0;
        for(int num : nums){
            if(set.find(num-1) == set.end()){
                int currentNumber = num;
                int currentSequence = 1;
                while(set.find(currentNumber+1) != set.end()){
                    currentNumber++;
                    currentSequence++;
                }
                longestSequence = max(longestSequence, currentSequence);
            }
        }
        return longestSequence;
    }
};