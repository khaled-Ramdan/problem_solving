//https://codeforces.com/contest/166/problem/B

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
template <typename T>
struct Point
{
    typedef Point P;
    T x, y;

    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }

    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    P operator+(P p) const { return P(x + p.x, y + p.y); }

    P operator+=(P p) const { return P(x + p.x, y + p.y); }

    P operator-(P p) const { return P(x - p.x, y - p.y); }

    P operator-=(P p) const { return P(x - p.x, y - p.y); }

    P operator*(T d) const { return P(x * d, y * d); }

    P operator/(T d) const { return P(x / d, y / d); }

    T dot(P p) const { return x * p.x + y * p.y; }

    T cross(P p) const { return x * p.y - y * p.x; }

    T cross(P a, P b) const { return (a - *this).cross(b - *this); }

    T dist2() const { return x * x + y * y; }

    double dist() const { return sqrt((double)dist2()); }

    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }

    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }

    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }

    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }

    friend istream &operator>>(istream &os, P &p)
    {
        return os >> p.x >> p.y;
    }
};

template <class P>
bool onSegment(P s, P e, P p)
{
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

int n, m;
vector<Point<ll>> points;
Point<ll> base;

bool comp(Point<ll> &a, Point<ll> &b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

void prepare()
{
    int idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (idx == -1 || comp(points[i], points[idx]))
        {
            idx = i;
        }
    }
    base = points[idx];
    rotate(points.begin(), points.begin() + idx, points.end());
    n--;
    for (int i = 0; i < n; i++)
    {
        points[i] = points[i + 1] - base;
    }
}

bool pointInsideTriangle(Point<ll> a, Point<ll> &b, Point<ll> &c, Point<ll> &d)
{
    ll area1 = abs(a.cross(b, c));
    ll area2 = abs(d.cross(a, b)) + abs(d.cross(c, a)) + abs(d.cross(b, c));
    return area1 == area2;
}

int sgn(ll value)
{
    return value > 0 ? 1 : value < 0 ? -1 : 0;
}

bool pointInsidePolygon(Point<ll> p)
{
    p = p - base;
    if (points[0].cross(p) != 0 && sgn(points[0].cross(p)) != sgn(points[0].cross(points[n - 1])))
        return false;
    if (points[n - 1].cross(p) != 0 && sgn(points[n - 1].cross(p)) != sgn(points[n - 1].cross(points[0])))
        return false;
    if (points[0].cross(p) == 0 || points[n - 1].cross(p) == 0)
        return false;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (points[mid].cross(p) <= 0)
        {
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    int idx = l;
    
    if (onSegment(points[idx], points[idx - 1], p))
        return false;

    return pointInsideTriangle(Point<ll>(0, 0), points[idx], points[idx - 1], p);
}

void solve()
{
    cin >> n;
    vector<Point<ll>> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].x >> v[i].y;

    reverse(v.begin(), v.end());
    points = v;
    prepare();

    cin >> m;
    bool ok = true;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        if (!pointInsidePolygon(Point<ll>(x, y)))
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
