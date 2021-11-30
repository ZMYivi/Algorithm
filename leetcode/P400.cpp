#include<iostream>
#include<sstream>
using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        long long next = 0;
        for(int i=1; i<=10; ++i) {
            long long st=1, ed=9;
            for(int j=1; j<i; ++j) {
                st *= 10;
                ed *= 10;
                ed += 9;
            }
            long long total = (ed - st + 1) * i;
            if(n > next && n<= next+total) {
                int temp = n - next;
                int pos = (temp / i);
                if(temp % i != 0) pos ++;
                int num = st + pos - 1;
                
                int ans;
                if(temp % i == 0) temp = 1;
                else {
                    temp = i - temp % i + 1;
                }
                for(int j=1; j <= temp; ++j) {
                    ans = num % 10;
                    num /= 10;
                }
                return ans;
            }
            next = next + total;
        }
        return 0;
    }
};

int main(){
    Solution *p = new Solution();
    cout << p->findNthDigit(10000000) << endl;

    long long len = 9999999;
    len --;
    long long pos = 0;
    int num = 0;
    int n = 10000000;
    while(pos <= len) {
        num ++;
        string temp = to_string(num);
        if(n > pos && n <= pos + temp.length()) {
            cout<< temp[n-pos-1] <<endl;
            return 0;
        }
        pos += temp.length();
    }
}
