#include<vector>
#include<algorithm>
#include<unordered_map>
#include<iostream>
using namespace std;

class Solution {
public:
    int gcd(int a, int b) {
        if(b == 0) return a;
        else return gcd(b, a%b); 
    }
    int maxScore(vector<int>& nums) {
        vector<int> f(1<<nums.size(), 0);
        vector<vector<int>> pre(nums.size(), vector<int>(nums.size(), 0));
        for(int i=0; i<nums.size(); i++)
            for(int j=i+1; j<nums.size(); j++)
                pre[i][j] = gcd(nums[i], nums[j]);
        
        for(int i=1; i<1<<nums.size(); i++) {
            int judge = 0;
            for(int j=0; j<nums.size(); j++) 
                if((i >> j) & 1) judge++;
            if(judge % 2 != 0) continue;

            for(int j=nums.size()-1; j>=0; j--)
                if(i & (1<<j)) {
                    for(int k = j-1; k>=0; k--)
                        if(i & (1<<k)) {
                            f[i] = max(f[i], f[i ^ (1<<j) ^ (1<<k)] + judge / 2 * pre[k][j]);
                        }
                }
        }
        return f[(1<<nums.size())-1];
    }
};

int main(){
    vector<int> tmp = {1,2};
    Solution s;
    // int ans = s.gcd(2, 2);
    int ans = s.maxScore(tmp);
    cout<<ans<<endl;
}

/***
 * 一个简单的dp竟然没有想出来，真该死啊
 * 用二进制表示装填，而不是用全排列
*/