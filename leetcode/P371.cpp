class Solution {
public:
    int getSum(int a, int b) {
        int ta[100], tb[100];
        int pa=0, pb=0;
        while(a != 0) {
            ta[pa++] = a / 2;
            a /= 2;
        }
        while(b != 0) {
            tb[pb++] = b / 2;
            b /= 2;
        }

        int temp = 0;
        for(int i=0; i<a; ++i) {
            if(ta[i] == tb[i]) {
                ta[i] = temp;
                temp = tb[i];
            } else {
                if(ta[i] != 0 && tb[i] != 0) {
                    ta[i] = temp;
                    temp = 0;
                } else {
                    if(ta[i] == 0) {
                        if(ta[])
                    }
                }
            }
        }
    }
};