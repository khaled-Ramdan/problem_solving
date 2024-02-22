#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
/*
how it works: https://www.youtube.com/watch?v=aoxOPx2BIHE
finding if a point leis inside a polygon (OR on any side) in log(N) .
1- use prepare()
2- use pointInConvexPolygon() for queries


the polygon points must be in counter-clockwise order.
*/
struct pt
{
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
    pt operator+(const pt &p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt &p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt &p) const { return x * p.y - y * p.x; }
    long long dot(const pt &p) const { return x * p.x + y * p.y; }
    long long cross(const pt &a, const pt &b) const { return (a - *this).cross(b - *this); }
    long long dot(const pt &a, const pt &b) const { return (a - *this).dot(b - *this); }
    long long sqrLen() const { return this->dot(*this); }
};

bool lexComp(const pt &l, const pt &r)
{
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

int sgn(long long val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

vector<pt> seq;
pt translation;
int n, m;

bool pointInTriangle(pt a, pt b, pt c, pt point)
{
    long long s1 = abs(a.cross(b, c));
    long long s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}
bool onSegment(pt s, pt e, pt p)
{
    return p.cross(s, e) == 0 and (s - p).dot(e - p) <= 0;
}
void prepare(vector<pt> &points)
{
    n = points.size();
    int pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (lexComp(points[i], points[pos]))
            pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for (int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

bool pointInConvexPolygon(pt point)
{
    point = point - translation;
    if (seq[0].cross(point) != 0 &&
        sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1])))
        return false;
    if (seq[n - 1].cross(point) != 0 &&
        sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0])))
        return false;
    /*
        considering the side is inside the polygon: 
        if (seq[0].cross(point) == 0)
        return seq[0].sqrLen() >= point.sqrLen();

        considering the side is inside the polygon: 
        if (seq[0].cross(point) == 0 || seq[n - 1].cross(point) == 0)
        return false;

    */
    if (seq[0].cross(point) == 0 || seq[n - 1].cross(point) == 0)
        return false;

    int l = 0, r = n - 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        int pos = mid;
        if (seq[pos].cross(point) >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;


    // remove it if you want to consider the side to be inside the polygon
    if (onSegment(seq[pos], seq[pos + 1], point))
        return false;

    return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), point);
}
void solve()
{
    cin >> n;
    vector<pt> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].x >> v[i].y;

    reverse(v.begin(), v.end());

    prepare(v);

    cin >> m;
    bool ok = true;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        // cout << pointInConvexPolygon(pt(x, y)) << endl;
        if (!pointInConvexPolygon(pt(x, y)))
            ok = false;
    }
    cout << (ok ? "YES" : "NO") << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
