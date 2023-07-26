#include<iostream>
#include<algorithm>
using namespace std;
inline int binary_search(long long int arr[], int start, int end, int key){
    int ret;
    int mid;
    while(start<=end){
        if(arr[start]<=key){
            return start;
        }
        if(arr[end]>key){
            return (end+1);
        }
        mid = start + (end-start)/2;
        if(arr[mid]>key)    start = mid+1;
        else if(arr[mid]<key)   end = mid-1;
        else{
            ret = mid;
            break;
        }
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int Q;
    cin >> Q;
    for(int j=0;j<Q;j++){
        long long int arr[50005], sum=0;
        long long int total[50005]={0};
        long long int re_total[50005]={0};
        int flag=1;
        int n, m;
        cin >> n >> m;
        for(int i=1;i<=n;i++){
            cin >> arr[i];
            sum += arr[i];
        }
        for(int i=0;i<m;i++){
            int u, v;
            cin >> u >> v;
            arr[u]--;
            arr[v]--;
        }
        for(int i=1;i<=n;i++){
            if(arr[i]<0){
                cout << "No";
                flag = 0;
                break;
            }
        }
        
        if(flag){
            if(sum%2){
                cout << "No";
                flag = 0;
            }
        }
        if(flag){
            sort(arr+1, arr+n+1, greater<int>());
            for(int i=1;i<=n;i++){
                total[i] = total[i-1] + arr[i];
            }
            for(int i=n;i>=1;i--){
                re_total[i] = re_total[i+1] + arr[i];
            }
            for(int i=1;i<=n;i++){
                long long int left = total[i];
                int tmp = 0;
                long long int right = 1LL*i*(i-1);
                if(i<n){
                    tmp = binary_search(arr, i+1, n, i);
                    right += (1LL*i*(tmp-i-1) + re_total[tmp]);
                }
                if(left > right){
                    cout << "No";
                    flag = 0;
                    break;
                }
            }
        }

        if(flag) cout << "Yes";
        cout << endl;
    }
}