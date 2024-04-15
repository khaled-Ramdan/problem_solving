// https://codeforces.com/blog/entry/80195

#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
template <class T>
struct Matrix
{
    T a[2][2] = {{0, 0}, {0, 0}};
    ll Mod = 0;
    Matrix() {}
    Matrix(ll mod) { Mod = mod; }
    void init(T r00, T r01, T r10, T r11)
    {
        a[0][0] = r00, a[0][1] = r01;
        a[1][0] = r10, a[1][1] = r11;
    }
    Matrix operator*(const Matrix &other)
    {
        Matrix product(Mod);
        for (int i = 0; i <= 1; i++)
            for (int j = 0; j <= 1; j++)
                for (int k = 0; k <= 1; k++)
                    product.a[i][k] = operation(product.a[i][k], a[i][j], other.a[j][k]);
        return product;
    }
    T operation(T a, T b, T c)
    {
        if constexpr (is_same_v<T, double>)
            return a + b * c;
        else if (Mod == 0)
            return a + b * c;
        else
            return (a % Mod + 1ll * b * c % Mod) % Mod;
    }
};
template <class T>
Matrix<T> expo_power(Matrix<T> a, ll k, ll mod)
{
    Matrix<T> product(mod);
    for (int i = 0; i <= 1; i++)
        product.a[i][i] = 1;
    while (k > 0)
    {
        if (k % 2)
            product = product * a;
        a = a * a;
        k /= 2;
    }
    return product;
}
void solve()
{
    int n;
    double p;
    cin >> n >> p;
    Matrix<double> re;
    re.init(1 - p, p, p, 1 - p);
 
    Matrix z = expo_power(re, n, 0);
    double ans = z.a[0][0];
    cout << fixed << setprecision(10) << ans << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
