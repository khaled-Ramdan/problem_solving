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
	for (int i = 1;i*i < n;i++)if (n % i == 0)ans.push_back(i), ans.push_back(n / i);
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
bool is_prime(int n) {
	if (n == 2)return true;
	if (n == 1 or not(n%2))return false;
	for (int i = 3;i * i <= n;i +=2)if (!(n % i))return false;
	return true;
}
//git prime numbers from one to n in time O(n*log(log(n))) nearly = O(n)
vector<long long> sevie(long long n) {
	vector<bool>state(n+1, 1);
	vector<long long>result;
	state[0] = state[1] = 0;
	for (long long i = 2;i <= n;i++) {
		if (state[i]) {
			//push value in result vector
			result.push_back(i);
			//make all multipliers equal zero for this number starting from its squared value
			for (long long j = i * i;j <= n;j += i)state[j] = false;//time complexity log(log(n))
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
