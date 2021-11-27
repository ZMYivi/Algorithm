#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

class Solution {
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        this->total = m*n;
    }
    
    vector<int> flip() {
        int x = rand() % total;
        vector<int> ans;
        total--;

        if(map.count(x)) {
            ans = {map[x] / n, map[x] % n};
        } else {
            ans = {x / n, x % n};
        }

        if(map.count(total)) {
            map[x] = map[total];
        } else {
            map[x] = total;
        }

        return ans;
    }
    
    void reset() {
        total = n*m;
        map.clear();
    }
private:
    int n;
    int m;
    int total;
    unordered_map<int, int> map;
};

int main() {

}
