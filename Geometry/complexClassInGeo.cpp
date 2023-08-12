#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
const double PI = acos(-1.0);
const double EPS = 1e-10;
typedef complex<double> point;
#define EPS 0.000'000'001
#define x real()
#define y imag()
#define angle(a) atan2(a.imag(), a.real())
#define vec(a, b) (b - a)
#define squaredLength(a) a.x *a.x + a.y *a.y
#define length(a) hypot(a.imag(), a.real()) // hypot is slower than sqrt but more accurate
#define normalize(a) a / length(a)
#define dotProduct(a, b) (conj(a) * b).real()
#define crossProduct(a, b) (conj(a) * b).imag()
#define rotate0(p, ang) p *exp(point(0, ang))
#define rotateAround(p, ang, about) rotate0(vec(about - p), ang) + about
#define reflect0(v, m) conj(v / m) * m
#define reflect(v, m, about) reflect0(vec(v, about), vec(m, about)) + about
#define norm(a) dotProduct(a, a)

bool isCollinear(point a, point b, point c)
{
    return fabs(crossProduct(vec(a, b), vec(a, c))) < EPS;
}
// Point C distance to line A-B
double distanceToLine(point a, point b, point c)
{
    double dist = crossProduct(vec(a, b), vec(a, c)) / length(vec(b, a));
    return fabs(dist);
}
// intersection of segment ab with segment cd
bool intersectSegments(point a, point b, point c, point d, point intersect)
{
    double d1 = crossProduct(a - b, d - c);
    double d2 = crossProduct(a - c, d - c);
    double d3 = crossProduct(a - b, a - c);

    if (fabs(d1) < EPS)
        return false; // parallel or idintical

    double t1 = d2 / d1;
    double t2 = d3 / d1;
    intersect = a + (b - a) * t1;

    if (t1 < -EPS or d2 < -EPS or t2 > 1 + EPS)
        return false; // ab is ray , cd is segment

    return true;
}
// where is p2 relative to segment p0-p1
// ccw = +1 => angle >0 or collinear after p1
// cw  = -1 => angle <0 or collinear after p0
// undefined = 0 => collinar in range [a,b]. Be carful here
int ccw(point p0, point p1, point p2)
{
    point v1(p1 - p0), v2(p2 - p0);
    if (crossProduct(v1, v2) > EPS)
        return +1;
    if (crossProduct(v1, v2) < -EPS)
        return -1;

    if (v1.x * v2.x < -EPS or v1.y * v2.y < -EPS)
        return -1;

    if (norm(v1) < norm(v2) - EPS)
        return +1;
    return 0;
}
bool intersect(point p1, point p2, point p3, point p4)
{
    // special case handling if a segment is just a point
    bool xx = (p1 == p2), yy = (p4 == p3);
    if (xx && yy)
        return p1 == p3;
    if (xx)
        return ccw(p3, p4, p2) == 0;

    if (yy)
        return ccw(p1, p2, p3) == 0;

    return ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 and
           ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0;
}
// if a , b ,c are collinear => don't call this function
pair<double, point> findCircle(point a, point b, point c)
{
    point m1 = (b + a) * 0.5, v1 = b - a, pv1 = point(v1.y, -v1.x);
    point m2 = (b + c) * 0.5, v2 = b - c, pv2 = point(v2.y, -v2.x);
    point end1 = m1 + pv1, end2 = m2 + pv2, center;
    intersectSegments(m1, end1, m2, end2, center);
    double len = length(a);
    return make_pair(len, center);
}
int dcmp(double a, double b) {
	return (fabs(a - b) <= EPS ? 0 : (a < b ? -1 : 1));
}
// return 0,1 or 2 points => using parameteric parameters / substitution method
vector<point> intersectLineCircle(point p0, point p1, point C, double r)
{
    double a = dotProduct(p1 - p0, p1 - p0);
    double b = 2 * dotProduct(p1 - p0, p0 - C);
    double c = dotProduct(p0 - C, p0 - C) - r * r;
    double f = b * b - 4 * a * c;

    vector<point> v;
    if (dcmp(f, 0) >= 0)
    {
        if (dcmp(f, 0) == 0)
            f = 0;
        double t1 = (-b + sqrt(f)) / 2 * a;
        double t2 = (-b - sqrt(f)) / 2 * a;
        v.push_back(p0 + t1 * (p1 - p0));
        if (dcmp(f, 0) != 0)
            v.push_back(p0 + t2 * (p1 - p0));
    }
    return v;
}
void solve()
{
    auto it = intersectLineCircle(point(25, 5), point(2, 6), point(2, 1), 12);
    cout << it.size() << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
