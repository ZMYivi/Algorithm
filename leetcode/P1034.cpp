#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int dfs(int x, int y, int& target, vector<vector<int>>& grid, vector<vector<int>>& ans, int& color) {
        if(f[x][y]) return 0;
        if(grid[x][y] != target) return 0;

        // 四个相邻的位置是否都是target，不是则为边界
        int temp = 0;
        if(x-1 >= 0 && grid[x-1][y] == target) temp++;
        if(x+1 < grid.size() && grid[x+1][y] == target) temp++;
        if(y-1 >= 0 && grid[x][y-1] == target) temp++;
        if(y+1 < grid[0].size() && grid[x][y+1] == target) temp++;

        if(temp != 4) ans[x][y] = color;
        f[x][y] = true;
        if(x-1 >= 0 && grid[x-1][y] == target) dfs(x-1, y, target, grid, ans, color);
        if(x+1 < grid.size() && grid[x+1][y] == target) dfs(x+1, y, target, grid, ans, color);
        if(y-1 >= 0 && grid[x][y-1] == target) dfs(x, y-1, target, grid, ans, color);
        if(y+1 < grid[0].size() && grid[x][y+1] == target) dfs(x, y+1, target, grid, ans, color);
        return 0;
    }
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        vector<vector<int>> ans(grid.size(), vector<int>(grid[0].size()));
        for(int i=0; i<grid.size(); ++i){
            for(int j=0; j<grid[i].size(); ++j){
                ans[i][j] = grid[i][j];
                f[i][j] = false;
            }
        }
        
        dfs(row, col, grid[row][col], grid, ans, color);
        return ans;
    }
private:
    bool f[51][51];
};

int main() {
    vector<vector<int>> temp = {{1,1}, {1,2}};
    Solution *p = new Solution();
    p->colorBorder(temp, 0, 0, 3);
}
