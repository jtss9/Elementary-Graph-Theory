#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5, MAX_LOGN = 20;
vector<int> g[MAXN];
int n, q, p[MAX_LOGN][MAXN], d[MAXN];
// p for parents, d for depth
long long dist[MAX_LOGN], dis;

void dfs(int cur, int parent, int depth){
    p[0][cur] = parent;
    d[cur] = depth;
    for(int i=0; i<MAX_LOGN-1; i++){
        p[i+1][cur] = p[i][p[i][cur]];
    }
    for(int i : g[cur]){
        if(i != parent) dfs(i, cur, depth+1);
    }
}

void init(){
    memset(p, -1, sizeof(p));
    dfs(1, -1, 0);
    dist[0] = 1LL;
    for(int i=1;i<MAX_LOGN;i++){
        dist[i] = dist[i-1] << 1LL;
    }
}

int LCA(int u, int v){
    if(d[u] > d[v]) swap(u, v);
    int diff = d[v] - d[u];
    for(int i=MAX_LOGN-1; i>=0; i--){
        if((diff>>i) & 1){
            v = p[i][v];
            dis += dist[i];
        }
    }
    if(u == v)  return u;
    for(int i=MAX_LOGN-1; i>=0; i--){
        if(p[i][u] != p[i][v]){
            u = p[i][u];
            v = p[i][v];
            dis += dist[i]*2;
        }
    }
    dis += 2;
    return p[0][u];
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i=1;i<n;i++){
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    init();
    cin >> q;
    for(int i=0;i<q;i++){
        int u, v;
        cin >> u >> v;
        dis = 0LL;
        int lca = LCA(u, v);
        cout << dis << "\n";
    }
}
