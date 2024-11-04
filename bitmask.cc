#include <bits/stdc++.h>
using namespace std;

class BitSet {
private:
   int bits;
   
public:
   BitSet() : bits(0) {}
   
   void add(int x) {
       bits |= (1 << x);
   }
   
   void remove(int x) {
       bits &= ~(1 << x);
   }
   
   void toggle(int x) {
       bits ^= (1 << x);
   }
   
   bool contains(int x) {
       return bits & (1 << x);
   }
   
   int count() {
       return __builtin_popcount(bits);
   }
   
   void print() {
       for(int i = 0; i < 32; i++) {
           if(contains(i)) cout << i << " ";
       }
       cout << "\n";
   }
   
   void printAllSubsets() {
       for(int subset = bits; subset; subset = (subset-1) & bits) {
           for(int i = 0; i < 32; i++) {
               if(subset & (1 << i)) cout << i << " ";
           }
           cout << "\n";
       }
   }
   
   void unionSet(const BitSet& other) {
       bits |= other.bits;
   }
   
   void intersectSet(const BitSet& other) {
       bits &= other.bits;
   }
   
   void differenceSet(const BitSet& other) {
       bits &= ~other.bits;
   }
   
   int getMin() {
       if(bits == 0) return -1;
       return __builtin_ctz(bits);
   }
   
   int getMax() {
       if(bits == 0) return -1;
       return 31 - __builtin_clz(bits);
   }
};

int n;
vector<vector<int>> dist;
vector<vector<int>> dp;

int tsp(int cur, int visited) {
   if(visited == (1 << n) - 1) {
       return dist[cur][0];
   }
   
   int& ret = dp[cur][visited];
   if(ret != -1) return ret;
   
   ret = 1e9;
   for(int next = 0; next < n; next++) {
       if(visited & (1 << next)) continue;
       ret = min(ret, dist[cur][next] + tsp(next, visited | (1 << next)));
   }
   
   return ret;
}

class BitUtils {
public:
   static int lsb(int x) {
       return x & -x;
   }
   
   static int turnOffLsb(int x) {
       return x & (x-1);
   }
   
   static int turnOnLsb(int x) {
       return x | (x+1);
   }
   
   static int countBits(int x) {
       return __builtin_popcount(x);
   }
   
   static int lowestBitPos(int x) {
       return __builtin_ctz(x);
   }
   
   static int highestBitPos(int x) {
       return 31 - __builtin_clz(x);
   }
};

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   BitSet set;
   set.add(1);
   set.add(3);
   set.add(5);
   
   cout << "Current set: ";
   set.print();
   cout << "Contains 3? " << set.contains(3) << "\n";
   cout << "Element count: " << set.count() << "\n";
   
   set.remove(3);
   cout << "After removing 3: ";
   set.print();
   
   cin >> n;
   dist.resize(n, vector<int>(n));
   dp.resize(n, vector<int>(1<<n, -1));
   
   for(int i = 0; i < n; i++) {
       for(int j = 0; j < n; j++) {
           cin >> dist[i][j];
       }
   }
   
   cout << "TSP cost: " << tsp(0, 1) << "\n";
   
   int x = 52;
   cout << "Number: " << x << "\n";
   cout << "Lowest set bit: " << BitUtils::lsb(x) << "\n";
   cout << "After turning off LSB: " << BitUtils::turnOffLsb(x) << "\n";
   cout << "Bit count: " << BitUtils::countBits(x) << "\n";
   cout << "Lowest bit position: " << BitUtils::lowestBitPos(x) << "\n";
   cout << "Highest bit position: " << BitUtils::highestBitPos(x) << "\n";
   
   return 0;
}