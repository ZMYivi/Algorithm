#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    string largestMerge(string word1, string word2) {
        string ans = "";
        int p1 = 0, p2 = 0;
        while(p1 < word1.size() || p2 < word2.size()) {
            if(p1 < word1.size() && word1.substr(p1) > word2.substr(p2))
                ans += word1[p1++];
            else ans += word2[p2++];
        }
        return ans;
    }
};

int main() {
    Solution s;
    string ans = s.largestMerge("abcabc", "abdcaba");
    cout<<ans<<endl;
}

/***
 * 贪心，没有分析出来
 * 重点是分析出如果当前两个指针位置向后有一段的相等的字符串时需要考虑第一个不相同的字符，而比较后缀的方式刚好满足这样的需求
*/