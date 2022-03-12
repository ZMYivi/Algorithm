#include<iostream>
#include<vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> ans;
        if(root->children.size() == 0) {
            ans.push_back(root->val);
            return ans;
        }
        for(int i=0; i<root->children.size(); i++) {
            vector<int> tmp = preorder(root->children[i]);
            for(int j=0; j<tmp.size(); ++j) {
                ans.push_back(tmp[j]);
            }
        }
        return ans;
    }
};