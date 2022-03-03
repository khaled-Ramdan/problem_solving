#include<bits\stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
const long long N = 1e5 + 0, MOD = 1e9 + 7;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
void solve() {
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<(1<<n);i++){
        //get all possible compination 0 => 2^n - 1 
        int sum=0;
        for(int j=0;j<n;j++)sum+= (((1<<j)&i)? -a[j]:a[j]);//if this position agree with relative compination => do operation 
        if(sum%360==0){
            cout<<"YES\n";
            return;
        }
    }
    cout<<"NO\n";
}
int main() {
	IO;
	//FIO
	solve();
	return 0;
}

/*
https://codeforces.com/problemset/problem/1097/B
problem link

*/
