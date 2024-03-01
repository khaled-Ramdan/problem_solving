// https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
struct Line
{
    ll m, b;
    mutable function<const Line *()> succ;
    bool operator<(const Line &other) const
    {
        return m < other.m;
    }
    bool operator<(const ll &x) const
    {
        const Line *s = succ();
        if (!s)
            return 0;
        return b - s->b < (s->m - m) * x;
    }
};
// will maintain upper hull for maximum
struct CHT : public multiset<Line, less<>>
{
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;
        return (long double)(x->b - y->b) * (z->m - y->m) >= (long double)(y->b - z->b) * (y->m - x->m);
    }
    void insert_line(ll m, ll b)
    {
        auto y = insert({m, b});
        y->succ = [=]
        { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }

    ll query(ll x)
    {

        auto l = *lower_bound(x);
        return l.m * x + l.b;
    }
};
CHT cht;
ll n, c, h[N], dp[N];
// negative for minimizing...
void solve()
{
    cin >> n >> c;
    for (int i = 0; i < n; i++)
        cin >> h[i];

    cht.insert_line(2 * h[0], -(h[0] * h[0] + dp[0]));

    for (int i = 1; i < n; i++)
    {
        dp[i] = -cht.query(h[i]) + h[i] * h[i] + c;
        cht.insert_line(2 * h[i], -(h[i] * h[i] + dp[i]));
        // cout << dp[i] << " ";
    }
    cout << dp[n - 1] << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}

// 7 14 21 28
