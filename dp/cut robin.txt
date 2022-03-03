#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e5,MOD = 1e8+7,INF = 1e18;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
ll n, m, dp[N] ,a , b , c;
ll solve(int x)
{
    if(x <= 0)
    {
        if(x == 0)
            return 0;
        return -1e6;
    }
    ll &ret = dp[x];
    if(~ret)
        return ret;
    ll c1 = 1 + solve(x - a);
    ll c2 = 1 + solve(x - b);
    ll c3 = 1 + solve(x - c);
    return ret = max({c1,c2,c3});
}
int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> a >> b >> c;
    memset(dp,-1,sizeof dp);
    cout << solve(n);
    return 0;
}