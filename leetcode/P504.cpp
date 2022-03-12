#include<iostream>
using namespace std;

class Solution {
public:
    string convertToBase7(int num) {
        int flag = 0;
        if(num < 0) {
            num = 0 - num;
            flag = 1;
        }
        if(num == 0) {
            return "0";
        }

        string ans = "";
        while(num > 0) {
            int p = num % 7;
            ans = to_string(p) + ans;
            num /= 7;
        }
        if(flag) {
            ans = "-" + ans;
        }
        return ans;
    }
};

int main() {
    Solution *sl = new Solution();
    cout<< sl->convertToBase7(-7);
}
