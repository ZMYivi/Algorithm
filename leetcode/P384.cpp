#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        this->original.resize(nums.size());
        copy(nums.begin(), nums.end(), original.begin());
    }
    
    vector<int> reset() {
        copy(original.begin(), original.end(), nums.begin());
        return nums;
    }
    
    vector<int> shuffle() {
        for(int i=0; i<nums.size(); ++i) {
            int j = i + rand()%(nums.size() - i);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        return nums;
    }
private:
    vector<int> nums;
    vector<int> original;
};