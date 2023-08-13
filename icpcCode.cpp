
#include <bits/stdc++.h>
using namespace std;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
vector<int> rabin_karp(string const &s, string const &t)
{
    const int p = 31;
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T));
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % m;

    vector<long long> h(T + 1, 0);
    for (int i = 0; i < T; i++)
        h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
    long long h_s = 0;
    for (int i = 0; i < S; i++)
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++)
    {
        long long cur_h = (h[i + S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}
vector<int> prefix_function(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
int n, lg[N + 1];
vector<vector<int>> c;
int compare(int i, int j, int l)
{
    int k = lg[l];
    pair<int, int> a = {c[k][i], c[k][(i + l - (1 << k)) % n]};
    pair<int, int> b = {c[k][j], c[k][(j + l - (1 << k)) % n]};
    return a == b ? 0 : a < b ? -1
                              : 1;
}
void pre()
{
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i / 2] + 1;
}
bool cmp(pair<int, int> a, pair<int, int> b)
{
    int x = compare(a.first, b.first, min(a.second - a.first + 1, b.second - b.first + 1));
    if (x == -1)
        return 1;
    if (x == 1)
        return 0;
    if (a.second - a.first + 1 < b.second - b.first + 1)
        return 1;
    if (a.second - a.first + 1 > b.second - b.first + 1)
        return 0;
    return a < b;
}
void count_sort(vector<int> &p, vector<int> &c)
{
    int n = p.size();

    vector<int> cnt(n);
    for (auto x : c)
        cnt[x]++;

    vector<int> p_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for (int i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto x : p)
    {
        p_new[pos[c[x]]] = x;
        pos[c[x]]++;
    }

    p = p_new;
}

int main()
{
    vector<string> vs;
    string s;
    cin >> s;
    s += "$";
    n = s.size();
    vector<int> p(n);
    c = vector<vector<int>>(25, vector<int>(n));
    // k=0
    {
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {s[i], i};
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++)
            p[i] = a[i].second;
        c[0][p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i].first == a[i - 1].first)
                c[0][p[i]] = c[0][p[i - 1]];
            else
                c[0][p[i]] = c[0][p[i - 1]] + 1;
        }
    }

    int k = 0;
    while ((1 << k) < n)
    {

        for (int i = 0; i < n; i++)
            p[i] = (p[i] - (1 << k) + n) % n;
        count_sort(p, c[k]);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            pair<int, int> now = {c[k][p[i]], c[k][(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[k][p[i - 1]], c[k][(p[i - 1] + (1 << k)) % n]};
            if (now == prev)
                c_new[p[i]] = c_new[p[i - 1]];
            else
                c_new[p[i]] = c_new[p[i - 1]] + 1;
        }
        k++;
        c[k] = c_new;
    }
    vector<int> lcp(n);
    int kz = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int pi = c[k][i], j = p[pi - 1];
        while (s[i + kz] == s[j + kz])
            kz++;
        lcp[pi] = kz;
        kz = max(kz - 1, 0);
    }
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += n - p[i] - lcp[i] - 1;
    }
    cout << sum << endl;

    /*
       int t;
       cin>>t;
       while(t--)
       {
          string s2;
           cin>>s2;
           int l=0,r=n-1,mid,ans=0,st=0,sz=s2.size();
           while(l<=r)
           {
               mid=(l+r)/2;
               //cout<<mid<<endl;
               int ok=0;
               {
                   for(int i=0;i<sz;i++)
                   {
                       if(s2[i]<s[p[mid]+i])
                       {
                           ok=-1;
                           break;
                       }
                       else if(s2[i]>s[p[mid]+i])
                       {
                           ok=1;
                           break;
                       }
                   }
               }
            if(ok<0){
                        r=mid-1;
               }
               else
               {
                    if(ok==0)ans=mid;
                   l=mid+1;
               }
           }
           st=ans;
           l=0,r=n-1;
           while(l<=r)
           {
               mid=(l+r)/2;
               //cout<<l<<" "<<mid<<" "<<r<<endl;

               int ok=0;
               {
                   for(int i=0;i<sz;i++)
                   {
                       if(s2[i]<s[p[mid]+i])
                       {
                           ok=-1;
                           break;
                       }
                       else if(s2[i]>s[p[mid]+i])
                       {
                           ok=1;
                           break;
                       }
                   }
               }

            if(ok<=0){
                    if(ok==0)ans=mid;
                        r=mid-1;
               }
               else
               {
                   l=mid+1;
               }
           }
           if(ans==0)cout<<0<<endl;
           else cout<<st-ans+1<<endl;

       }
    */
    return 0;
}
vector<int> manacher_odd(string s)
{
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]])
        {
            p[i]++;
        }
        if (i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
vector<int> manacher(string s)
{
    string t;
    for (auto c : s)
    {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
////////////////.......comb

struct comb
{
    vector<ll> fc, invfc, fib, dr;
    int n;
    ll MOD;
    comb(int n = 1e6, ll Mod = Mod)
    {
        this->n = n;
        MOD = Mod;
        fc.assign(n, 0);
        fib.assign(n, 0);
        dr.assign(n, 0);
        invfc.assign(n, 0);
        factClc();
        // inverseClc(); //can only be used if MOD < 1e6
    }
    void factClc()
    {
        fc[0] = 1;
        for (int i = 1; i < n; i++)
            fc[i] = (fc[i - 1LL] % MOD * i % MOD) % MOD;
    }
    void inverseClc()
    {
        invfc[1] = 1;
        for (int i = 2; i < MOD; i++)
            invfc[i] = MOD - (MOD / i) * invfc[MOD % i] % MOD;
    }
    ll nCr(ll n, ll r)
    {
        return (fc[n] * inv(fc[r] * fc[n - r] % MOD) + MOD) % MOD;
    }
    ll nCrFast(ll n, ll r)
    {

        return (fc[n] * invfc[fc[r]] % MOD * invfc[fc[n - r]] % MOD + MOD) % MOD;
    }
    // only for small range ==> can overflow
    ll getC(ll n, int r)
    {
        if (r > n)
            return 0;
        ll res = 1;
        for (int i = 0; i < r; i++)
        {
            res *= n - i;
            res /= i + 1;
        }
        return res;
    }
    ll modpow(ll base, ll pow)
    {
        if (pow == 0)
            return 1 % MOD;
        ll u = modpow(base, pow / 2);
        u = (u * u) % MOD;
        if (pow % 2 == 1)
            u = (u * base) % MOD;
        return u;
    }
    ll add(ll a, ll b)
    {
        return ((a % MOD + b % MOD) % MOD + MOD) % MOD;
    }
    ll mul(ll a, ll b)
    {
        return ((a % MOD * b % MOD) % MOD + MOD) % MOD;
    }
    void derrangement()
    {
        dr[0] = 1;
        dr[1] = 0;
        for (int i = 2; i < n; i++)
            dr[i] = mul((i - 1LL), add(dr[i - 1], dr[i - 2]));
    }
    void fibonacci()
    {
        fib[0] = 1;
        fib[1] = 2;
        for (int i = 2; i < n; i++)
            fib[i] = add(fib[i - 1], fib[i - 2]);
    }
    void fibFast()
    {
        map<long, long> F;

        // long f(long n)
        function<ll(ll)> f = [&](long long n)
        {
            if (F.count(n))
                return F[n];
            long k = n / 2;
            if (n % 2 == 0)
            { // n=2*k
                return F[n] = (f(k) * f(k) + f(k - 1) * f(k - 1)) % Mod;
            }
            else
            { // n=2*k+1
                return F[n] = (f(k) * f(k + 1) + f(k - 1) * f(k)) % Mod;
            }
        }
    }
};
/*
    * https://cp-algorithms.com/combinatorics/binomial-coefficients.html#properties
    nCk = nC(n-k)
    nCk = (n/k)*[(n-1)C(k-1)]
    {sum k = [0=>n] (nCk) }= 2^n
    nC1 + nC2 + .... + nCn = 2^n = 1<<n
    {sum m= [0=>n](mCk)} = (n+1)C(k+1)
    0Ck + 1Ck + .... + nCk = (n+1)C(k+1)
    {sum k=[0=>m]((n+k)Ck)} = (n+m+1)Cm
    nC0 + (n+1)C1 + (n+2)C2 + (n+3)C3= (n+4)C3
    (nC0)^2 + (nC1)^2 + ... + (nCn)^2 = (2nCn)
    (nC1) + 2 (nC2)+ ... + n(nCn) = n* 2^(n-1)
    nC0 + (n-1)C1 + (n-2)C2 + ... 0Cn = Fibonacci(n+1)
    The number of ways to place k identical items into n different places when any place can contain any amount of items
    is the definition of the number of k-combinations with repetitions:
    ans = C[n+k-1][k]


    in pascal triangle
    The number of odd elements in row i = 2 ^ (#1's in the binary representation of i)
    Derrangement: permutation has no fixed point
    [4 1 2 3] => derragment
    [1 3 4 2] => not a derrangement (1 maps to 1)
    !n ==> number of derrangements for permutation of size n
    note: n! ==> factorial(n)  , !n ==>derrangment(n)
    !n = [n/e] , e = 2.71828... nearest integer to fraction
    !n = |_ n/e + 1/2 _|     ==> floor function
    probabilty of no fixed points = !n / n!  = n/e/n = 1/e = 0.37
    when n>=4 probability of derrangement  = 37%
    or 63% to get a match (there are fixed points in permutaion)
    n => 0 1 2 3 4 5    6    7
    !n => 1 0 1 2 9 44  265  1854
    dp recurrance:
        !n = (n-1) * [!(n-1)+!(n-2)] for n>=2
        !1 = 0, !0 = 1
    other recurrance:
    ! n =  n==0? 1 : n * !(n-1) + (-1)^ n
*/

//......
const int N = 1e6;
int p[N], isPrime[N];
void spf()
{
    for (int i = 2; i < N; i++)
    {
        if (p[i])
            continue;
        isPrime[i] = true;
        for (ll j = i; j < N; j += i)
            p[j] = i;
    }
}
map<ll, ll> factors(ll n)
{
    map<ll, ll> ret;
    while (n > 1)
    {
        ll spf = p[n];
        while (n % spf == 0)
        {
            ret[spf]++;
            n /= spf;
        }
    }
    return ret;
}
bool is_prime(ll n)
{
    if (n == 2)
        return true;
    if (n == 1 or not(n % 2))
        return false;
    for (ll i = 3; i * i <= n; i += 2)
        if (!(n % i))
            return false;
    return true;
}
ll totient(ll n)
{
    ll coprimes = 1;
    auto temp = factors(n);
    for (auto &i : temp)
        coprimes *= ll(pow(i.first, i.second - 1)) * (i.first - 1);
    return coprimes;
    // if qutiont(n)==n-1 : n is prime
}

//....
#define setIO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
__int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }
//.. priority queue sort
struct myComp
{
    constexpr bool operator()(pair<int, int> const &a, pair<int, int> const &b)
        const noexcept
    {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first > b.first;
    }
};
///.....MO
int N = 1e5, n, m, len, a[N], fr1[N], fr2[N], ans[N], res;
struct query
{
    int l, r, idx;
} q[N];
bool cmp1(query one, query two)
{
    if (one.l / len != two.l / len)
        return one.l < two.l;
    if ((one.l / len) & 1)
        return two.r < one.r;
    else
        return one.r < two.r;
}
void add(int i)
{
    int cur = ++fr1[a[i]];
    fr2[cur - 1]--;
    fr2[cur]++;
    res = max(res, cur);
}
void remove(int i)
{
    int cur = --fr1[a[i]];
    fr2[cur + 1]--;
    fr2[cur]++;
    if (fr2[res] == 0)
        res--;
}
void solve()
{
    scanf("%d %d", &n, &m);
    len = (sqrt(n)) + 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d %d", &q[i].l, &q[i].r);
        q[i].idx = i;
    }
    sort(q, q + m, cmp1);
    int curl = 1, curr = 0;
    for (int i = 0; i < m; ++i)
    {
        while (curl < q[i].l)
            remove(curl++);
        while (curl > q[i].l)
            add(--curl);
        while (curr < q[i].r)
            add(++curr);
        while (curr > q[i].r)
            remove(curr--);
        ans[q[i].idx] = res;
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
}
//... sqr
/*
square root decomposition: O(sqrt(n)*O(operation time)
*/
ll n, sqr, q;
void squareRootDecompesition()
{
    cin >> n;
    sqr = (int)ceil(sqrt(n));
    vector<ll> a(n), block(sqr);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        block[i / sqr] += a[i];
    }
    cin >> q;
    while (q--)
    {
        ll t, l, r, sum = 0, idx, val;
        cin >> t;
        if (t == 1)
        { // answer query
            cin >> l >> r;
            --l, --r;
            for (int i = l; i <= r;)
            {
                if (i % sqr == 0 and i + sqr - 1 <= r)
                { // block inside the range
                    sum += block[i];
                    i += sqr;
                }
                else // brute force movement
                    sum += a[i++];
            }
        }
        else
        { // update
            cin >> idx >> val;
            idx--;
            block[idx / sqr] -= a[idx]; // undo
            a[idx] = val;               // update array
            block[idx / sqr] += a[idx]; // do
        }
    }
}

//..  sparse table
long long st[K + 1][MAXN];
// init
std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << (i - 1))];

// compute sum from l to r
long long sum = 0;
for (int i = K; i >= 0; i--)
{
    if ((1 << i) <= R - L + 1)
    {
        sum += st[i][L];
        L += 1 << i;
    }
}

// log precalculation
int lg[MAXN + 1];
lg[1] = 0;
for (int i = 2; i <= MAXN; i++)
    lg[i] = lg[i / 2] + 1;

// Alternatively, log can be computed on the fly in constant space and time:
//  C++20
#include <bit>
int log2_floor(unsigned long i)
{
    return std::bit_width(i) - 1;
}

// pre C++20
int log2_floor(unsigned long long i)
{
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

// Afterwards we need to precompute the Sparse Table structure. This time we define $f$ with $f(x, y) = \min(x, y)$.

int st[K + 1][MAXN];

std::copy(array.begin(), array.end(), st[0]);

for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++)
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

// And the minimum of a range $[L, R]$ can be computed with:

int i = lg[R - L + 1];
int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);
///////////////////////////////////
int lg[N + 1];
int table[6][17][N];
void build()
{
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            table[j][0][i] = arr[i][j];

    for (int k = 0; k < m; k++)
        for (int i = 1; i <= 16; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                table[k][i][j] = max(table[k][i - 1][j], table[k][i - 1][j + (1 << (i - 1))]);
}
int get(int l, int r, int indx)
{
    if (l > r)
        return 0;
    int i = lg[r - l + 1];
    int ret = max(table[indx][i][l], table[indx][i][r - (1 << i) + 1]);
    return ret;
}
////////////2d sparse ////////////////
int f[N][N][10][10];
int query(int l, int d, int r, int u)
{
    int k1 = std::__lg(r - l);
    int k2 = std::__lg(u - d);
    return std::max({f[l][d][k1][k2], f[r - (1 << k1)][d][k1][k2], f[l][u - (1 << k2)][k1][k2], f[r - (1 << k1)][u - (1 << k2)][k1][k2]});
}
// build
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < m; j++)
    {
        if (a[i][j] == 0)
        {
            f[i][j][0][0] = 0;
        }
        else
        {
            f[i][j][0][0] = 1;
            if (i > 0 && j > 0)
            {
                f[i][j][0][0] += std::min({f[i - 1][j][0][0], f[i][j - 1][0][0], f[i - 1][j - 1][0][0]});
            }
        }
    }
}
for (int k1 = 0; k1 < 10; k1++)
{
    for (int k2 = 0; k2 < 10; k2++)
    {
        for (int i = 0; i + (1 << k1) <= n; i++)
        {
            for (int j = 0; j + (1 << k2) <= m; j++)
            {
                if (k1 == 0 && j + (2 << k2) <= m)
                {
                    f[i][j][k1][k2 + 1] = std::max(f[i][j][k1][k2], f[i][j + (1 << k2)][k1][k2]);
                }
                if (i + (2 << k1) <= n)
                {
                    f[i][j][k1 + 1][k2] = std::max(f[i][j][k1][k2], f[i + (1 << k1)][j][k1][k2]);
                }
            }
        }
    }
}
//....lazy
class segmentTree
{
    vector<ll> tree, lazy;

public:
    segmentTree(int n = N)
    {
        tree.assign(n * 4, 0);
        lazy.assign(n * 4, 0);
    }
    ll build(const vector<ll> &a, ll s, ll e, ll p)
    {
        if (s == e)
            return tree[p] = a[s];
        return tree[p] = build(a, s, (s + e) / 2, 2 * p) + build(a, (s + e) / 2 + 1, e, 2 * p + 1);
    }
    void relax(ll s, ll e, ll p)
    {
        ll mid = (s + e) / 2;
        tree[2 * p] += (mid - s + 1) * lazy[p];
        lazy[2 * p] += lazy[p];

        tree[2 * p + 1] += (e - (mid + 1) + 1) * lazy[p];
        lazy[2 * p + 1] += lazy[p];

        lazy[p] = 0;
    }
    void update(ll s, ll e, ll p, ll l, ll r, ll v)
    {
        if (l > e or r < s)
            return;
        if (s >= l and e <= r)
        {
            tree[p] += (e - s + 1) * v;
            lazy[p] += v;
            relax(s, e, p);
            return;
        }
        relax(s, e, p);
        update(s, (s + e) / 2, 2 * p, l, r, v);
        update((s + e) / 2 + 1, e, 2 * p + 1, l, r, v);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
    ll get(ll s, ll e, ll p, ll i)
    {
        relax(s, e, p);
        if (s == e)
            return tree[p];
        if (i <= (s + e) / 2)
            return get(s, (s + e) / 2, 2 * p, i);
        else
            return get((s + e) / 2 + 1, e, 2 * p + 1, i);
    }
    ll getRange(ll s, ll e, ll p, ll l, ll r)
    {
        if (s >= l and e <= r)
            return tree[p];
        if (l > (s + e) / 2)
            return getRange((s + e) / 2 + 1, e, 2 * p + 1, l, r);
        else if (r <= (s + e) / 2)
            return getRange(s, (s + e) / 2, 2 * p, l, r);
        else
            return getRange(s, (s + e) / 2, 2 * p, l, r) + getRange((s + e) / 2 + 1, e, 2 * p + 1, l, r);
    }
};
class maxSubArraySum
{
    struct data
    {
        ll best, sum, pref, suff;
        data(ll val)
        {
            sum = val;
            best = pref = suff = max(0LL, val);
        }
    };
    vector<data> tree;

public:
    maxSubArraySum(int n = N)
    {
        tree.assign(4 * n, 0);
    }
    ll curBest()
    {
        return tree[1].best;
    }
    void build(const vector<ll> &v, int st, int en, int p)
    {
        if (st == en)
            return tree[p] = data(v[st]), void();
        build(v, st, (st + en) / 2, 2 * p);
        build(v, (st + en) / 2 + 1, en, 2 * p + 1);
        tree[p] = operation(tree[2 * p], tree[2 * p + 1]);
    }
    void update(int idx, int val, int st, int en, int p)
    {
        if (idx < st or idx > en)
            return;
        if (st == en)
            return tree[p] = data(val), void();
        update(idx, val, st, (st + en) / 2, 2 * p);
        update(idx, val, (st + en) / 2 + 1, en, 2 * p + 1);
        tree[p] = operation(tree[2 * p], tree[2 * p + 1]);
    }
    data operation(data l, data r)
    {
        data res(0);
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.best = max({l.best, r.best, l.suff + r.pref});
        return res;
    }
};

struct segtree
{
    int size;
    vector<ll> maxx, minn;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        maxx.assign(size * 2, 0ll);
        minn.assign(size * 2, 0ll);
    }
    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                maxx[x] = a[lx];
                minn[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        maxx[x] = max(maxx[2 * x + 1], maxx[2 * x + 2]);
        minn[x] = min(minn[2 * x + 1], minn[2 * x + 2]);
    }
    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }
    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            maxx[x] = v;
            minn[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
            set(i, v, 2 * x + 2, m, rx);
        maxx[x] = max(maxx[2 * x + 1], maxx[2 * x + 2]);
        minn[x] = min(minn[2 * x + 1], minn[2 * x + 2]);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    ll fmax(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || l >= rx)
        {
            return 0;
        }
        if (l <= lx && rx <= r)
        {
            return maxx[x];
        }
        int m = (lx + rx) / 2;
        return max(fmax(l, r, 2 * x + 1, lx, m), fmax(l, r, 2 * x + 2, m, rx));
    }
    ll fmax(int l, int r)
    {
        return fmax(l, r, 0, 0, size);
    }
    ll fmin(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r || l >= rx)
        {
            return 1e15;
        }
        if (l <= lx && rx <= r)
        {
            return minn[x];
        }
        int m = (lx + rx) / 2;
        return min(fmin(l, r, 2 * x + 1, lx, m), fmin(l, r, 2 * x + 2, m, rx));
    }
    ll fmin(int l, int r)
    {
        return fmin(l, r, 0, 0, size);
    }
    /*ll sum(int l,int r,int x,int lx,int rx)
    {
        if(lx>=r||l>=rx)
        {
            return 0;
        }
        if(l<=lx&&rx<=r)
        {
            return sums[x];
        }
        int m=(lx+rx)/2;
        return sum(l,r,2*x+1,lx,m)+sum(l,r,2*x+2,m,rx);
    }
    ll sum(int l,int r)
    {
        return sum(l,r,0,0,size);
    }*/
};
//.... 
ll n, m = 0, k;
using namespace std;
ll a[1001][1001];
ll arr[4000][4000];

struct segtree
{
    int size;
    void init(int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        // arr.resize(size,vector<ll>(size,0));
        // for(int i=0;i<size*2;i++)arr.push_back(NEUel);
    }
    void build_y(int x, int lx, int rx, int y, int ly, int ry)
    {
        if (ry - ly == 1)
        {
            if (lx == rx - 1)
                arr[x][y] = a[lx][ly];
            else
                arr[x][y] = arr[x * 2 + 1][y] + arr[x * 2 + 2][y];
        }
        else
        {
            int my = (ly + ry) / 2;
            build_y(x, lx, rx, y * 2 + 1, ly, my);
            build_y(x, lx, rx, y * 2 + 2, my, ry);
            arr[x][y] = arr[x][y * 2 + 1] + arr[x][y * 2 + 2];
        }
    }
    void build_x(int x, int lx, int rx)
    {
        if (rx - lx != 1)
        {
            int m = (lx + rx) / 2;
            build_x(2 * x + 1, lx, m);
            build_x(2 * x + 2, m, rx);
        }
        build_y(x, lx, rx, 0, 0, size);
        // arr[x]=merge(arr[2*x+1],arr[2*x+2]);
    }
    void build()
    {
        build_x(0, 0, size);
    }
    void update_y(int x, int lx, int rx, int y, int ly, int ry, int a, int b, int new_val)
    {
        if (ly == ry - 1)
        {
            if (lx == rx - 1)
            {
                arr[x][y] = (arr[x][y] + 1) % 2;
                // cout<<arr[x][y]<<'\n';
            }
            else
                arr[x][y] = arr[x * 2 + 1][y] + arr[x * 2 + 2][y];
        }
        else
        {
            int my = (ly + ry) / 2;
            if (b < my)
                update_y(x, lx, rx, y * 2 + 1, ly, my, a, b, new_val);
            else
                update_y(x, lx, rx, y * 2 + 2, my, ry, a, b, new_val);
            arr[x][y] = arr[x][y * 2 + 1] + arr[x][y * 2 + 2];
        }
    }

    void update_x(int x, int lx, int rx, int a, int b, int new_val)
    {
        if (lx != rx - 1)
        {
            int mx = (lx + rx) / 2;
            if (a < mx)
                update_x(x * 2 + 1, lx, mx, a, b, new_val);
            else
                update_x(x * 2 + 2, mx, rx, a, b, new_val);
        }
        update_y(x, lx, rx, 0, 0, size, a, b, new_val);
    }
    void update_x(int a, int b, int val = 0)
    {
        update_x(0, 0, size, a, b, val);
    }

    int sum_y(int x, int y, int tly, int try_, int ly, int ry)
    {
        if (tly >= ry || try_ <= ly)
            return 0;
        if (ly <= tly && try_ <= ry)
            return arr[x][y];
        int tmy = (tly + try_) / 2;
        return sum_y(x, y * 2 + 1, tly, tmy, ly, ry) + sum_y(x, y * 2 + 2, tmy, try_, ly, ry);
    }
    int sum_x(int x, int tlx, int trx, int lx, int rx, int ly, int ry)
    {
        if (tlx >= rx || trx <= lx)
            return 0;
        if (lx <= tlx && trx <= rx)
            return sum_y(x, 0, 0, size, ly, ry);
        int tmx = (tlx + trx) / 2;
        return sum_x(x * 2 + 1, tlx, tmx, lx, rx, ly, ry) + sum_x(x * 2 + 2, tmx, trx, lx, rx, ly, ry);
    }
    int sum(int a, int b, int c, int d)
    {
        return sum_x(0, 0, size, a, b, c, d);
    }
};

void fn()
{
    cin >> n >> m;
    segtree st;
    st.init(n);
    string s;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            a[i][j] = (int)(s[j] == '*');
            // cout<<a[i][j]<<" ";
        }
        cout << '\n';
    }
    // cout<<1;
    st.build();
    // return;
    while (m--)
    {
        int c;
        ll a, b;
        cin >> c >> a >> b;
        if (c == 2)
        {
            ll d, f;
            cin >> d >> f;
            cout << st.sum(a - 1, d, b - 1, f) << '\n';
        }
        else
        {
            st.update_x(a - 1, b - 1);
        }
    }
}
int main()
{
    // fastio();
    int t = 1;
    // cin>>t;
    while (t--)
        fn();
    return 0;
}
void fn()
{
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    st.build(v);
    while (m--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.fmin(l, r) << '\n';
        }
    }
}
void getStringStream()
{
    string str;
    int x;
    getline(cin, str);
    stringstream ss(str);
    vector<int> v;
    while (ss >> x)
        v.push_back(x);
}
//..... Matrix exponential
// n ! ≈sqrt(2 * pi * n) * (n ^ n) * (e ^ (-n)) stirling approximation.
int MOD = 1e9 + 7;
#define REP(i, n) for (int i = 0; i < (n); i++)
struct Matrix
{
    ll a[2][2] = {{0, 0}, {0, 0}};
    Matrix operator*(const Matrix &other)
    {
        Matrix product;
        REP(i, 2)
        REP(j, 2)
        REP(k, 2)
        {
            product.a[i][k] += a[i][j] * other.a[j][k] % MOD;
            product.a[i][k] %= MOD;
        }
        return product;
    }
};
Matrix expo_power(Matrix a, ll k)
{
    Matrix product;
    REP(i, 2)
    product.a[i][i] = 1;
    while (k > 0)
    {
        if (k % 2)
        {
            product = product * a;
        }
        a = a * a;
        k /= 2;
    }
    return product;
}
void MatrixExponential()
{
    ll n, m;
    cin >> n;
    Matrix ree;
    ree.a[0][0] = 19;
    ree.a[0][1] = 7;
    ree.a[1][0] = 6;
    ree.a[1][1] = 20;
    Matrix z = expo_power(ree, n);
    // printMat(z);
    cout << z.a[0][0] << '\n';
    return;
}
// ...
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
int dcmp(double a, double b)
{
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
//..... DSU
struct DSU
{
    vector<ll> par, siz, st, en, nxt;
    DSU(int n)
    {
        par.resize(n + 1);
        siz.resize(n + 1);
        st.resize(n + 1);
        en.resize(n + 1);
        nxt.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        iota(st.begin(), st.end(), 0);
        iota(en.begin(), en.end(), 0);
        fill(siz.begin(), siz.end(), 1);
    }
    ll parent(ll u)
    {
        if (u == par[u])
            return u;
        return par[u] = parent(par[u]);
    }
    void join(ll u, ll v)
    {
        u = parent(u);
        v = parent(v);
        if (u == v)
            return;
        if (siz[u] > siz[v])
            swap(u, v);
        par[u] = v;
        siz[v] += siz[u];
        nxt[en[v]] = st[u];
        en[v] = en[u];
    }
    void print()
    {
        int u = parent(1);
        while (u)
        {
            cout << u << " ";
            u = nxt[u];
        }
    }
};
/// graph

struct myComp
{
    constexpr bool operator()(pair<int, int> const &a, pair<int, int> const &b) const noexcept
    {
        return a.second < b.second;
    }
};
struct edge
{
    int from, to, cost;
};
vector<edge> adj;
ll dijkstra(int src, int tar)
{
    vector<ll> dis(n + 1, INF);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    dis[src] = 0;
    q.push({0, src});
    while (q.size())
    {
        ll u = q.top().second, uc = q.top().first;
        q.pop();
        if (u == tar)
            return c;
        if (uc != dis[u])
            continue;
        for (auto &e : g[u])
        {
            ll v = e.second, vc = e.first;
            if (dis[v] > dis[u] + vc)
            {
                dis[v] = dis[u] + vc;
                q.push({dis[v], v});
            }
        }
    }
    return -1;
}
pair<bool, ll> bellman1(int src, int tar)
{
    bool isUpdated = 0, hasCycles = 0;
    vector<ll> dis(n, INF);
    dis[src] = 0;
    for (int i = 0; i < n; i++)
    {
        isUpdated = 0;
        for (auto &e : adj)
        {
            if (dis[e.to] > dis[e.from] + e.cost)
            {
                dis[e.to] = dis[e.from] + e.cost;
                isUpdated = 1;
            }
        }
        if (!isUpdated)
            break;
        if (i == n - 1)
            hasCycles = 1;
    }
    return {hasCycles, dis[tar]};
}
ll bellman2(int src, int tar)
{
    vector<ll> dis(n, INF);
    dis[src] = 0;
    bool isUpdated = 0;
    for (int i = 0; i < n - 1; i++)
    {
        isUpdated = 0;
        for (auto &e : adj)
        {
            if (dis[e.to] > dis[e.from] + e.cost)
            {
                isUpdated = 1;
                dis[e.to] = dis[e.from] + e.cost;
            }
        }
        if (!isUpdated)
            break;
    }
    vector<int> hasCycles(n, 0);
    for (int i = 0; i < n - 1; i++)
    {
        isUpdated = 0;
        for (auto &e : adj)
        {
            if (dis[e.to] > dis[e.from] + e.cost)
            {
                isUpdated = 1;
                dis[e.to] = dis[e.from] + e.cost;
                hasCycles[e.to] = 1;
            }
            hasCycles[e.to] |= hasCycles[e.from];
        }
        if (!isUpdated)
            break;
    }
    if (hasCycles[tar])
        return -1;
    return dis[tar];
}
ll Fdis[500][500], nxt[505][505];
void init_floyed()
{
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (i == j)
                continue;
            Fdis[i][j] = INF;
        }
    }
}
void floyd_warshall()
{ // dp algorithm
    for (int k = 0; k < n; k++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (Fdis[u][v] > Fdis[u][k] + Fdis[k][v])
                    Fdis[u][v] = Fdis[u][k] + Fdis[k][v], nxt[u][v] = nxt[u][k];
}

//...
vector<vector<ll>> anc, graph, mx, mn;
vector<ll> dpth;
map<pair<ll, ll>, ll> cost;
ll n, m, x, y, c, q;
void init()
{
    m = ll(ceil(log2(n)));
    anc = vector<vector<ll>>(n + 1, vector<ll>(m + 1));
    mx = vector<vector<ll>>(n + 1, vector<ll>(m + 1));
    mn = vector<vector<ll>>(n + 1, vector<ll>(m + 1, INF));
    graph = vector<vector<ll>>(n + 1);
    dpth = vector<ll>(n + 1);
}
void dfs(ll i, ll p)
{
    for (ll &child : graph[i])
    {
        if (child == p)
            continue;
        dpth[child] = dpth[i] + 1;
        anc[child][0] = i;
        mn[child][0] = mx[child][0] = cost[{child, i}];
        for (ll j = 1; j < m; j++)
        {
            anc[child][j] = anc[anc[child][j - 1]][j - 1];
            mx[child][j] = max(mx[child][j - 1], mx[anc[child][j - 1]][j - 1]);
            mn[child][j] = min(mn[child][j - 1], mn[anc[child][j - 1]][j - 1]);
        }
        dfs(child, i);
    }
}
pair<ll, pair<ll, ll>> k_anc(ll u, ll k)
{
    ll mxval = 0, mnVal = INF;
    for (ll i = 0; i < m; i++)
    {
        if (k & (1LL << i))
        {
            mxval = max(mxval, mx[u][i]);
            mnVal = min(mnVal, mn[u][i]);
            u = anc[u][i];
        }
    }
    return {u, {mxval, mnVal}};
}
pair<ll, pair<ll, ll>> lca(ll u, ll v)
{
    if (dpth[u] < dpth[v])
        swap(u, v);
    ll k = dpth[u] - dpth[v];
    auto kth = k_anc(u, k);
    u = kth.first;
    ll mxVAl = 0;
    ll mnVal = INF;
    if (u == v)
        return kth;
    for (ll i = m - 1; i >= 0; i--)
    {
        if (anc[v][i] != anc[u][i])
        {
            mxVAl = max(mxVAl, mx[u][i]);
            mxVAl = max(mxVAl, mx[v][i]);
            mnVal = min(mnVal, mn[u][i]);
            mnVal = min(mnVal, mn[v][i]);
            u = anc[u][i];
            v = anc[v][i];
        }
    }
    mxVAl = max(mxVAl, mx[u][0]);
    mxVAl = max(mxVAl, mx[v][0]);
    mnVal = min(mnVal, mn[u][0]);
    mnVal = min(mnVal, mn[v][0]);
    mxVAl = max(mxVAl, kth.second.first);
    mnVal = min(mnVal, kth.second.second);
    return {anc[u][0], {mxVAl, mnVal}};
}
void start(ll rt = 1)
{
    anc[rt][0] = rt;
    dpth[rt] = 0;
    dfs(rt, -1);
}
void solve()
{
    cin >> n;
    init();
    for (ll i = 1; i < n; i++)
    {
        cin >> x >> y >> c;
        graph[x].push_back(y);
        graph[y].push_back(x);
        cost[{x, y}] = cost[{y, x}] = c;
    }
    start();
    cin >> q;
    while (q--)
    {
        cin >> x >> y;
        auto ans = lca(x, y);
        cout << ans.second.second << " " << ans.second.first << endl;
    }
} 
// euler circuit.
/*
This is an algorithm to find an Eulerian circuit in a connected graph in which every vertex has even degree.
1. Choose any vertex v and push it onto a stack. Initially all edges are unmarked.
2. While the stack is nonempty, look at the top vertex, u, on the stack. If u has an unmarked incident edge, say, to a vertex w, then push w onto the stack and mark the edge uw. On the other hand, if u has no unmarked incident edge, then pop u off the stack and print it.
                 When the stack is empty, you will have printed a sequence of vertices that correspond to an Eulerian circuit
*/


int value(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A' + 26;
    return ch - '0' + 52;
}

int n, indeg[3900], outdeg[3900];
vector<int> undirected[3900], adj[3900];
bool vis[3900];

void dfs1(int pos)
{
    for (int i = 0; i < undirected[pos].size(); ++i)
    {
        if (!vis[undirected[pos][i]])
        {
            vis[undirected[pos][i]] = true;
            dfs1(undirected[pos][i]);
        }
    }
}

bool is_connected()
{
    for (int i = 0; i < 3900; ++i)
    {
        if (!undirected[i].empty())
        {
            vis[i] = true;
            dfs1(i);
            for (int j = 0; j < 3900; ++j)
            {
                if (!undirected[j].empty() && !vis[j])
                    return false;
            }
            return true;
        }
    }
    return 0;
}

int temp_path[400002], final_path[400005], tsz, fsz;

void euler_dfs(int v)
{

    temp_path[tsz++] = v;
    while (!adj[v].empty())
    {
        int vv = adj[v].back();
        adj[v].pop_back();
        euler_dfs(vv);
    }
    final_path[fsz++] = temp_path[--tsz];
}

char schar(int val)
{
    int t = val % 62;
    if (t < 26)
        return t + 'a';
    t -= 26;
    if (t < 26)
        return t + 'A';
    t -= 26;
    return t + '0';
}

char fchar(int val)
{
    return schar(val / 62);
}

int EulerMain()
{
    // Hierholzer algorithm to find eulerian path
    scanf("%d", &n);
    char str[5];
    int src = -1;
    while (n--)
    {
        scanf("%s", str);
        int a = value(str[0]) * 62 + value(str[1]);
        int b = value(str[1]) * 62 + value(str[2]);
        undirected[a].push_back(b);
        undirected[b].push_back(a);
        outdeg[a]++;
        indeg[b]++;
        adj[a].push_back(b);
        src = a;
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 62 * 62; i++)
    {

        if (indeg[i] == 0 && outdeg[i] == 0)
            continue;

        if (indeg[i] > outdeg[i] + 1 || outdeg[i] > indeg[i] + 1)
        {
            printf("NO");
            return 0;
        }

        if (indeg[i] > outdeg[i])
            cnt1++;
        if (indeg[i] < outdeg[i])
        {
            cnt2++;
            src = i;
        }
    }

    if ((cnt1 == cnt2 && cnt1 == 0) || (cnt1 == cnt2 && cnt1 == 1))
    {

        if (!is_connected())
        {
            printf("NO");
            return 0;
        }

        printf("YES\n");
        euler_dfs(src);

        reverse(final_path, final_path + fsz);
        printf("%c", fchar(final_path[0]));
        for (int i = 0; i < fsz; i++)
            printf("%c", schar(final_path[i]));
        return 0;
    }

    printf("NO");
    return 0;
}
