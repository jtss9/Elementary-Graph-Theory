#include<bits/stdc++.h>
using namespace std;
int min(int a, int b){
    return a > b ? b : a;
}
int main(){
    int n;
    cin >> n;
    vector<string> input(n);
    for(int i=0;i<n;i++){
        cin >> input[i];
    }
    vector<string> trash;
    int count=0;
    int d[n]={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(input[i].length() < input[j].length())   continue;
            else if(i==j)   continue;
            else{
                for(int k=0;k<=input[i].length()-input[j].length();k++){
                    if(input[i].substr(k, input[j].length()) == input[j]){
                        if(d[j]==0){
                            trash.push_back(input[j]);
                            d[j] = 1;
                            count ++;
                        }
                        break;
                    }
                }
            }
            
        }
    }
    for(int i=0;i<trash.size();i++){
        remove(input.begin(), input.end(), trash[i]);
    }
    n -= count;
    input.resize(n);
    /*for(int i=0;i<n;i++){
        cout << input[i] << " ";
    }
    cout << "\n\n";*/

    vector<vector<int>> graph(n, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j] = input[j].length();
            for(int k=1; k<=min(input[i].length(), input[j].length()); k++){
                if(input[i].substr(input[i].size()-k) == input[j].substr(0, k)){
                    graph[i][j] = input[j].size() - k;
                }
            }
        }
    }
    vector<string>tmp1, tmp2;
    for(int i=0;i<n;i++){
        int tmp_count=0;
        for(int j=0;j<n;j++){
            if(graph[i][j] == input[j].length())    tmp_count++;
        }
        if(tmp_count==n-1)  tmp1.push_back(input[i]);
        else    tmp2.push_back(input[i]);
    }
    sort(tmp1.begin(), tmp1.end());
    input.clear();
    input.insert(input.end(), tmp1.begin(), tmp1.end());
    input.insert(input.end(), tmp2.begin(), tmp2.end());
    reverse(input.begin(), input.end());

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j] = input[j].length();
            for(int k=1; k<=min(input[i].length(), input[j].length()); k++){
                if(input[i].substr(input[i].size()-k) == input[j].substr(0, k)){
                    graph[i][j] = input[j].size() - k;
                }
            }
        }
    }

    /*for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }*/

    vector<vector<int>> dp(1<<n, vector<int>(n, 10005));
    vector<vector<int>> parents(1<<n, vector<int>(n, -1));

    for(int i=0;i<n;i++)    dp[1<<i][i] = input[i].length();

    for(int s=1; s<(1<<n); s++){
        for(int i=0;i<n;i++){
            if(!(s & (1<<i)))   continue;
            int prev = s - (1<<i);
            for(int j=0;j<n;j++){
                if(dp[prev][j] + graph[j][i] < dp[s][i]){
                    dp[s][i] = dp[prev][j] + graph[j][i];
                    parents[s][i] = j;
                }
            }
        }
    }
    auto it = min_element(begin(dp.back()), end(dp.back()));
    int now = it - begin(dp.back());
    int index = (1<<n) - 1;
    string answer;
    while(index){
        int prev = parents[index][now];
        if(prev == -1)  answer = input[now] + answer;
        else    answer = input[now].substr(input[now].length()-graph[prev][now]) + answer;
        index = index & ~(1<<now);
        now = prev;
    }
    cout << answer;

}