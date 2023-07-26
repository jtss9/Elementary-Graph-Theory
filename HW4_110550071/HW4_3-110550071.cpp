#include<bits/stdc++.h>
#define BIG 1e9
using namespace std;
int graph[1005][1005]={}, residual_graph[1005][1005]={};
int parent[1005];
int n, m, k;
bool bfs(int s, int t){
    int num = n+m+4;
    bool visited[num];
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i=0;i<num;i++){
            if(!visited[i] && residual_graph[u][i] > 0){
                if(i==t){
                    parent[i] = u;
                    return true;
                }
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }
    return false;
}

int fordfulkerson(int s, int t){
    int num = n+m+4;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            residual_graph[i][j] = graph[i][j];
        }
    }
    int max_flow=0;
    while(bfs(s, t)){
        int path_flow = BIG;
        for(int v=t;v!=s;v=parent[v]){
            int u = parent[v];
            path_flow = min(path_flow, residual_graph[u][v]);
        }
        for(int v=t;v!=s;v=parent[v]){
            int u = parent[v];
            residual_graph[u][v] -= path_flow;
            residual_graph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    graph[0][n+m+1] = n;
    graph[0][n+m+2] = k;
    for(int i=1;i<=n;i++){
        graph[n+m+1][i] = 1;
        graph[n+m+2][i] = 1;
        int t;
        cin >> t;
        for(int j=0;j<t;j++){
            int mons;
            cin >> mons;
            graph[i][n+mons] = 1;
        }
    }
    for(int i=n+1;i<=n+m;i++){
        graph[i][n+m+3] = 1;
    }
    int max_flow = fordfulkerson(0, n+m+3);
    cout << max_flow;
}