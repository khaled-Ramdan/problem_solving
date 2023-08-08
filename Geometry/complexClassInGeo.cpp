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

void solve()
{
    point a(0, 1), b(0, 3), c(0, 2);
    cout << isCollinear(a, c, b) << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
