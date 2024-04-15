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
    vector<vector<T>> matrix;
    ll Mod = 0;
    Matrix() {}
    Matrix(int n, ll mod) { init(n, mod); }
    void init(int n, ll mod)
    {
        Mod = mod;
        matrix = vector<vector<T>>(n, vector<T>(n));
    }
    Matrix operator*(const Matrix &other)
    {
        int n = matrix.size();
        Matrix product(n, Mod);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    product.matrix[i][k] = operation(product.matrix[i][k], matrix[i][j], other.matrix[j][k]);
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
Matrix<T> expo_power(Matrix<T> a, ll k)
{
    int n = a.matrix.size();
    Matrix<T> product(n, a.Mod);
    for (int i = 0; i < n; i++)
        product.matrix[i][i] = 1;

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
    ll n, m, k;
    cin >> n >> m >> k;
    Matrix<ll> mat(n, Mod);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        mat.matrix[x][y]++;
    }

    mat = expo_power(mat, k);
    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            ans += mat.matrix[i][j];
            ans %= Mod;
        }
    cout << ans << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
