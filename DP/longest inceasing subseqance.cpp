#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lp(x,y) for(auto i=x;i<y;i++)
#define lpj(x,y) for(auto j=x;j<y;j++)
#define W  int g;  cin>>g; while(g--)
#define SIZ ll(1e6)
const long long N = 2e3 + 3, MOD = 1e9 + 7, INF = 1e9;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
/*
* get the longest increasing subseqance from the array
* 6
* 5 2 7 3 4 6
* ans: 4  =>taking 2 3 4 6 
*/
int n,dp[N][N];
vector<int>a;
int sol(int x, int prv) {//note that prv can be either a value or index =>here it is index
	if (x == n)return 0;
	int& ret = (~prv ? dp[x][prv] : prv);
	if (~ret)return ret;
	int c1 = sol(x + 1, prv);
	int c2 = 0;
	if (prv==-1 or a[x] >= a[prv])c2 = 1 + sol(x + 1, x);
	return ret = max({ c1,c2 });
}
void solve() {
	cin >> n;
	a.resize(n);
	for (int& i : a)cin >> i;
	memset(dp, -1, sizeof dp);
	cout << sol(0, -1);
}
int main() {
	IO;
	solve();
	return 0;
}