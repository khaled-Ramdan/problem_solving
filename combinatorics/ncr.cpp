#define _CRT_SECURE_NO_WARNINGS
/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W int g; cin >> g; while (g--)
#define sz(v) int(v.size())
#define FIO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
typedef long long ll;
const long long N = 5e5 + 5, Mod = 998244353, INF = 1e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };

struct Com {
	vector<ll>fc; int n; ll MOD;
	Com(int n = 1e6, ll Mod = Mod) {
		this->n = n;
		MOD = Mod;
		fc.assign(n, 0);
		factClc();
	}
	void factClc() {
		fc[0] = 1;
		for (int i = 1; i < n; i++)
			fc[i] = (fc[i - 1LL] % MOD * i % MOD) % MOD;
	}
	ll nCr(ll n, ll r) {
		return (fc[n] * inv(fc[r] * fc[n - r] % MOD) + MOD) % MOD;
	}
	ll getC(ll n, int r)	//only for small range ==> can overflow
	{
		if (r > n) return 0;
		ll res = 1;
		for (int i = 0; i < r; i++)
		{
			res *= n - i;
			res /= i + 1;
		}
		return res;
	}
	ll modpow(ll base, ll pow) {
		if (pow == 0)return 1 % MOD;
		ll u = modpow(base, pow / 2);
		u = (u * u) % MOD;
		if (pow % 2 == 1)u = (u * base) % MOD;
		return u;
	}
	ll add(ll a, ll b) {
		return ((a % MOD + b % MOD) % MOD + MOD) % MOD;
	}
	ll mul(ll a, ll b) {
		return ((a % MOD * b % MOD) % MOD + MOD) % MOD;
	}
};






//calculate until 1000*1000 in O(1)
//calculate until 1000*1000 in O(1)
struct combination {
	vector<vector<ll>>C;
	int n;
	combination(int n = 1001, ll Mod = Mod) {
		this->n = n;
		C = vector<vector<ll>>(n, vector<ll>(n));
		init();
	}
	void init() {
		C[0][0] = 1;
		for (int i = 1; i < n; i++) {
			C[i][0] = C[i][i] = 1;
			for (int j = 1; j < i; j++)
				C[i][j] = (C[i - 1][j] % Mod + C[i - 1][j - 1] % Mod) % Mod;
		}
	}
	ll nCr(ll n, ll r) {
		return C[n][r];
	}
};
//calculate until 1e6 in O(log(n))
//can calculate in O(1) if Mod is smaller than 1e6
struct comb {
	vector<ll>fc, invfc, fib, dr;
	int n;
	ll MOD;
	comb(int n = 1e6, ll Mod = Mod) {
		this->n = n;
		MOD = Mod;
		fc.assign(n, 0);
		fib.assign(n, 0);
		dr.assign(n, 0);
		invfc.assign(n, 0);
		factClc();
		//inverseClc(); //can only be used if MOD < 1e6
	}
	void factClc() {
		fc[0] = 1;
		for (int i = 1; i < n; i++)
			fc[i] = (fc[i - 1LL] % MOD * i % MOD) % MOD;
	}
	void inverseClc() {
		invfc[1] = 1;
		for (int i = 2; i < MOD; i++)
			invfc[i] = MOD - (MOD / i) * invfc[MOD % i] % MOD;
	}
	ll nCr(ll n, ll r) {
		return (fc[n] * inv(fc[r] * fc[n - r] % MOD) + MOD) % MOD;
	}
	ll nCrFast(ll n, ll r) {

		return (fc[n] * invfc[fc[r]] % MOD * invfc[fc[n - r]] % MOD + MOD) % MOD;
	}
	//only for small range ==> can overflow
	ll getC(ll n, int r)
	{
		if (r > n) return 0;
		ll res = 1;
		for (int i = 0; i < r; i++)
		{
			res *= n - i;
			res /= i + 1;
		}
		return res;
	}
	ll modpow(ll base, ll pow) {
		if (pow == 0)return 1 % MOD;
		ll u = modpow(base, pow / 2);
		u = (u * u) % MOD;
		if (pow % 2 == 1)u = (u * base) % MOD;
		return u;
	}
	ll add(ll a, ll b) {
		return ((a % MOD + b % MOD) % MOD + MOD) % MOD;
	}
	ll mul(ll a, ll b) {
		return ((a % MOD * b % MOD) % MOD + MOD) % MOD;
	}
	void derrangement() {
		dr[0] = 1;
		dr[1] = 0;
		for (int i = 2; i < n; i++)
			dr[i] = mul((i - 1LL), add(dr[i - 1], dr[i - 2]));
	}
	void fibonacci() {
		fib[0] = 1;
		fib[1] = 2;
		for (int i = 2; i < n; i++)
			fib[i] = add(fib[i - 1] , fib[i - 2]);
	}
};


int main()
{
	IO;
	comb c;
	combination cc;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j <= i; j++) {
			cout << (cc.nCr(i, j) != c.nCr(i, j)) << endl; 
		}
	}
	return 0;
}
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
*/
