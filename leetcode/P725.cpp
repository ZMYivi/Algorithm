#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int len = 0;
        ListNode* p = head;
        while(p!=nullptr){
            len++;
            p = p->next;
        }
        
        int sub_len = len / k;
        if(sub_len == 0) sub_len = 1;
        int more = len % k;
        if(len<k) more = 0;
        int temp = 1;
        vector<ListNode*> ans;
        while(head!=nullptr){
            if(temp == 1){
                ans.push_back(head);
            }
            if(temp == sub_len && more > 0){
                more--;
            } else if (temp >= sub_len){
                temp = 1;
                p = head;
                head = head->next;
                p->next = nullptr;
                continue;
            }
            temp++;
            head = head->next;
        }
        len = ans.size();
        for(int i=0; i<k-len; ++i){
            ans.push_back(nullptr);
        }
        return ans;
    }
};

int main(){
    ListNode* root = new ListNode();
    root->val = 1;
    Solution* p = new Solution();
    p->splitListToParts(root, 3);
}