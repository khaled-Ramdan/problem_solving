#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
template <class T>
struct Point
{
    T x, y, z;
    Point(T x, T y, T z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point &operator+=(const Point &t)
    {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    Point &operator-=(const Point &t)
    {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    Point &operator*=(T t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    Point operator/=(T t)
    {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    Point operator+(const Point &t) const
    {
        return Point(*this) += t;
    }
    Point operator-(const Point &t) const
    {
        return Point(*this) -= t;
    }
    Point operator*(T t) const
    {
        return Point(*this) *= t;
    }
    Point operator/(T t) const
    {
        return Point(*this) /= t;
    }
};
template <class T>
T dotProduct(Point<T> p1, Point<T> p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}
template <class T>
T norm(const Point<T> p) // squared length a.a
{
    return dotProduct(p, p);
}
template <class T>
double Abs(Point<T> p) // length of the vector
{
    return sqrt(norm(p));
}
template <class T>
double projection(Point<T> p1, Point<T> p2) // projection of p1 into p2
{
    return dotProduct(p1, p2) / Abs(p2);
}
template <class T>
double angle(Point<T> p1, Point<T> p2) // angle between a, b
{
    return acos(dotProduct(p1, p2) / Abs(p1) / Abs(p2));
}
template <class T>
Point<T> cross(Point<T> p1, Point<T> p2)
{
    return Point<T>(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);
}
template <class T>
T triple(Point<T> p1, Point<T> p2, Point<T> p3)
{
    return dotProduct(p1, cross(p2, p3));
}
template <class T>
T intersect(Point<T> a1, Point<T> d1, Point<T> a2, Point<T> d2) // for lines
{
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
template <class T>
Point<T> intersect(Point<T> a1, Point<T> n1, Point<T> a2, Point<T> n2, Point<T> a3, Point<T> n3) // for planes
{
    Point<T> x(n1.x, n2.x, n3.x);
    Point<T> y(n1.y, n2.y, n3.y);
    Point<T> z(n1.z, n2.z, n3.z);
    Point<T> d(dotProduct(a1, n1), dotProduct(a2, n2), dotProduct(a3, n3));
    return Point<T>(triple(d, y, x), triple(x, d, z), triple(x, y, d)) / triple(n1, n2, n3);
}
void solve()
{
    Point<int> p1(3, 2, 2), p2(-2, 6, 6), p3(1, 3, 1);
    int res = triple(p1, p2, p3);
    cout << res << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
