#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
vector<int> graph[MAX];
int matched[MAX];
bool visited[MAX];

bool dfs(int cur) {
   if (visited[cur]) return false;
   visited[cur] = true;
   
   for (int next : graph[cur]) {
       if (matched[next] == -1 || dfs(matched[next])) {
           matched[next] = cur;
           return true;
       }
   }
   return false;
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   int n, m, k;
   cin >> n >> m >> k;
   
   for (int i = 1; i <= n; i++) {
       int cnt;
       cin >> cnt;
       while (cnt--) {
           int work;
           cin >> work;
           graph[i].push_back(work);
       }
   }
   
   fill(matched, matched + MAX, -1);
   
   int match = 0;
   for (int i = 1; i <= n; i++) {
       fill(visited, visited + MAX, false);
       if (dfs(i)) match++;
   }
   
   for (int i = 1; i <= n && match < k; i++) {
       fill(visited, visited + MAX, false);
       if (dfs(i)) match++;
   }
   
   cout << match << '\n';
   
   return 0;
}