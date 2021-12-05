#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        const int modd = 1337;
        bool f[1338] = {0};   
        int num[1338] = {0};
        int total = 1, p = a % modd;
        while(!f[p]) {
            f[p] = true;
            num[total++] = p;
            p = ((p % modd) * (a % modd)) % modd;
        }
        num[0] = num[--total];

        int temp = 0, flag = 0;
        for(int i=0; i<b.size(); ++i) {
            flag *= 10;
            temp = b[i] + flag;
            flag = temp % total;
        }
        return num[flag];
    }
};

int main() {
    Solution *p = new Solution();
    vector<int> temp = {2,0,0};
    cout << p->superPow(2147483647, temp);
}