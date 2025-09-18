// Dijkstra

#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef pair<int,int> pii;

const int MAX = 20001;
vector<pii> graph[MAX];
int dist[MAX];
int V, E, start;

void dijkstra() {
   priority_queue<pii, vector<pii>, greater<pii>> pq;
   fill(dist, dist + MAX, INF);
   
   dist[start] = 0;
   pq.push({0, start});
   
   while(!pq.empty()) {
       int cur_dist = pq.top().first;
       int cur = pq.top().second;
       pq.pop();
       
       if(dist[cur] < cur_dist) continue;
       
       for(pii next : graph[cur]) {
           int next_vertex = next.first;
           int next_dist = cur_dist + next.second;
           
           if(next_dist < dist[next_vertex]) {
               dist[next_vertex] = next_dist;
               pq.push({next_dist, next_vertex});
           }
       }
   }
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   cin >> V >> E >> start;
   
   for(int i = 0; i < E; i++) {
       int u, v, w;
       cin >> u >> v >> w;
       graph[u].push_back({v, w});
   }
   
   dijkstra();
   
   for(int i = 1; i <= V; i++) {
       if(dist[i] == INF) cout << "INF\n";
       else cout << dist[i] << '\n';
   }
   return 0;
}