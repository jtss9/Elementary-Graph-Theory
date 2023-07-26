#include<bits/stdc++.h>
using namespace std;
struct Graph{
    int n_ver;
    vector <pair<int, pair<int, int>>> edges;
    Graph(int n_ver){
        this->n_ver = n_ver;
    }

    void add_edge(int w, int u, int v){
        edges.push_back({w, {u, v}});
    }
    void clear_graph(){
        edges.clear();
        n_ver = 0;
    }
    void g_resize(int n){
        this->n_ver = n;
    }
    long long Kruskal();
};

struct Sets{
    int *par, *rank;
    int n;
    Sets(int n){
        this->n = n;
        par = new int[n+1];
        rank = new int[n+1];
        for(int i=0;i<=n;i++){
            rank[i] = 0;
            par[i] = i; 
        }
    }

    //get parent of r
    int dfs(int r){
        if(r != par[r]){
            par[r] = dfs(par[r]);
        }
        return par[r];  
    }

    void combine(int t1, int t2){
        t1 = dfs(t1); t2 = dfs(t2);
        
        if(rank[t1] > rank[t2]){
            par[t2] = t1;
        }else{
            par[t1] = t2;
        }

        if(rank[t1] == rank[t2])    rank[t2]++;
    }
};

long long Graph::Kruskal(){
    long long cost_temp = 0;
    sort(edges.begin(), edges.end());
    Sets s(n_ver);

    vector< pair<int, pair<int, int>>> :: iterator it;
    for(it = edges.begin(); it != edges.end(); it++){
        int u = it->second.first;
        int v = it->second.second;

        int s_u = s.dfs(u);
        int s_v = s.dfs(v);

        //different sets then combine
        if(s_u != s_v){
            cost_temp += 1LL*(it->first);
            s.combine(s_u, s_v);
        }
    }
    return cost_temp;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> q;
    Graph g(0);
    for(int i=0;i<q;i++){
        int n, m, start, small=1000000005;
        //start for the smallest index; small for the value of start
        cin >> n >> m;
        int a[100005]={0};
        g.clear_graph();
        g.g_resize(n);
        for(int j=0;j<n;j++){
            cin >> a[j];
            if(a[j] < small){
                start = j;
                small = a[start];
            }
        }
        for(int j=0;j<n;j++){
            if(j==start)    continue;
            g.add_edge(small+a[j], start, j);
        }
        for(int j=0;j<m;j++){
                int u, v, w;
                cin >> u >> v >> w;
                if(w >= a[u-1]+a[v-1])  continue;
                if(w >= a[u-1]+small && w >= a[v-1]+small)    continue;
                g.add_edge(w, u-1, v-1);
        }
        long long cost = g.Kruskal();
        cout << cost << "\n";
    }
    return 0;
}