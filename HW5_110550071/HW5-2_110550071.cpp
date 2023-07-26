#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    int degree[100]={0};
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
    }
    int min_d = 1000;
    for(int i=1;i<=n;i++){
        if(degree[i] < min_d){
            min_d = degree[i];
        }
    }
    cout << min_d;
}