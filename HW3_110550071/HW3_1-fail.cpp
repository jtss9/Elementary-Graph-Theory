#include<bits/stdc++.h>
using namespace std;
int visited[100005]={0}, special_visited[100005]={0}, cycle_vis[100005]={0};
vector<int> graph[100005];
long long cost=0;
int edge[505][505]={0};
int a[100005] = {0};
int sm, ind;
int st_c, max_edge, ind1, ind2;
void dfs(int r){
    for(int i : graph[r]){
        if(!special_visited[i]){
            if(a[i] < sm){
                sm = a[i];
                ind = i;
            }
            special_visited[i] = 1;
            dfs(i);
        }
    }
}

void find_cycle(int r, int parent){
    cycle_vis[r] = 1;
    for(int i : graph[r]){
        if(!cycle_vis[i]){
            if(edge[r][i] > max_edge){
                max_edge = edge[r][i];
                ind1 = r; ind2 = i;
            }
            find_cycle(i, r);
            return;
        }else if(i != parent){
            //exist cycle!
            visited[ind1] = 0;
            visited[ind2] = 0;
            cost -= edge[ind1][ind2];
            edge[ind1][ind2] = 0;
            edge[ind2][ind1] = 0;
            auto it1 = remove(graph[ind1].begin(), graph[ind1].end(), ind2);
            auto it2 = remove(graph[ind2].begin(), graph[ind2].end(), ind1);
            graph[ind1].erase(it1, graph[ind1].end());
            graph[ind2].erase(it2, graph[ind2].end());
            return;
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> q;
    for(int i=0;i<q;i++){
        cost=0;
        int n, m, start, small=1000000005;
        cin >> n >> m;
        for(int j=0;j<=n;j++){
            visited[j]=0;
            special_visited[j]=0;
            graph[j].clear();
            a[j]=0;
        }
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                edge[j][k]=0;
            }
        }
        for(int j=1;j<=n;j++){
            cin >> a[j];
            if(a[j] < small){
                start = j;
                small = a[j];
            }
        }
        if(m){
            for(int j=0;j<m;j++){
                int u, v, w;
                cin >> u >> v >> w;
                if(w >= a[u]+a[v])  continue;
                if(w >= a[u]+small && w >= a[v]+small)    continue;
                visited[u] = 1;
                visited[v] = 1;
                cost += 1LL*(w);
                graph[u].push_back(v);
                graph[v].push_back(u);
                edge[u][v] = w;
                edge[v][u] = w;

                for(int k=0;k<n;k++){
                    cycle_vis[k]=0;
                }
                max_edge = 0; st_c = u;
                find_cycle(u, -1);
            }
            for(int j=1;j<=n;j++){
                sm = 1000000005;
                ind = start;
                dfs(j);
                if(sm == 1000000005)  continue;
                if(ind != start){
                    cost += 1LL*small + a[ind];
                }
            }
        }
        for(int j=1;j<=n;j++){
            for(int k : graph[j]){
                visited[k] = 1;
            }
        }
        visited[start] = 1;
        for(int j=1;j<=n;j++){
            if(!visited[j]){
                cost += 1LL*small + a[j];
                visited[j] = 1;
            }
        }
        cout << cost << endl;
    }
}