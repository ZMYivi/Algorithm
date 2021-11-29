#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        struct temp {
            int x, y;
            temp(int a, int b) {
                x = a;
                y = b;
            };
            bool operator < (const temp& a) const {
                return x * a.y < a.x * y; 
            }
        };

        priority_queue<temp> d;
        for(int i=0; i<arr.size(); ++i)
            for(int j=i+1; j<arr.size(); ++j) {
                temp a(arr[i], arr[j]);
                d.push(a);
                if(d.size() == k) d.pop();
            }
        
        vector<int> ans;
        ans.push_back(d.top().x);
        ans.push_back(d.top().y);
        return ans;
    }
};