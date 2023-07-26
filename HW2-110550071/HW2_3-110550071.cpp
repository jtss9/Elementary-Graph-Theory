#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
vector<int> g[MAXN], C_key;
int degree[MAXN] = {0}, visit[MAXN] = {0}, num, D_key[MAXN] ={0};

void dfs(int s){
    for(int i : g[s]){
        if(!visit[i] && degree[i]!=3){
            visit[i] = 1;
            num++;
            dfs(i);
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n;
    for(int i=1;i<n;i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        degree[a]++; degree[b]++;
        
    }
    cin >> m;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        C_key.push_back(x);
    }

    vector<int> leaf;
    for(int i=0;i<n;i++){
        if(!visit[i] && degree[i]==1){
            visit[i] = 1;
            num = 1;
            leaf.push_back(i);
            dfs(i);
            D_key[num]++;
        }
    }
    if(leaf.size() != m+2){
        cout << "NO";
    }else{
        for(int i : C_key){
            int f = 1;
            if(D_key[i]!=0){
                D_key[i]--;
                f = 0;
            }
            if(f){
                cout << "NO";
                return 0;
            }
        }
        cout << "YES";
    }
}