#include<bits\stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<ll, ll>>generate_divisors(ll n) {//generate two numbers there product equal n
	vector<pair<ll, ll>>ans;
	for (ll i = 1;i * i <= n;i++)
		if (n % i == 0)ans.push_back({ i,n / i });
	return ans;
}
vector<ll>divisors(ll n) {//get all divisors of n
	vector<ll>ans;
	for (ll i = 1;i*i < n;i++)if (n % i == 0)ans.push_back(i), ans.push_back(n / i);
	if (ll(sqrt(n)) * ll(sqrt(n)) == n)ans.push_back(ll(sqrt(n)));
	return ans;
}
map<ll, ll> factors(ll n) {//get the prime factors of an integer n
	map<ll, ll>a;
	for (ll i = 2;i * i <= n;i++) {
		while (n % i == 0)
		{
			a[i]++;
			n /= i;
		}
	}
	if (n > 1)a[n]++;
	return a;
}
ll rangeFactorization1(ll n) {//get sum of number of divisors for each number from one to n
	//forward thinking
	ll sum = 0;
	for (int i = 1;i <= n;i++)sum += divisors(i).size();
	return sum;
}
ll rangeFactorization2(ll n) {//get sum of number of divisors for each number from one to n
	//backward thinking 
	vector<ll>numOfFactors(n + 1);
	for (int i = 1;i <= n;i++)
		for (int j = i;j <= n;j += i)numOfFactors[j]++;
	//git num of factors for each element from one to n
	ll sum = 0;
	for (int i = 0;i < n;i++)sum += numOfFactors[i];
	return sum;
}
//get the greatest common divisor of two numbers
ll gcd(ll a, ll b) {// Euclid's algorithm
	return (not b ? a : gcd(b, a % b));
}
// get the least common multipule of two numbers 
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}
/*
* note that gcd(a,b)*lcm(a,b)==a*b
* (x + y) mod m = (x mod m + y mod m) mod m
* (x - y) mod m = (x mod m - y mod m) mod m
* (x * y) mod m = (x mod m * y mod m) mod m
* (x**n) mod m = (x mod m)**n mod m
*/
//calculate number of coprime numbers from 1 to n
//numbers a,b are considerd coprimes if gcd(a,b)==1
ll totient(ll n) {
	ll coprimes = 1;
	auto temp = factors(n);
	for (auto& i : temp)coprimes *= ll(pow(i.first, i.second - 1)) * (i.first - 1);
	return coprimes;
	//if qutiont(n)==n-1 : n is prime
}
//get prime number in time O(.5 * sqrt(n))
bool is_prime(ll n) {
	if (n == 2)return true;
	if (n == 1 or not(n%2))return false;
	for (ll i = 3;i * i <= n;i +=2)if (!(n % i))return false;
	return true;
}
//git prime numbers from one to n in time O(n*log(log(n))) nearly = O(n)
vector<long long> sieve(long long n) {
	vector<bool>state(n+1, 1);
	vector<long long>result;
	state[0] = state[1] = 0;
	for (long long i = 2;i <= n;i++) {
		if (state[i]) {
			result.push_back(i);
			for (long long j = i * i;j <= n;j += i)state[j] = false;
		}
	}
	return result;
}
//get the power more efficiently in therms of MOD
ll modpow(ll base,ll pow,int mod){
	if(pow==0)return 1%mod;
	ll u=modpow(base,pow/2,mod);
	u= (u*u)%mod;
	if(pow%2==1)u=(u*base)%mod;
	return u;
}

///.........................................................................modoular division
// C++ function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y);
 
// Function to find modulo inverse of b. It returns
// -1 when inverse doesn't
int modInverse(int b, int m)
{
    int x, y; // used in extended GCD algorithm
    int g = gcdExtended(b, m, &x, &y);
 
    // Return -1 if b and m are not co-prime
    if (g != 1)
        return -1;
 
    // m is added to handle negative x
    return (x%m + m) % m;
}
 
// Function to compute a/b under modulo m
int modDivide(int a, int b, int m)
{
    a = a % m;
    int inv = modInverse(b, m);
    return (inv * a) % m;
}
 
// C function for extended Euclidean Algorithm (used to
// find modular inverse.
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

//.........................................................another impl...........
LL f[maxn];
long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
  if(a==0&&b==0) return -1;
  if(b==0){x=1;y=0;return a;}
  long long d=extend_gcd(b,a%b,y,x);
  y-=a/b*x;
  return d;
}
long long mod_reverse(long long a,long long n)
{
  long long x,y;
  long long d=extend_gcd(a,n,x,y);
  if(d==1) return (x%n+n)%n;
  else return -1;
}
 
ll C(ll n, ll m,ll Mod)
{
  long long A = f[n];
  long long B = f[n - m] * f[m] % Mod;
  long long C = mod_reverse(B, Mod);
  return ((A * C % Mod)+Mod)%Mod;
}


// count number of integers divisble by x not y in a range from 1 to  N 
ll countDivibleByXNotY(ll X, ll Y, ll N)
{
	ll divisibleByX = N / X;
	ll divisibleByY = N / Y;
	ll LCM = (X * Y) / gcd(X, Y);
	ll divisibleByLCM = N / LCM;
	ll divisibleByXorY = divisibleByX + divisibleByY - divisibleByLCM;
	ll divisibleByXnotY = divisibleByXorY - divisibleByY;
	return divisibleByXnotY;
}



///...............Smallest prime Factor............
//smallest prime factor
const int N= 1e6;
int p[N];
void spf() {
	for (int i = 2; i < N; i++) {
		if (p[i])continue;
		for (ll j = i; j < N; j += i)
			if(!p[j])
			   p[j] = i;
	}
}
map<ll, ll> factors(ll n) {
	map<ll, ll>ret;
	while (n > 1)
	{
		ll spf = p[n];
		while (n % spf == 0) {
			ret[spf]++;
			n /= spf;
		}
	}
	return ret;
}
///.............. extended GCD
/*
    representation of gcd(a, b) in form of a*x + b *y = gcd(a, b)
    x => is the multiplication inverse of a % b
*/
int extended_gcd(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1)
    {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
int rec_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = rec_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

/*
for [a*x + b*y = c]. find any solution where g is gcd(a, b)
if c is multiple of gcd(a, b) => there is a solution where for a*x + b*y = c.
otherwise, no solution
*/
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g)
{
    g = rec_gcd(abs(a), abs(b), x0, y0);
    if (c % g)
    {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0)
        x0 = -x0;
    if (b < 0)
        y0 = -y0;
    return true;
}


/*
the solution for x+y is minimum possible => 
use the information in shift_solution from all possible solutions. 
If a < b , we need to select smallest possible value of  cnt.
If a > b , we need to select the largest possible value of  cnt .
If  a = b , all solution will have the same sum x + y.

OR => just get min sum when shift_solution is called every time
*/
int mnsum = 1e9 + 7, xmnsm = 0, ymnsm = 0;
void shift_solution(int &x, int &y, int a, int b, int cnt)
{
    if (mnsum > x + y)
    {
        mnsum = x + y;
        xmnsm = x, ymnsm = y;
    }
    x += cnt * b;
    y -= cnt * a;
    if (mnsum > x + y)
    {
        mnsum = x + y;
        xmnsm = x, ymnsm = y;
    }
    cout << x << " " << y << " " << cnt << endl;
}

/*
the function gets the number of solutions in a range for x and y
*/
int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy)
{
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);

    if (x < minx)
        shift_solution(x, y, a, b, sign_b);

    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);

    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);

    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);

    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);

    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);

    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);

    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}
//.... Mobius function 
/*
    Mobius function:
            m(1) = 1
            m(n) = 1 if n is a square free positive integer + Even number of prime factors  => m(2*3*5*7) = 1
            m(n) = -1 if n is a square free positive integer + Odd number of prime factors  => m (2*3*5) = -1
            m(n) = 0 if n is NOT a square free integer => m(2*3*3*7) = 0

    M(n) = 1, -1, -1, 0, -1, 1, -1, 0, 0, 1, -1, 0, -1, 1
    M(n) + 1 = 2, 0, 0, 1, 0, 2, 0, 1, 1, 2, 0, 1, 0, 2
*/
ll mobius(ll n)
{
    ll mebVal = 1;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (n % (i * i) == 0)
                return 0;
            n /= i;
            mebVal *= -1;
        }
    }
    if (n)
        mebVal *= -1;
    return mebVal;
}
// generate the mobius for elements in range from 1 to n.
vector<int> mobius_generator(int n)
{
    vector<int> mobius(n + 1, -1);
    vector<bool> prime(n + 1, 1);

    mobius[1] = 1, prime[1] = 0;

    for (int i = 2; i <= n; i++)
    {
        if (!prime[i])
            continue;
        mobius[i] = -1;
        for (int j = i * i; j <= n; j += i)
        {
            prime[j] = 0;
            mobius[j] = j % (i * i) == 0 ? 0 : -mobius[j];
        }
    }
    return mobius;
}
int kth_square_free(int k, int n)
{
    auto mob = mobius_generator(n);
    vector<int> v(n);
    for (int i = 1; i <= n; i++)
        v[i] = mob[i] != 0;
    for (int i = 2; i <= n; i++)
        v[i] += v[i - 1];
    return v[k];
}
// count triples (a, b, c) where a, b, c <= n and gcd(a, b,c) = 1
ll coprime_triples(ll n)
{
    auto mobius = mobius_generator(n);
    ll sum = 0;
    for (ll i = 2; i <= n; i++)
    {
        sum -= mobius[i] * (n / i) * (n / i) * (n / i);
    }
    return sum;
}
ll square_free_index(ll val, int n)
{
    auto mobius = mobius_generator(n);
    ll idx = val;
    for (ll i = 2; i * i <= val; i++)
        idx += mobius[i] * (val / (i * i));

    return idx;
}
