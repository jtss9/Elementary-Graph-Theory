#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> visited, cut;
vector<int> tin, low;
int n, m, count_time;

void dfs(int v, int parent){
    int children = 0;
    visited[v] = true;
    tin[v] = low[v] = count_time++;

    for(int i : adj[v]){
        if(!visited[i]){
            children++;
            dfs(i, v);
            low[v] = min(low[v], low[i]);
            if(parent != -1 && low[i] >= tin[v])    cut[v] = true;
        }
        else if(i != parent){
            low[v] = min(low[v], tin[i]);
        }
    }
    if(parent == -1 && children > 1)    cut[v] = true;
}

void find(){
    count_time = 0;
    visited.assign(n+1, false);
    cut.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for(int i=1;i<=n;i++){
        if(!visited[i]) dfs(i, -1);
    }
    int count=0;
    for(int i=1;i<=n;i++){
        if(cut[i])  count++;
    }
    cout << count << "\n";
    for(int i=1;i<=n;i++){
        if(cut[i]){
            cout << i << " ";
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    adj.resize(n+1);
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    find();
}