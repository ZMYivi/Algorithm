#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int f = 0, b = s.size() - 1;
        while(s[f] == s[b] && b - f > 1) {
            for(int i=f+1; i<=b; i++) {
                if(s[i] != s[i-1]) {
                    f = i;
                    break;
                }
                if(i == b) f = i;
            }
            for(int i=b-1; i>f; i--) {
                if(s[i] != s[i+1]) {
                    b = i;
                    break;
                }
                if(i == f+1) b = i;
            }
        }
        if(b - f == 1 && s[b] == s[f]) return 0;
        return b - f + 1;
    }
};

int main() {
    Solution s;
    cout<<s.minimumLength("aabaa")<<endl;;
}