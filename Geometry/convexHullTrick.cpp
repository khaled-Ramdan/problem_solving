//https://codeforces.com/contest/319/problem/C

#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
const ll is_query = -(1LL << 62);
/// We add a line in the form of y = ax + b;
/// so we say dp[i] = min j<i {dp[j] + b[j] * a[i]}
/// where b[j] is a and dp[j] is b and a[i] represents x
struct Line
{
    ll m, b;
    mutable function<const Line *()> succ;
    bool operator<(const Line &rhs) const
    {
        if (rhs.b != is_query)
            return m < rhs.m;
        const Line *s = succ();
        if (!s)
            return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct ConvexHullTrick
{ // will maintain upper hull for maximum
    multiset<Line> s;
    bool bad(multiset<Line>::iterator y)
    {
        auto z = next(y);
        if (y == s.begin())
        {
            if (z == s.end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == s.end())
            return y->m == x->m && y->b <= x->b;
        return (long double)(x->b - y->b) * (z->m - y->m) >= (long double)(y->b - z->b) * (y->m - x->m);
    }
    void insert_line(ll m, ll b)
    {
        auto y = s.insert({m, b});
        y->succ = [=]
        { return next(y) == s.end() ? 0 : &*next(y); };
        if (bad(y))
        {
            s.erase(y);
            return;
        }
        while (next(y) != s.end() && bad(next(y)))
            s.erase(next(y));
        while (y != s.begin() && bad(prev(y)))
            s.erase(prev(y));
    }
    ll eval(ll x)
    {
        auto l = *s.lower_bound((Line){x, is_query});
        return l.m * x + l.b;
    }
};
ConvexHullTrick cht;
void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    cht.insert_line(-b[0], 0);
    ll ans = 0;
    for (int i = 1; i < n; i++)
    {
        ll cur = -cht.eval(a[i]);
        ans = max(ans, cur);
        cht.insert_line(-b[i], -ans);
    }
    cout << ans << "\n";
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
