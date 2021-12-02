#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> ans(n);
        vector<pair<int, int>> temp;

        for(int i=0; i<n; ++i) {
            temp.emplace_back(make_pair(-score[i], i));
        }
        sort(temp.begin(), temp.end());

        for(int i=0; i<n; ++i) {
            if(i == 0) ans[temp[i].second] = "Gold Medal";
            if(i == 1) ans[temp[i].second] = "Silver Medal";
            if(i == 2) ans[temp[i].second] = "Bronze Medal";
            if(i > 2) ans[temp[i].second] = to_string(i+1);
        }
        
        return ans;
    }
};

int main(){

}