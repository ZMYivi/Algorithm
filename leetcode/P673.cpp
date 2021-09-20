#include<vector>
#include<map>
#include<iostream>
using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int f[2003], t[2003];
        int max_ans = 1;
        for(int i=0; i<nums.size(); ++i) {
            f[i] = 1;
            t[i] = 1;
        }
        for(int i=0; i<nums.size(); ++i) {
            for(int j=0; j<i; ++j) {
                if (nums[i] > nums[j]) {
                    if(f[j]+1>f[i]) {
                        f[i] = f[j] + 1;
                        t[i] = t[j];
                        if(f[i] > max_ans) 
                            max_ans = f[i];
                    } else if (f[j] + 1 == f[i]) {
                        t[i] += t[j];
                    }
                }
            }
        }
        int ans = 0;
        for(int i=0; i<nums.size(); ++i) {
            if(f[i]==max_ans) {
                ans += t[i];
            }
        }
        return ans;
    }
};

int main(){
    Solution* p = new Solution();
    vector<int> test = {1,2,4,3,5,4,7,2};
    cout << p->findNumberOfLIS(test) << endl;
}