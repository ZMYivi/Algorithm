#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int i = 0;
        while (i<bits.size()) {
            if(bits[i++] == 0) {
                continue;
            }
            if(i+1 == bits.size()) {
                return false;
            }
            i++;
        }
        return true;
    }
};