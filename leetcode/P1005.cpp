#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        for(int i=0;i<nums.size();++i)
            if(nums[i]<0 && k>0){
                nums[i] = 0 - nums[i];
                k--;
            }
        int ans = 0;
        for(int i=0;i<nums.size();++i) ans += nums[i];
        if(k>0) {
            if(k % 2 == 1) {
                int temp = nums[0];
                for(int i=0;i<nums.size();++i) temp = min(temp, nums[i]);
                ans -= temp;
            }
        }
        return ans;
    }
};

