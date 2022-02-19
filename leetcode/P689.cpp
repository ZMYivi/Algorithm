#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    const bool com(int a, int b) {
        return a<b;
    }
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        struct item {
            int value, index;
            item(int a, int b) {
                value = a;
                index = b;
            }
            bool operator < (const item& a) const {
                if(value < a.value) return false;
                else if (value == a.value && index > a.index) return false;
                return true;
            }
        };

        vector<int> temp;
        for(int i=0;i<nums.size();++i) temp.push_back(nums[i]);
        sort(temp.begin(), temp.end(), com);
        int max_v = 0;
        for(int i=0;i<3*k;++i) max_v += temp[i];

        priority_queue<item> q;
        int ans=0;
        for(int i=0;i<3*k;++i) {
            q.push(item(nums[i], i));
            ans+=nums[i];
        }
        
        for(int i=3*k; i<nums.size(); ++i) {
            if(ans == max_v) {
                vector<int> ans;
                while(q.size() > 0) {
                    ans.push_back(q.top().index);
                    q.pop();
                }
                sort(ans.begin(), ans.end());
                return vector<int> {ans[0], ans[k], ans[2*k]};
            }
            q.push(item(nums[i], i));
            ans = ans - q.top().value + nums[i];
            q.pop();
        }
        if(ans == max_v) {
            vector<int> ans;
            while(q.size() > 0) {
                ans.push_back(q.top().index);
                q.pop();
            }
            sort(ans.begin(), ans.end());
            return vector<int> {ans[0], ans[k], ans[2*k]};
        }
    }
};

int main() {
    Solution*p = new Solution();
    vector<int> temp = {1,2,1,2,6,7,5,1};
    p->maxSumOfThreeSubarrays(temp, 2);
}