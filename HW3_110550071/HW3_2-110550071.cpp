#include<bits/stdc++.h>
#define MAX_DIS 922337203685477
using namespace std;
typedef pair<int, long long> p2;

class Graph{
public:
    int n_ver;
    vector<vector<p2>> adj;
    vector<long long> d1, dn, d;

    Graph() : n_ver(0){};
    Graph(int n_ver){
        this->n_ver = n_ver;
        adj.resize(n_ver);
    }

    void add_edge(long long w, int u, int v){     // u->v length w
        adj[u].push_back(make_pair(v, w));
    }
    void clear_graph(){
        adj.clear();
        d1.clear(); dn.clear(); d.clear();
        n_ver = 0;
    }
    void g_resize(int n){
        this->n_ver = n;
        adj.resize(n);
    }

    void dijkstra_1(int start);

    void dijkstra_n(int start);

    void solve_k1();

    void solve_k2();
};

// i->1
void Graph::dijkstra_1(int start){
    priority_queue<p2, vector<p2>, greater<p2>> pq;
    d1.resize(n_ver, MAX_DIS);
    pq.push(make_pair(0, start));
    d1[start] = 0;
    while(pq.size()){
        int u = pq.top().second;
        pq.pop();
        for(auto i : adj[u]){
            int v = i.first;
            long long wei = i.second;
            if(d1[v] > d1[u] + wei){
                d1[v] = d1[u] + wei;
                pq.push(make_pair(d1[v], v));
            }
        }
    }
}

void Graph::solve_k1(){
    for(int i=0;i<n_ver;i++){
        if(d1[i] >= MAX_DIS)  cout << -1 << " ";
        else    cout << d1[i] << " ";
    }
    cout << "\n";
}

// i->n
void Graph::dijkstra_n(int start){
    priority_queue<p2, vector<p2>, greater<p2>> pq;
    dn.resize(n_ver, MAX_DIS);
    pq.push(make_pair(0, start));
    dn[start] = 0;
    while(pq.size()){
        int u = pq.top().second;
        pq.pop();
        for(auto i : adj[u]){
            int v = i.first;
            long long wei = i.second;
            if(dn[v] > dn[u] + wei){
                dn[v] = dn[u] + wei;
                pq.push(make_pair(dn[v], v));
            }
        }
    }
}

// i -> 1+n
void Graph::solve_k2(){
    adj.resize(n_ver+1);
    for(int i=0;i<n_ver;i++){
        add_edge(d1[i]+dn[i], n_ver, i);
    }

    priority_queue<p2, vector<p2>, greater<p2>> pq;
    d.resize(n_ver+1, MAX_DIS);
    pq.push(make_pair(0, n_ver));
    d[n_ver] = 0;
    while(pq.size()){
        int u = pq.top().second;
        pq.pop();
        for(auto i : adj[u]){
            int v = i.first;
            long long wei = i.second;
            if(d[v] > d[u] + wei){
                d[v] = d[u] + wei;
                pq.push(make_pair(d[v], v));
            }
        }
    }
    for(int i=0;i<n_ver;i++){
        if(d[i] >= MAX_DIS)  cout << -1 << " ";
        else    cout << d[i] << " ";
    }
    cout << "\n";

}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int t, sub;
    cin >> t >> sub;
    Graph g(0);
    for(int i=0;i<t;i++){
        int n, m, k;
        cin >> n >> m >> k;
        g.clear_graph();
        g.g_resize(n);
        for(int j=0;j<m;j++){
            int u, v;
            long long w;
            cin >> u >> v >> w;
            g.add_edge(w, v-1, u-1);
        }
        if(k==1){
            g.dijkstra_1(0);
            g.solve_k1();
        }
        else if(k==2){
            g.dijkstra_1(0);
            g.dijkstra_n(n-1);
            g.solve_k2();
        }
    }
}