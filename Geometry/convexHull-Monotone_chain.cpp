#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
/*

Monotone chain Algorithm¶
get convex hull with collinear points : 3 pints in same line
    time : O(n log n)

the convex hull points is returned in counter-clockwise order
if you want to include collinear points => put the `include_collinear` to be true
otherwise it will be skipped

you want to get smallest convex hull ?
=> don't include collinear points option.
*/
struct pt
{
    double x, y;
};

int orientation(pt a, pt b, pt c)
{
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0)
        return -1; // clockwise
    if (v > 0)
        return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear)
{
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear)
{
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}

vector<pt> convex_hull(vector<pt> a, bool include_collinear = false)
{
    if (a.size() == 1)
        return a;

    sort(a.begin(), a.end(), [](pt a, pt b)
         { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++)
    {
        if (i == a.size() - 1 || cw(p1, a[i], p2, include_collinear))
        {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i], include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2, include_collinear))
        {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i], include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if (include_collinear && up.size() == a.size())
    {
        reverse(a.begin(), a.end());
        return a;
    }
    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);

    return a;
}
void solve()
{
    int n, x, y;
    cin >> n;
    vector<pt> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        v[i].x = x;
        v[i].y = y;
    }
    auto vv = convex_hull(v);
    cout << vv.size() << endl;
    for (int i = 0; i < vv.size(); i++)
        cout << vv[i].x << " " << vv[i].y << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
