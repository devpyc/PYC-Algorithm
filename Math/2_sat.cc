#include <bits/stdc++.h>
using namespace std;

class TwoSAT {
private:
   int n;
   vector<vector<int>> adj;
   vector<vector<int>> radj;
   vector<bool> visited;
   vector<int> order, sccId;
   int sccCounter;
   
   void dfs(int here) {
       visited[here] = true;
       for(int there : adj[here])
           if(!visited[there])
               dfs(there);
       order.push_back(here);
   }
   
   void reverseDfs(int here) {
       visited[here] = true;
       sccId[here] = sccCounter;
       for(int there : radj[here])
           if(!visited[there])
               reverseDfs(there);
   }
   
public:
   TwoSAT(int _n) : n(_n) {
       adj.resize(2*n);
       radj.resize(2*n);
   }
   
   int neg(int x) {
       return x >= n ? x-n : x+n;
   }
   
   void addClause(int x, int y) {
       adj[neg(x)].push_back(y);
       adj[neg(y)].push_back(x);
       radj[y].push_back(neg(x));
       radj[x].push_back(neg(y));
   }
   
   vector<bool> solve() {
       visited = vector<bool>(2*n, false);
       order.clear();
       
       for(int i = 0; i < 2*n; i++)
           if(!visited[i])
               dfs(i);
       
       reverse(order.begin(), order.end());
       visited = vector<bool>(2*n, false);
       sccId = vector<int>(2*n, -1);
       sccCounter = 0;
       
       for(int x : order)
           if(!visited[x]) {
               reverseDfs(x);
               sccCounter++;
           }
       
       for(int i = 0; i < n; i++)
           if(sccId[i] == sccId[i+n])
               return vector<bool>();
       
       vector<bool> result(n);
       for(int i = 0; i < n; i++)
           result[i] = sccId[i] > sccId[i+n];
       return result;
   }
};

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n, m;
   cin >> n >> m;
   
   TwoSAT sat(n);
   
   while(m--) {
       int a, b;
       cin >> a >> b;
       if(a > 0) a--;
       else a = (-a-1) + n;
       if(b > 0) b--;
       else b = (-b-1) + n;
       sat.addClause(a, b);
   }
   
   vector<bool> result = sat.solve();
   
   if(result.empty()) {
       cout << "0\n";
   } else {
       cout << "1\n";
       for(int i = 0; i < n; i++)
           cout << result[i] << " ";
       cout << "\n";
   }
   
   return 0;
}