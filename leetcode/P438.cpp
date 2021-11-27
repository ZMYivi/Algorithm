#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        if(s.length() < p.length()) return ans;

        int f[26][30003] = {0};
        f[s[0] - 'a'][0] = 1;
        for(int i=1; i<s.length(); ++i) {
            for(int j=0; j<26; ++j) {
                if(j == s[i]-'a') f[j][i] = f[j][i-1] + 1;
                else f[j][i] = f[j][i-1];
            }
        }

        int t[26] = {0};
        for(int i=0; i<p.length(); ++i) t[p[i] - 'a']++;

        for(int i=p.length()-1; i<s.length(); ++i) {
            bool flag = true;
            int st = 0;
            if(i - p.length() + 1 > 0 ) st = i - p.length() + 1;
            if(st == 0 ) {
                for(int j=0; j<26; ++j)
                    if(f[j][i] != t[j]) flag = false;
            } else {
                for(int j=0; j<26; ++j) {
                    if(f[j][i] - f[j][st - 1] != t[j]) flag = false;
                }
            }

            if(flag) ans.push_back(st);
        }
        return ans;
    }
};
