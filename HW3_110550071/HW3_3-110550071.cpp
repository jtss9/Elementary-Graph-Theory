#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> adj[100005];
int visited[100005]={};
int par[100005];
int height[100005]={-1};
int vis[100005]={};
void get_parent(int r){
    for(int i : adj[r]){
        if(!visited[i]){
            visited[i] = 1;
            par[i] = r;
            get_parent(i);
        }
        
    }
}

void get_height(int r){
    for(int i : adj[r]){
        //height[r] = max(height[i]) + 1
        if(i == par[r]) continue;
        get_height(i);
        int tmp = -1;
        if(height[i] > tmp){
            tmp = height[i];
        }
        if(tmp>=height[r]) height[r] = tmp + 1;
    }
}

int main(){
    cin >> n;
    for(int i=1;i<n;i++){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    visited[1] = 1;
    par[1] = -1;
    get_parent(1);

    for(int i=1;i<=n;i++){
        if(adj[i].size() == 1){
            height[i] = 0;
        }
    }
    get_height(1);

    for(int i=1;i<=n;i++){
        cout << height[i] << " " << par[i] << "\n"; 
    }
}