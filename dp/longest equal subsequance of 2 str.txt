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
* longest equal string subseqance:
* str1:abcdefgh
* str2:ackghefhlmn
*/
int n, dp[N][N], k;
string a, b;
int sol(int i,int j) {
	if (i == a.size() or j == b.size())return 0;
	int& ret = dp[i][j];
	if (~ret)return ret;
	if (a[i] == b[j])return ret = 1 + sol(i + 1, j + 1);
	int c1 = sol(i, j + 1);
	int c2 = sol(i + 1, j);
	return ret = max({ c1,c2 });
}
void solve() {
	cin >> a >> b;
	memset(dp, -1, sizeof dp);
	cout << sol(0, 0);
}
int main() {
	IO;
	solve();
	return 0;
}