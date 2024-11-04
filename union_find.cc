#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
   vector<int> parent;
   vector<int> rank;
   vector<int> size;

public:
   UnionFind(int n) {
       parent.resize(n);
       rank.resize(n, 0);
       size.resize(n, 1);
       for(int i = 0; i < n; i++) {
           parent[i] = i;
       }
   }

   int find(int x) {
       if(parent[x] == x) return x;
       return parent[x] = find(parent[x]);
   }

   void unite(int x, int y) {
       x = find(x);
       y = find(y);
       
       if(x == y) return;
       
       if(rank[x] < rank[y]) swap(x, y);
       parent[y] = x;
       size[x] += size[y];
       
       if(rank[x] == rank[y]) rank[x]++;
   }

   bool same(int x, int y) {
       return find(x) == find(y);
   }

   int getSize(int x) {
       return size[find(x)];
   }
};

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n, m;
   cin >> n >> m;
   
   UnionFind uf(n);
   
   for(int i = 0; i < m; i++) {
       int op, a, b;
       cin >> op >> a >> b;
       a--; b--;
       
       if(op == 0) {
           uf.unite(a, b);
       } else {
           cout << (uf.same(a, b) ? "YES\n" : "NO\n");
       }
   }
   
   return 0;
}