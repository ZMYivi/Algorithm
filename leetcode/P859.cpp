#include<iostream>
using namespace std;

class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if(s.length() != goal.length()) return false;
        int a[30] = {0}, b[30] = {0};
        int tot = 0;
        for(int i=0; i<s.length(); ++i) {
            a[s[i]-'a']++;
            b[goal[i]-'a']++;
            if(s[i] != goal[i]) tot++;
            if(tot > 2) return false;
        }
        if(tot == 1) return false;
        for(int i=0; i<30; ++i)
            if(a[i] != b[i]) return false;
        if(tot == 2) return true;
        for(int i=0; i<30; ++i)
            if(a[i]>=2) return true;
        return false;
    }
};