#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
int n;
ll crossProduct(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.first * b.second - a.second * b.first;
}
vector<pair<int, int>> convexHull(vector<pair<int, int>> points)
{
    vector<pair<int, int>> high, low;
    sort(points.begin(), points.end());

    low.push_back(points[0]);
    high.push_back(points[0]);

    for (int i = 1; i < points.size(); i++)
    {
        auto point = points[i];
        while (high.size() > 1)
        {
            auto a = high.back();
            auto b = high[high.size() - 2];
            pair<ll, ll> p1 = {a.first - b.first, a.second - b.second};
            pair<ll, ll> p2 = {point.first - b.first, point.second - b.second};
            if (crossProduct(p1, p2) >= 0)
                high.pop_back();
            else
                break;
        }
        high.push_back(point);

        while (low.size() > 1)
        {
            auto a = low.back();
            auto b = low[low.size() - 2];
            pair<ll, ll> p1 = {a.first - b.first, a.second - b.second};
            pair<ll, ll> p2 = {point.first - b.first, point.second - b.second};
            if (crossProduct(p1, p2) <= 0)
                low.pop_back();
            else
                break;
        }
        low.push_back(point);
    }

    for (int i = low.size() - 2; i > 0; i--)
        high.push_back(low[i]);

    return high;
}
pair<int, int> sub(pair<int, int> a, pair<int, int> b)
{
    return {a.first - b.first, a.second - b.second};
}
ll square(pair<ll, ll> p)
{
    return p.first * p.first + p.second * p.second;
}
void solve()
{
    int n;
    ll ans = 0;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].first >> points[i].second;
    }

    auto hull = convexHull(points);

    int siz = hull.size();
    for (int i = 0, j = 1; i < siz; i++)
    {
        while (square(sub(hull[j], hull[i])) > square(sub(hull[j], hull[(i + 1) % siz])))
        {
            ans = max(ans, square(sub(hull[j], hull[i])));
            j = (j + 1) % siz;
        }
    }
    cout << fixed << setprecision(9) << sqrt(ans) << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
