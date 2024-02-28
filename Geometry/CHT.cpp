//https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
struct CHT
{

    struct Line
    {
        ll slope, yIntercept;

        Line(ll slope, ll yIntercept) : slope(slope), yIntercept(yIntercept) {}

        ll val(ll x)
        {
            return slope * x + yIntercept;
        }

        ll intersect(Line y)
        {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };

    deque<pair<Line, ll>> dq;

    void insert(ll slope, ll yIntercept)
    {
        Line newLine(slope, yIntercept);

        while (int(dq.size()) > 1 && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty())
        {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    ll query(ll x)
    {

        while (int(dq.size()) > 1)
        {
            if (dq[1].second <= x)
                dq.pop_front();
            else
                break;
        }

        return dq[0].first.val(x);
    }

    ll query2(ll x)
    {
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, ll> &a, const pair<Line, ll> &b)
                                {
                                    return a.second > b.second;
                                });

        return qry.first.val(x);
    }
};
CHT cht;
ll n, c, h[N], dp[N];
void solve()
{
    cin >> n >> c;
    for (int i = 0; i < n; i++)
        cin >> h[i];

    cht.insert(-2 * h[0], h[0] * h[0] + dp[0]);

    for (int i = 1; i < n; i++)
    {
        dp[i] = cht.query2(h[i]) + h[i] * h[i] + c;
        cht.insert(-2 * h[i], h[i] * h[i] + dp[i]);
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
