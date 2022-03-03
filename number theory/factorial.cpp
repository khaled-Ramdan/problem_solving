#include<bits\stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
const long long N = 1e5 + 0, MOD = 1e9 + 7;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
//get number of copies of a prime in a factiorial => Given n and p what is the max x such n%(p^x)==0
/* for example try to expolre 16 with the prime 2
			  1				 	  2
	  1	  	  2		   3		  2
  1	  2   3	  2   5	   2    7	  2
1 2	3 2 5 2 7 2 9 2 11 2  13 2 15 2				[Exploring 16! with p=2]

level one -> 16/2
level two -> 16/4
level tree-> 16/8
level four-> 16/16
*/
int FactN_primePower(int n,int p){//O(log n base p)   ||| n should be the factorial value
	int pow=0;
	for(int i=p;i<=n;i*=p){
		pow+=n/i;
	}
}
/*
	factorial factorization n! = p1^a * p1^b * .....
	what are possible primes in n! => n! is exponential but it consists of primes of range [1->n]
	seive on n and get all primes in range n 
	for each prime p call the fuction FactN_prime power(n,p)
*/
/*
	Given m, what is max x such that m^x divides n!?
	Again, think in prime representation.
	let's simplify, uch that m^x divides g?
	Let m =  2^3 * 5^4
	Let g =  2^10 * 5^8 * 11^3
	Then 1st we can with 2 and 5 only.
	10/3 = 3, then max for p1=2 is (2^3)^3
	8/4 =2, so max is (5^4)^2
	Then let x = min(3, 2) = 2...so m^2 divides g
	
	what if m = 2^3 * 5^4 * 7^2 ? then it doesn't divide g, and x = 0
	
	what about n!?
	Then factroize m
		for each p^x in m
			check power in n!, and follow as above

*/

void solve() {

}
int main() {
	IO;
	FIO
	solve();
	return 0;
}
