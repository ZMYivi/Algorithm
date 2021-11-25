#include<iostream>
using namespace std;

class Solution {
public:
    string originalDigits(string s) {
        int f[30] = {0};
        for(int i=0; i<s.size(); ++i) {
            f[s[i]-'a']++;
        }

        string nums[10] = {"geight", "wtwo", "zzero", "ufour", "ffive", "xsix", "sseven", "hthree", "oone", "inine"};
        int index[10] = {8, 2, 0, 4, 5, 6, 7, 3, 1, 9};
        int count[10] = {0};
        for(int i=0; i<10; ++i) {
            int temp = f[nums[i][0] - 'a'];
            if(temp > 0) {
                count[index[i]] = temp;
                for(int j=1; j<nums[i].size(); ++j) {
                    f[nums[i][j] - 'a'] -= temp;
                }
            }
        }

        string ans = "";
        for(int i=0; i<10; ++i)
            for(int j=0; j<count[i]; ++j)
                ans += '0' + i;

        return ans;


        
        // // 模拟大法好
        // nums[8] = f['g' - 'a'];
        // if(nums[8] > 0 ){
        //     f['e' - 'a'] -= f['g' - 'a'];
        //     f['i' - 'a'] -= f['g' - 'a'];
        //     f['h' - 'a'] -= f['g' - 'a'];;
        //     f['t' - 'a'] -= f['g' - 'a'];
        //     f['g' - 'a'] = 0;
        // }
        
        // nums[2] = f['w' - 'a'];
        // if(nums[2] > 0) {
        //     f['t' - 'a'] = f['w' - 'a'];
        //     f['o' - 'a'] = f['w' - 'a'];
        //     f['w' - 'a'] = 0;
        // }
        
        // nums[0] = f['z' - 'a'];
        // f['e' - 'a'] -= f['z' - 'a'];
        // f['r' - 'a'] -= f['z' - 'a'];
        // f['o' - 'a'] -= f['z' - 'a'];
        // f['z' - 'a'] = 0;

        // nums[4] = f['u' - 'a'];
        // f['f' - 'a'] -= f['u' - 'a'];
        // f['o' - 'a'] -= f['u' - 'a'];
        // f['r' - 'a'] -= f['u' - 'a'];
        // f['u' - 'a'] = 0;

        // nums[5] = f['f' - 'a'];
        // f['i' - 'a'] -= f['f' - 'a'];
        // f['v' - 'a'] -= f['f' - 'a'];
        // f['e' - 'a'] -= f['f' - 'a'];
        // f['f' - 'a'] = 0;

        // nums[6] = f['x' - 'a'];
        // f['s' - 'a'] -= f['x' - 'a'];
        // f['i' - 'a'] -= f['x' - 'a'];
        // f['x' - 'a'] = 0;

        // nums[7] = f['s' - 'a'];
        // f['e' - 'a'] -= f['s' - 'a'] * 2;
        // f['v' - 'a'] -= f['s' - 'a'];
        // f['n' - 'a'] -= f['s' - 'a'];
        // f['s' - 'a'] = 0;

        // nums[3] = f['h' - 'a'];
        // f['t' - 'a'] -= f['h' - 'a'];
        // f['r' - 'a'] -= f['h' - 'a'];
        // f['e' - 'a'] -= f['h' - 'a'] * 2;
        // f['h' - 'a'] = 0;

        // nums[1] = f['o' - 'a'];
        // f['n' - 'a'] -= f['o' - 'a'];
        // f['e' - 'a'] -= f['o' - 'a'];
        // f['o' - 'a'] = 0;

        // nums[9] = f['i' - 'a'];
    }
};

int main() {
    Solution *p = new Solution();
    cout << p->originalDigits("owoztneoer");
}
