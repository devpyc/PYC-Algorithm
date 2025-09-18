// Miller-Rabin + Follard-Rho
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll mul(ll x, ll y, ll m) {
   ll ret = 0;
   while(y > 0) {
       if(y & 1) ret = (ret + x) % m;
       x = (x + x) % m;
       y >>= 1;
   }
   return ret;
}

ll pow(ll x, ll y, ll m) {
   ll ret = 1;
   x %= m;
   while(y > 0) {
       if(y & 1) ret = mul(ret, x, m);
       x = mul(x, x, m);
       y >>= 1;
   }
   return ret;
}

bool isPrime(ll n, vector<ll>& a) {
   if(n <= 1) return false;
   for(ll i = 0; i < a.size() && a[i] < n; i++) {
       if(n % a[i] == 0) return n == a[i];
   }
   
   ll d = n-1;
   while(!(d & 1)) d >>= 1;
   
   bool ok = true;
   for(ll i = 0; i < a.size() && a[i] < n && ok; i++) {
       ll cur = pow(a[i], d, n);
       if(cur == 1 || cur == n-1) continue;
       ok = false;
       for(ll r = 1; r < 63; r++) {
           cur = mul(cur, cur, n);
           if(cur == n-1) {
               ok = true;
               break;
           }
       }
   }
   return ok;
}

ll gcd(ll a, ll b) {
   return b ? gcd(b, a%b) : a;
}

ll pollard_rho(ll n) {
   if(n % 2 == 0) return 2;
   if(isPrime(n, {2,3,5,7,11,13,17,19,23,29,31,37})) return n;
   
   ll x = rand()%(n-2) + 2;
   ll y = x;
   ll c = rand()%(n-1) + 1;
   ll d = 1;
   
   while(d == 1) {
       x = (mul(x, x, n) + c) % n;
       y = (mul(y, y, n) + c) % n;
       y = (mul(y, y, n) + c) % n;
       d = gcd(abs(x-y), n);
       if(d == n) return pollard_rho(n);
   }
   if(isPrime(d, {2,3,5,7,11,13,17,19,23,29,31,37})) return d;
   return pollard_rho(d);
}

vector<ll> factorize(ll n) {
   vector<ll> ret;
   while(n > 1) {
       ll f = pollard_rho(n);
       ret.push_back(f);
       n /= f;
   }
   sort(ret.begin(), ret.end());
   return ret;
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int t;
   cin >> t;
   
   while(t--) {
       ll n;
       cin >> n;
       
       vector<ll> bases = {2,3,5,7,11,13,17,19,23,29,31,37};
       if(isPrime(n, bases)) {
           cout << n << " is prime\n";
       } else {
           cout << n << " is not prime\n";
           
           vector<ll> factors = factorize(n);
           cout << "Factors: ";
           for(ll f : factors) {
               cout << f << " ";
           }
           cout << "\n";
           
           map<ll, int> cnt;
           for(ll f : factors) cnt[f]++;
           
           cout << "Prime factorization: ";
           for(auto [p, e] : cnt) {
               cout << p;
               if(e > 1) cout << "^" << e;
               cout << " ";
           }
           cout << "\n";
       }
       cout << "\n";
   }
   
   return 0;
}