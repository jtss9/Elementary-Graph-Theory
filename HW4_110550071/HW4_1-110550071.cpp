#include<bits/stdc++.h>
#define MAX_DIS 922337203685477
using namespace std;
typedef pair<int, long long> p2;
long long infected_time[1000005]={}, protected_time[1000005]={};
int n, m, p, q, t1, t2;
vector<vector<p2>> adj_virus, adj_anti;

void get_infected(queue<int> q1){
    priority_queue<p2, vector<p2>, greater<p2>> pq;
    vector<long long> d(n+1,MAX_DIS);
    while(q1.size()){
        int i = q1.front();
        q1.pop();
        pq.push(make_pair(0, i));
        d[i] = 0;
    }
    while(pq.size()){
        int u = pq.top().second;
        pq.pop();
        for(auto i : adj_virus[u]){
            int v = i.first;
            long long wei = i.second;
            if(d[v] > d[u] + wei){
                d[v] = d[u] + wei;
                pq.push(make_pair(d[v], v));
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(d[i] < infected_time[i])   infected_time[i] = d[i];
    }
}

void get_protected(queue<int> q2){
    priority_queue<p2, vector<p2>, greater<p2>> pq2;
    vector<long long> d2(n+1,MAX_DIS);
    while(q2.size()){
        int i = q2.front();
        q2.pop();
        pq2.push(make_pair(0, i));
        d2[i] = 0;
    }
    while(pq2.size()){
        int u = pq2.top().second;
        pq2.pop();
        for(auto i : adj_anti[u]){
            int v = i.first;
            long long wei = i.second;
            if(d2[v] > d2[u] + wei){
                d2[v] = d2[u] + wei;
                pq2.push(make_pair(d2[v], v));
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(d2[i] < protected_time[i])   protected_time[i] = d2[i];
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> p >> q >> t1 >> t2;
    adj_virus.resize(n+1);
    adj_anti.resize(n+1);
    for(int i=0;i<m;i++){
        int a, b, w;
        cin >> a >> b >> w;
        adj_virus[a].push_back(make_pair(b, w));
        adj_anti[a].push_back(make_pair(b, 1));
    }
    for(int i=1;i<=n;i++){
        infected_time[i] = MAX_DIS;
        protected_time[i] = MAX_DIS;
    }
    //infected
    queue<int> q1;
    for(int i=0;i<p;i++){
        int v;
        cin >> v;
        q1.push(v);
    }
    get_infected(q1);
    
    //protected
    queue<int> q2;
    for(int i=0;i<q;i++){
        int a;
        cin >> a;
        q2.push(a);
    }
    get_protected(q2);
    //result
    int result=0;
    for(int i=1;i<=n;i++){
        if(protected_time[i] < MAX_DIS) protected_time[i] += 1LL*t1;
        if(infected_time[i] < protected_time[i]) result++;
    }
    cout << result;
}