#include<iostream>
using namespace std;
int dfs(int x) {
    if (x==1) {
        return 0;
    }
    if(x%2==0){
        return dfs(x/2)+1;
    }else{
        if(dfs(x+1)>dfs(x-1)){
            return dfs(x-1) + 1;
        } else {
            return dfs(x+1) + 1;
        }
    }
}
int main(){
    int n = 7;
    cout<<dfs(n)<<endl;
}