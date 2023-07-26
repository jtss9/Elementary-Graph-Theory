#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main(){
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<vector<int>> relation;
    relation.resize(n+1);
    for(int i=0; i<m;i++){
        int a, b;
        cin >> a >> b;
        relation[a].push_back(b);
    }

    vector<int> die(n+1, 0);
    // time=0
    queue<int> q;
    for(int i=0;i<k;i++){
        int v;
        cin >> v;
        q.push(v);
        die[v] = 1; 
    }
    q.push(-1);
    int time_count = 0;
    while(q.size()){
        int f = q.front();
        q.pop();
        if(q.empty()) break;
        if(f == -1){
            time_count++;
            q.push(-1);
            f = q.front();
            q.pop();
            if(time_count==t-1) break;
        }
        for(int i=0;i<relation[f].size();i++){
            if(die[relation[f][i]]==0){
                die[relation[f][i]] = 1;
                q.push(relation[f][i]);
            }
        }

    }

    int total=0;
    for(int i=1;i<=n;i++){
        if(die[i]==1){
            total++;
        }
    }
    cout << total;

}