#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums, int k) {
        vector<int> g;
        vector<int> f(1, 0);
        for(int i=0; i<nums.size(); i++)
            if(nums[i] == 1) {
                g.emplace_back(i - g.size());
                f.emplace_back(f.back() + g.back());
            }
        int ans = 0x7fffffff;
        for(int i=0; i<g.size() - k; i++) {
            int mid = i + k / 2;
            ans = min(ans, (1 - k % 2) * g[mid] + f[i+k] - f[mid+1] - f[mid] + f[i]);
        }
        return ans;
    }
};

int main() {
    Solution a;
    vector<int> tmp = {1,0,0,1,0,1};
    int ans = a.minMoves(tmp, 2);
    cout<<ans<<endl;
}

/*
    很有趣的一个计算题目，有空了可以推倒推倒
*/