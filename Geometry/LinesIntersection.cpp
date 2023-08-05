#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
#define EPS 0.000'000'000'001
template <class T>
struct Line
{
    T a, b, c;
    Line(){};
    Line(T a, T b, T c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};
template <class T>
struct Point
{
    T x, y;
};
template <class T>
T det(T a, T b, T c, T d)
{
    return a * d - b * c;
}
template <class T>
bool equivalent(Line<T> m, Line<T> n)
{
    return abs(det(m.a, m.b, n.a, n.b)) < EPS && abs(det(m.a, m.c, n.a, n.c)) < EPS && abs(det(m.b, m.c, n.b, n.c)) < EPS;
}
template <class T>
bool parallel(Line<T> n, Line<T> m)
{
    return abs(det(n.a, n.b, m.a, m.b)) < EPS;
}
template <class T>
bool intersect(Line<T> n, Line<T> m, Point<T> &res)
{
    T zn = det(n.a, n.b, m.a, m.b);
    if (abs(zn) < EPS)
        return false;
    res.x = -det(n.c, n.b, m.c, m.b);
    res.y = -det(n.a, n.c, m.a, m.c);
    return true;
}
void solve()
{
    Line<int> n(1, 2, 3), m(2, 21, 5);
    if (equivalent(n, m))
        cout << "Equavilant\n";
    else if (parallel(n, m))
        cout << "Parallel\n";
    else
    {
        Point<int> p;
        intersect(n, m, p);
        cout << "Intersect at (" << p.x << " , " << p.y << ")";
    }
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
