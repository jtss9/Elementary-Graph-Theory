#include<bits/stdc++.h>
 
 
using namespace std;


//#define int long long 
#define endl '\n'
#define eb emplace_back
#define pb push_back
#define ALL(X) X.begin(), X.end()
#define rALL(X) X.rbegin(), X.rend()
#define debug(x) cout << x<<endl;
typedef long long loli;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<loli,loli> pll;
typedef pair<pll,pll> pllll;
typedef string str;
 
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<loli> vl;
typedef vector<vl> vvl;
typedef vector<vvl> vvvl;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<ld> vld;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<str> vs;
#define maxn 100005
//int a[maxn];
vector<vector<pair<int,int>>> new_edge(maxn);
vector<bool> visited(maxn,false);
int num;
int timer;
int n,m;
int cnt1,cnt2;
void dij(vi &ans, vvpii &graph,int source){
    ans[source] =0;
    priority_queue<pii,vpii,greater<pii>> p;
    p.push({0,source});
    while(p.size()){
        //system("pause");
        int now = p.top().second;
        p.pop();
        for(auto &t:graph[now]){
            int w = t.second;
            int next = t.first;
            if(ans[next]==-1 || ans[next]>ans[now]+w){
                ans[next]=ans[now]+w;
                p.push({ans[next],next});
            }
        }
    }
}
vector<int> dfn(maxn),low(maxn);
vb in(maxn,false);
vb flag(maxn,false);
int idx =0;
void tarjan(int u, int fa) {
    in[u] = true; ++idx;
    dfn[u] = low[u] = idx;
    for(auto &t : new_edge[u]) {
        int v = t.first;
        if(v == fa) continue;
        if(!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) flag[t.second] = true;
        } else if(in[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    in[u] = false;
}       
void _solve(){
    cin >> n>> m;
    vvi ori(m+1,vi(3));
    vvpii g(n+1);
    vvpii rg(n+1);
    //cout << "df"<<endl;
    for(int i =1;i<=m;i++){
        int a,b,c;cin >>a>>b>>c;
        ori[i][0] = a;
        ori[i][1] = b;
        ori[i][2] = c;
        g[a].pb({b,c});
        rg[b].pb({a,c});
    }

    vi ans1(n+1,-1);
    vi ans2(n+1,-1);
    vi parent1(n+1);
    vi parent2(n+1);
   // cout << "df"<<endl;
    dij(ans1,g,1); 
    dij(ans2,rg,2);
    int sh = ans1[2];
  //  cout <<"df"<<endl;
    for(int i =1;i<=m;i++){
        if(ans1[ori[i][0]]+ori[i][2]+ans2[ori[i][1]] == sh){
            new_edge[ori[i][0]].pb({ori[i][1],i});
            new_edge[ori[i][1]].pb({ori[i][0],i});
        }
    }
     tarjan(1, 0);
    for(int i =1;i<=m;i++){
        if(ans1[ori[i][1]]+ori[i][2]+ans2[ori[i][0]] < sh&&ans2[ori[i][0]]!=-1&&ans1[ori[i][1]]!=-1)cout <<"HAPPY\n";
        else{
            if(flag[i])cout <<"SAD\n";
            else cout << "SOSO\n";
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    _solve();

}