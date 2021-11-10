#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (duration == 0) {
            return 0;
        }
        int lt = timeSeries[0], ans = 0;
        for(int i=1; i<timeSeries.size(); ++i) {
            if(timeSeries[i] == lt) continue;
            if(timeSeries[i] - duration + 1 < lt) ans += timeSeries[i] - lt + 1;
            else ans += duration;
            lt = timeSeries[i];
        }
        if(timeSeries.size() > 1) ans += duration;
        return ans;
    }
};
