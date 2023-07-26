#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
    int out[1005]={0}, in[1005] = {0};
    for(int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        out[u]++;
        in[v]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=1;i<=n;i++){
        cout << in[i] << " " << out[i] << endl;
    }
}