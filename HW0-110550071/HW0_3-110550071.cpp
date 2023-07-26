#include<iostream>
using namespace std;
int main(){
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	int points[n] = {0};
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int r;
			cin >> r;
			if(i==j) continue;
			if(r==0) points[i] += b;
			if(r==1) points[i] += a;
			if(r==2) points[i] += c;
		}
	}
	for(int i=0;i<n;i++){
		cout << points[i] << " ";
	}
}
