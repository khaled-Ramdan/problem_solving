#include<bits\stdc++.h>
using namespace std;
#define W int g; cin>>g;while(g--)
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
int main() {
	long long n;
	W{
	cin >> n;
	vector<long long>a = sevie(n);
	copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	}
	return 0; 
}
