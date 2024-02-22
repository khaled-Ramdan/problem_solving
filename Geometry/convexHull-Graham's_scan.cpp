#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
/*

Graham's scan Algorithm
get convex hull with collinear points : 3 pints in same line
    time : O(n log n)

the convex hull points is returned in counter-clockwise order
if you want to include collinear points => put the `include_collinear` to be true
otherwise it will be skipped
you want to get smallest convex hull ?
=> don't include collinear points option.

====> you should take care if a point is repeated 
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
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

vector<pt> convex_hull(vector<pt> &a, bool include_collinear = false)
{
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b)
                         { return make_pair(a.y, a.x) < make_pair(b.y, b.x); });
    sort(a.begin(), a.end(), [&p0](const pt &a, const pt &b)
         {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0; });
    if (include_collinear)
    {
        int i = (int)a.size() - 1;
        while (i >= 0 && collinear(p0, a[i], a.back()))
            i--;
        reverse(a.begin() + i + 1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++)
    {
        while (st.size() > 1 && !cw(st[st.size() - 2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    return st;
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
    auto vv = convex_hull(v, true);
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
