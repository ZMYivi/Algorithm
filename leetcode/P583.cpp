#include<string>
#include<string.h>
#include<iostream>
using namespace std;

class Solution {
public:
    int maxi(int a, int b) {
        if(a > b) return a;
        return b;
    }
    int minDistance(string word1, string word2) {
        int f[503][503];
        memset(f, 0, sizeof(f));
        int n=word1.size(), m=word2.size();

        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=m; ++j) {
                if(word1[i-1] == word2[j-1]) {
                    f[i][j] = f[i-1][j-1] + 1;
                } else {
                    f[i][j] = maxi(f[i-1][j], f[i][j-1]);
                }
            }
        }

        return word1.size()+word2.size()-2*f[n][m];
    }
};

int main() {
    Solution* p = new Solution();
    cout<< p->minDistance("leetcode", "etco") <<endl;
}