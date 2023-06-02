/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 1e6 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
ll xp[N];
ll add(ll a, ll b, ll mod)
{
    return ((a % mod + b % mod) % mod + mod) % mod;
}
ll mul(ll a, ll b, ll mod)
{
    return ((a % mod * b % mod) % mod + mod) % mod;
}
ll pushBack(ll h, ll x, ll p, char ch)
{
    return add(mul(h, x, p), ch, p);
}
ll popFront(ll h, ll len, ll p, char ch)
{
    return add(h, -mul(ch, xp[len - 1], p), p);
}
ll popBack(ll h, ll x, ll p, char ch)
{
    return mul(add(h, -ch, p), inv(x, p), p);
}
ll pushFront(ll h, ll len, ll p, char ch)
{
    return add(h, mul(ch, xp[len], p), p);
}
int x = 128, p = 1e9 + 7, ccc;
char a[N], b[N];
void solve()
{
    scanf("%s %s", &a, &b);
    // printf("%s\n%s", a, b);
    // assert(a == "aa");
    int n = strlen(a), m = strlen(b);
    ll hb = 0, ha = 0;
    for (int i = 0; i < m; i++)
        hb = pushBack(hb, x, p, b[i]);
    for (int i = 0; i < min(n, m); i++)
        ha = pushBack(ha, x, p, a[i]);
    vector<int> ans;
    if (ha == hb)
        ans.push_back(1);
    for (int i = m; i < n; i++)
    {
        ha = popFront(ha, m, p, a[i - m]);
        ha = pushBack(ha, x, p, a[i]);
        if (ha == hb)
            ans.push_back(i - m + 2);
    }
    if (ccc)
        printf("\n");
    if (ans.size() == 0)
        printf("Not Found\n");
    else
    {
        printf("%d\n", ans.size());
        for (auto it : ans)
            printf("%d ", it);
        printf("\n");
    }
    ccc++;
}
int main()
{
    // IO;
    int TC = 1;
    xp[0] = 1;
    for (int i = 1; i < N; i++)
        xp[i] = mul(x, xp[i - 1], p);
    scanf("%d", &TC);
    while (TC--)
        solve();
}
