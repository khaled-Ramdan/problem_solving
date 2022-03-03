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
* 0/1 knapsack problem =>thief wants to steel as much value as possible && weight 
* should fit the size of the knapsack
* example:.
* w: 10 4 20 5 7
* p: 10 15 3 1 4
* knapsack size: 12
* 	 0 1 0 0 1 <=ans subset
*	ans:19
*/
int n, dp[N][N], k;
vector<int>w,p;
int sol(int x, int rem) {
	if (x == n or not rem)return 0;
	int& ret = dp[x][rem];
	if (~ret)return ret;
	int c1 = sol(x + 1, rem);
	int c2 = 0;
	if (rem >= w[x])c2 = p[x] +sol(x + 1, rem - w[x]);
	return ret = max({ c1,c2 });
}
void solve() {
	cin >> n >> k;
	w.resize(n);
	p.resize(n);
	for (int& i : w)cin >> i;
	for (int& i : p)cin >> i;
	memset(dp, -1, sizeof dp);
	cout << sol(0, k);
}
int main() {
	IO;
	solve();
	return 0;
}