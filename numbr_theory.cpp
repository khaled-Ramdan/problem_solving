#include<bits\stdc++.h>
using namespace std;
typedef long long ll;
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
