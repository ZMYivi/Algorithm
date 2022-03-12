#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int t[100005][2] = {0};
    int n[100005][2] = {0};
    int clac(int root) {
        if(t[root][0] == 0 && t[root][1] == 0) {
            return 1;
        }
        if(t[root][0] != 0) {
            n[root][0] = clac(t[root][0]);
        }
        if(t[root][1] != 0) {
            n[root][1] = clac(t[root][1]);
        }
        return n[root][0] + n[root][1] + 1;
    }
    int countHighestScoreNodes(vector<int>& parents) {
        for(int i=0; i<parents.size(); ++i) {
            if(parents[i] != -1) {
                if(t[parents[i]][0] == 0) {
                    t[parents[i]][0] = i;
                } else {
                    t[parents[i]][1] = i;
                }
            }
        }
        int total = clac(0);

        int max = 0;
        int num = 0;
        for(int i=0; i<parents.size(); ++i) {
            if(parents[i] == -1) {
                int tmpa = 1, tmpb = 1;
                if(t[i][0] != 0) {
                    tmpa = n[i][0];
                }
                if(t[i][1] != 0) {
                    tmpb = n[i][1];
                }
                if(tmpa * tmpb > max) {
                    max = tmpa * tmpb;
                    num = 1;
                }
            } else {
                int tmpa = 1, tmpb = 1, tmpc = 1;
                if(t[i][0] != 0) {
                    tmpa = n[i][0];
                }
                if(t[i][1] != 0) {
                    tmpb = n[i][1];
                }
                tmpc = total - n[i][0] - n[i][1] - 1;

                if (tmpa * tmpb * tmpc > max) {
                    max = tmpa * tmpb * tmpc;
                    num = 1;
                } else if (tmpa * tmpb * tmpc == max) {
                    num++;
                }
            }
        }

        return num;
    }
};

int main() {
    vector<int> par = {-1,2,0,2,0};
    Solution p;
    int ans = p.countHighestScoreNodes(par);
    cout << ans << endl;
}