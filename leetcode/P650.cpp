#include<iostream>
#include<limits>
using namespace std;

class MySolution {
public:
    int minSteps(int n) {
        int f[1002];
        memset(f, 0x3f, sizeof(f));
        f[1] = 0;
        f[2] = 2;
        for(int i=3; i<=n; ++i){
            for(int j=1; j<i; ++j) {
                int temp = INT_MAX;
                if((i - j) % j == 0) temp = f[j] + (i - j) / j + 1;
                if(f[i] > temp) f[i] = temp; 
            }
        }
        return f[n];
    }
};

class Solution {
public:
    int minSteps(int n) {
        int ans = 0;
        for(int i=2; i*i<=n; ++i) {
            while(n%i == 0){
                n/= i;
                ans+=i;
            }
        }
        if(n>1) ans+=n;
        return ans;
    }
};

int main() {
    Solution* p = new Solution();
    cout<<p->minSteps(24)<<endl;
}