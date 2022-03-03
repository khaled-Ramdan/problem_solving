//maximal product : you are givin integer s and want to split it into exactly k peices 
//and get max product as possible

#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lp(x,y) for(auto i=x;i<y;i++)
#define lpj(x,y) for(auto j=x;j<y;j++)
#define W  int g;  cin>>g; while(g--)
#define SIZ ll(1e6)
const long long N = 2e5+3, MOD = 1e9 + 7, INF = 1e9;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
ll dp[N][100];
ll s, k;
ll sol(ll rem,ll peices) {
	if (not peices) {
		if (not rem)return 1;
		return 0;
	}
	if (not rem)return 0;
	ll& ret = dp[rem][peices];
	if (~ret)return ret;
	for (int i = 1;i <= rem;i++) {
		ret = max(ret, i * sol(rem - i, peices - 1));
	}
	return ret;
}
void solve() {
	memset(dp, -1, sizeof dp);
	cin >> s >> k;
	cout << sol(s, k) << endl;
}
int main() {
	IO;
	W solve();
	return 0;
}