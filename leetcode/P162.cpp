#include<vector>
#include<iostream>
#include<limits.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // 设置边界
        nums.insert(nums.begin(), INT_MIN);
        nums.insert(nums.end(), INT_MIN);

        int head = 1, tail = nums.size() - 2;
        while(abs(tail-head)>1) {
            int mid = (head + tail) / 2;
            if (nums[mid] > nums[mid-1]) {
                head = mid;
            } else {
                tail = mid - 1;
            }
        }
        if (nums[head]>=nums[head-1]&&nums[head]>=nums[head+1]) {
            return head-1;
        }
        return tail-1;
    }
};

int main(){
    vector<int> nums = {1,2,1,3,5,6,4};
    Solution * p = new Solution();
    int res = p->findPeakElement(nums);
    cout<<res<<endl;
}