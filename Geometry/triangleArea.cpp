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
    T x, y;
    Point(T x, T y) : x(x), y(y){};
    Point &operator-=(Point p)
    {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator-(Point p)
    {
        return *(this) -= p;
    }
};
template <class T>
double length(Point<T> a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}
double fixAngle(double A)
{
    return A > 1 ? 1 : (A < -1 ? -1 : A);
}
// side => S , Angle =>A
// SAA =====> Sin(A) / a = Sin(B) / b = Sin(C) / c
double getSide_a_from_bAB(double b, double A, double B)
{
    return sin(A) * b / sin(B);
}
// SSA
double getAngle_A_from_abB(double a, double b, double B)
{
    return asin(fixAngle(a * sin(B) / b));
}
// a*a = b*b + c*c - 2*b*c cos(A)
double getAngle_A_form_abc(double a, double b, double c)
{
    return acos(fixAngle((b * b + c * c - a * a) / (2 * a * b)));
}
// Given the length of three medains of triangle , find Area
// A median of a triagle is a line segment join a vertex to the midpoint of the opposite side.
double triangleAreaUsingMedains(double a, double b, double c)
{
    if (a <= 0 or b <= 0 or c <= 0)
        return -1;
    double s = 0.5 * (a + b + c);
    double medians_area = s * (s - a) * (s - b) * (s - c);
    double area = 4.0 / 3.0 * sqrt(medians_area);
    if (medians_area <= 0.0 or area <= 0.0)
        return -1;
    return area;
}
template <class T>
double triangleAreaUsingPoints(Point<T> a, Point<T> b, Point<T> c)
{
    double aa = length(a - b);
    double bb = length(b - c);
    double cc = length(c - a);
    double s = (aa + bb + cc) / 2;
    return sqrt(s * (s - aa) * (s - bb) * (s - cc));
}
void solve()
{
    Point<int> p(1, 2), q(5, 24), o(4, 3);
    cout << triangleAreaUsingPoints(p, q, o);
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
