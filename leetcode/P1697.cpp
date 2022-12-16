#include<algorithm>
#include<vector>
#include<map>
#include<iostream>
using namespace std;

class Solution {
public:
    int find(map<int, int> &fa, int cur) {
        if(fa[cur] == cur) return cur;
        fa[cur] = find(fa, fa[cur]);
        return fa[cur];
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        sort(edgeList.begin(), edgeList.end(), [](vector<int> &a, vector<int> &b){
            return a[2] < b[2];
        });
        for(int i=0; i<queries.size(); i++) queries[i].push_back(i);
        sort(queries.begin(), queries.end(), [](vector<int> &a, vector<int> &b){
            return a[2] < b[2]; 
        });
 
        map<int, int> fa;
        for(int i=0; i<n; i++) fa[i] = i;
        vector<bool> ans(queries.size());
        int p = 0;
        for(int i=0; i<queries.size(); i++) {
            ans[queries[i][3]] = false;
            while(p < edgeList.size() && edgeList[p][2] < queries[i][2]) {
                int a = find(fa, edgeList[p][0]);
                int b = find(fa, edgeList[p][1]);
                fa[a] = b;
                p++;
            }
            if(find(fa, queries[i][0]) == find(fa, queries[i][1])) {
                ans[queries[i][3]] = true;
            }
        }
        return ans;
    }
};

/*
    这个题目比较有趣，刚开始没有啥思路，就是觉得可能可以用最小生成树，但是死活想不到如何查询，看了题解用的并查集才恍然大悟
*/