#include <bits/stdc++.h>
#define ll long long
using namespace std;

class UnionFind {
private:
   vector<int> parent, rank;
public:
   UnionFind(int n) : parent(n), rank(n, 0) {
       for(int i = 0; i < n; i++) parent[i] = i;
   }
   
   int find(int u) {
       if(u == parent[u]) return u;
       return parent[u] = find(parent[u]);
   }
   
   void merge(int u, int v) {
       u = find(u); v = find(v);
       if(u == v) return;
       if(rank[u] < rank[v]) swap(u, v);
       parent[v] = u;
       if(rank[u] == rank[v]) rank[u]++;
   }
};

struct Edge {
   int u, v, w;
   Edge(int u, int v, int w) : u(u), v(v), w(w) {}
   bool operator<(const Edge& o) const { return w < o.w; }
};

ll kruskal(int V, vector<Edge>& edges) {
   sort(edges.begin(), edges.end());
   UnionFind uf(V);
   ll ret = 0;
   
   for(Edge& e : edges) {
       if(uf.find(e.u) != uf.find(e.v)) {
           uf.merge(e.u, e.v);
           ret += e.w;
       }
   }
   return ret;
}

ll prim(int V, vector<vector<pair<int,int>>>& adj) {
   vector<bool> vis(V);
   vector<int> minW(V, INT_MAX);
   priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
   
   ll ret = 0;
   minW[0] = 0;
   pq.push({0, 0});
   
   while(!pq.empty()) {
       auto [w, u] = pq.top(); pq.pop();
       if(vis[u]) continue;
       
       vis[u] = true;
       ret += w;
       
       for(auto [v, nw] : adj[u]) {
           if(!vis[v] && nw < minW[v]) {
               minW[v] = nw;
               pq.push({nw, v});
           }
       }
   }
   return ret;
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int V, E; cin >> V >> E;
   vector<Edge> edges;
   vector<vector<pair<int,int>>> adj(V);
   
   for(int i = 0; i < E; i++) {
       int u, v, w; cin >> u >> v >> w;
       u--; v--;
       edges.emplace_back(u, v, w);
       adj[u].push_back({v, w});
       adj[v].push_back({u, w});
   }
   
   cout << kruskal(V, edges) << '\n';
   cout << prim(V, adj) << '\n';
   
   return 0;
}