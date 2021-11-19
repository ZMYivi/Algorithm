#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums.size() == 0) {
            return 0;
        }
        int last = nums[0], now = nums[0];
        int lena = 1, lenb = 1, ans = 0;
        for (int i = 1; i<nums.size(); i++) {
            if (nums[i] != now) {
                if(now-last == 1) {
                    ans = max(ans, lena+lenb);
                }
                lena = lenb;
                last = now;
                lenb = 1;
                now = nums[i];
            } else {
                lenb++;
            }
        }
        if (now-last == 1){
            ans = max(ans, lena+lenb);
        }
        return ans;
    }
};

int main(){
    vector<int> nums{1,3,2,2,5,2,3,7};
    Solution *temp = new Solution();
    cout << temp->findLHS(nums) <<endl;
}