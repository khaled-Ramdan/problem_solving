#include<bits\stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
const long long N = 1e5 + 0, MOD = 1e9 + 7;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
int l,r;
//generating subsets >>>>> there are two ways:(recursive - bitmasks)
//1- search with recusive way
int n=5;//vector size
vector<int>subset,base;
void search(int k){
	if(k==n){
		//process on subset
		for(int i=0;i<subset.size();i++)cout<<subset[i]<<" ";cout<<endl;
	}
	else{
		//do => push => do => pop
		search(k+1);
		subset.push_back(base[k]);//base[k]
		search(k+1);
		subset.pop_back();
	}
}
//2- search with bits
void search_with_bits(vector<ll>a){
	for(int i=0;i< (1<<n);i++){
		vector<ll>subset;
		for(int j=0 ;j<n;j++){
			if(i&(1<<j)){
				cout<< a[j]<<" ";
			}
		}
		cout<<endl;
	}
}
//generating permutation => O(n!) 
// method one =>recursion
vector<int>permutation,chosen;
void generate_permutaion() {
	if (permutation.size() == n) {
		// process permutation
		for(int i=0;i<permutation.size();i++)cout<<permutation[i]+1<<" ";
		cout<<endl;
	} 
	else {
		for (int i = 0; i < n; i++) {
			if (chosen[i]) continue;
			chosen[i] = true;
			permutation.push_back(i);
			generate_permutaion();
			chosen[i] = false;		
			permutation.pop_back();
		}
	}
}
//method two => next permutaion function
void generate_permutaion2(){
	for (int i = 0; i < n; i++) {
		permutation.push_back(i+1);
	}
	do {
		// process permutation
		for(int i=0;i<n;i++)cout<<permutation[i]<<" ";
		cout<<endl;
	} while (next_permutation(permutation.begin(),permutation.end()));
}
void solve() {
	base.resize(n);
	chosen.resize(n);
	for(int i=0;i<n;i++)base[i]=i+1;
	//search_with_bits(vector<ll>(base.begin(),base.end()));
	generate_permutaion2();
}
int main() {
	IO;
	FIO
	solve();
	return 0;
}
