#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    bool checkSort(vector<int>& arr) {
        for(int i=1; i<arr.size(); ++i) {
            if (arr[i] < arr[i-1]) {
                return false;
            }
        }
        return true;
    }
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> ans;      
        int len = arr.size();
        if (checkSort(arr)) {
            return ans;
        }
        while(true) {
            int max = arr[0], pi = 0;
            for(int i=0; i<len; ++i) {
                if (arr[i] > max) {
                    pi = i;
                    max = arr[i];
                }
            }
            if (pi!=0) {
                ans.push_back(pi+1);
                for(int i=0; i<(pi+1)/2; ++i){
                    int temp = arr[i];
                    arr[i] = arr[pi-i];
                    arr[pi-i] = temp;
                }
            }
            ans.push_back(len--);
            for(int i=0; i<(len+1)/2; ++i) {
                int temp = arr[i];
                arr[i] = arr[len-i];
                arr[len-i] = temp;
            }
            if (checkSort(arr)) {
                return ans;
            }
        }
    }
};

int main(){
    Solution *temp = new Solution();
    vector<int> target {3,2,4,1};
    temp->pancakeSort(target);
}