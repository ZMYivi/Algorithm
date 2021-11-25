#include<iostream>
using namespace std;

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int total = minutesToTest / minutesToDie;
        int len = 0, flag = 1;
        while(buckets > flag) {
            if(buckets % (total + 1) != 0) flag = 0;
            buckets /= total + 1;
            len++;
        }
        
        return len;
    }
};

int main() {
    Solution *p = new Solution();
    p->poorPigs(4, 15, 15);
}