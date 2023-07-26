#include<iostream>
using namespace std;
int main(){
	int n, max_count=0, max_num=0;
	cin >> n;
	int a[100000] = {0};
	while(n--){
		int tmp;
		cin >> tmp;
		a[tmp]++;
		if(a[tmp] > max_count){
			max_count = a[tmp];
			max_num = tmp;
		}else if(a[tmp] == max_count && tmp > max_num){
			max_num = tmp;
		}
	}
	cout << max_num << " " << max_count;
}
