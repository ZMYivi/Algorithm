#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    int find(vector<int>& fa, int a) {
        if(fa[a] == a) return a;
        fa[a] = find(fa, fa[a]);
        return fa[a];
    }
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<int> fa(n, 0);
        for(int i=0; i<n; i++) fa[i] = i;
        for(auto &e:edges) {
            int a = find(fa, e[0]);
            int b = find(fa, e[1]);
            if(a == source) fa[b] = a;
            else if(b == source) fa[a] = b;
            else fa[a] = b;
        }
        if(fa[source] == fa[destination]) return true;
        return false;
    }
};

int main(){
    vector<vector<int>> t;
    vector<int> a={0,1};
    t.emplace_back(a);
    vector<int> b={1,2};
    t.emplace_back(b);
    vector<int> c={2,0};
    t.emplace_back(c);

    Solution s;
    bool ans = s.validPath(3, t, 0, 2);
    cout<<ans<<endl;
}