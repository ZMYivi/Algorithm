## 162.寻找峰值

题目难度：中等

【题目描述】

峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。

【解题思路】

题目要求的是logn的复杂度，首先排除遍历。然后logn的算法首先想到的就是二分大法，观察题目中给的数据，是一个不会出现相邻相等元素相等的数组，再加上题目要求的是给出任意一个峰值，所以就可以通过二分来确定某一个峰值。

首先要确定找最大峰值还是最小峰值，我这里找的是最大的峰值，所以首先判断下当前的mid处于一个什么位置，是下降位置还是上升位置，如果是下降位，说明大峰值在左边，如果是上升位，则大峰值在右边。关于如果前后指针处于一个距离很远的位置，且中间隔了很多个大峰值，这种方法也是没问题的，因为题目保证了相邻元素不相等，即不会出现不知道当前处于什么位置的情况，还有就是题目要求任意输出一个峰值即可，所以保证了算法的可行性。

## 212.单词搜索 II

题目难度：困难

【题目描述】

给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

【解题思路】

个人版本：无脑搜索，加点儿剪枝优化即可，首先题目要求字母不可以重复使用，所以可以加一个位置的判断，如果重复就返回，再根据题目中说的每个单词的长度不超过12，所以再加一个搜索的深度，就可以搞定了，感觉算法很合理，但是如果单词的长度变得更长一些则可能不会ac，下面附上个人版的代码

```c++
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
```

官方版本：官方给出的正确的答案是字典树加dfs，跟我的区别就是，我的方法是暴力搜索加剪枝，官方答案引导搜索，我的理解是这里的字典树起到的左右就是引导下个搜索的方向，但是这个方法确实很巧妙，之前听说过字典树，但是没有使用，这次使用了一把，确实好使，以后有类似的字符串的搜索，可以用一用，同时字典树也有一个小优化，就是每当匹配到一个单词之后就给删掉，对于那种全是一个字符的case有奇效。

