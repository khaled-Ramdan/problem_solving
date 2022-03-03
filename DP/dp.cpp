//problem link
//https://atcoder.jp/contests/dp/tasks/dp_c

#include<bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lp(x,y) for(auto i=x;i<y;i++)
#define lpj(x,y) for(auto j=x;j<y;j++)
#define W  int g;  cin>>g; while(g--)
#define SIZ ll(1e6)
const long long N = 5e5 + 5, MOD = 1e9 + 7, INF = 1e18;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll dp[N][3], n,a[N][3],ans;
ll sol(int i, int j) {
	if (i == n )return 0;
	ll& ret = dp[i][j];
	if (~ret)return ret;
	int c1 = a[i][j] + sol(i + 1, (j + 1) % 3);
	int c2 = a[i][j] + sol(i + 1, (j + 2) % 3);
	return ret = max(c1, c2);
}
/*
* coloring a house with rgb 
* no to succsessive houses with same color
* minimize the cost
* input =>number of houses - cost of each color for each house
* test case:
* 3
* 1 100 100
* 100 1 100
* 100 100 1
* ans: 3
*/
int n, dp[N][4],r[N],g[N],b[N];// 0 1 2
int sol(int x,int prv) {
	if (x == n)return 0;
	int& ret = dp[x][prv];
	if (~ret)return ret;
	ret = INF;
	int c1 = INF, c2 = INF, c3 = INF;
	if (prv != 0)c1 = r[x] + sol(x + 1, 0);
	if (prv != 1)c2 = g[x] + sol(x + 1, 1);
	if (prv != 2)c3 = b[x] + sol(x + 1, 2);
	return ret = min({ c1,c2,c3 });
}
void solve() {
	cin >> n;
	memset(dp, -1, sizeof dp);
	//first problem
	/*for (int i = 0;i < n;i++)for (int j = 0;j < 3;j++)cin >> a[i][j];
	for (int i = 0;i < 3;i++)ans = max(ans, sol(0,i));
	cout << ans;*/
	//second problem
	/*for (int i = 0;i < n;i++)cin >> r[i] >> g[i] >> b[i];
	cout << sol(0, 3);*/
	
}
int main() {
	IO;
	solve();
	return 0;
}
