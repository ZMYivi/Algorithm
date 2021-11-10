#include<vector>
#include<map>
#include<string>
using namespace std;

class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        map<string, int> tree;
        for(int i=0; i<paths.size(); ++i) {
            if(tree.count(paths[i][0]) == 0) {
                tree[paths[i][0]] = 1;
            } else {
                tree[paths[i][0]]++;
            }

            if(tree.count(paths[i][1]) == 0) {
                tree[paths[i][0]] = -1;
            } else {
                tree[paths[i][0]]--;
            }
        }

        for(auto i:paths) {
            if(tree[i[0]] == -1) {
                return i[0];
            }
            if(tree[i[1]] == -1) {
                return i[0];
            }
        }
    }
};