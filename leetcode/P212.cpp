#include<vector>
#include<map>
#include<string>
#include<iostream>
using namespace std;

class Solution {
public:
    map<string, bool> flag;
    bool judge[14][14];
    int m, n, top;
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        m = board.size(), n = board[0].size();
        top = 0;
        for(int i=0; i<words.size(); i++){
            if (words[i].size() > top) top = words[i].size();
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                memset(judge, 0, sizeof(judge));
                dfs(i, j, board, "", 0);
            }
        }
        vector<string> ans;
        for(int i=0; i<words.size(); i++) {
            if (flag[words[i]]) {
                ans.push_back(words[i]);
            }
        }
        return ans;
    }
    void dfs(int i, int j, vector<vector<char> >& board, string str, int deep) {
        if (deep >= top) return;
        if ((i<0)||(i>=m)||(j<0)||(j>=n)) return;
        if (judge[i][j]) return;
        flag[str + board[i][j]] = true;
        judge[i][j] = true;
        dfs(i+1, j, board, str + board[i][j], deep + 1);
        dfs(i-1, j, board, str + board[i][j], deep + 1);
        dfs(i, j+1, board, str + board[i][j], deep + 1);
        dfs(i, j-1, board, str + board[i][j], deep + 1);
        judge[i][j] = false;
        return;
    }
};

int main() {
    Solution* p = new Solution();
    vector<string> ans;
    vector<vector<char> > board(4, vector<char>(4));
    vector<char> temp1 = {'a', 'b', 'c', 'e'};
    board[0] = temp1;
    vector<char> temp2 = {'z', 'z', 'd', 'z'};
    board[1] = temp2;
    vector<char> temp3 = {'z', 'z', 'c', 'z'};
    board[2] = temp3;
    vector<char> temp4 = {'z', 'a', 'b', 'z'};
    board[3] = temp4;
    vector<string> temp5 = {"abcdce"};
    
    ans = p->findWords(board, temp5);
    for(int i=0; i<ans.size(); i++)
        cout<<ans[i]<<endl;
}