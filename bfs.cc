// 1. BFS

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
vector<int> graph[MAX];
bool visited[MAX];
int n, m;

void bfs(int start) {
   queue<int> q;
   q.push(start);
   visited[start] = true;
   
   while(!q.empty()) {
       int cur = q.front();
       q.pop();
       cout << cur << ' ';
       
       for(int next : graph[cur]) {
           if(!visited[next]) {
               visited[next] = true;
               q.push(next);
           }
       }
   }
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   
   cin >> n >> m;
   for(int i = 0; i < m; i++) {
       int a, b;
       cin >> a >> b;
       graph[a].push_back(b);
       graph[b].push_back(a);
   }
   
   for(int i = 1; i <= n; i++) {
       sort(graph[i].begin(), graph[i].end());
   }
   
   bfs(1);
   return 0;
}

// 2. 0-1 BFS

// #include <bits/stdc++.h>
// using namespace std;

// const int MAX = 1001;
// const int INF = 1e9;
// vector<pair<int,int>> graph[MAX];
// int dist[MAX];
// bool in_queue[MAX];
// int n, m;

// void bfs_01(int start) {
//     deque<int> dq;
//     fill(dist, dist + MAX, INF);
    
//     dist[start] = 0;
//     dq.push_front(start);
//     in_queue[start] = true;
    
//     while(!dq.empty()) {
//         int cur = dq.front();
//         dq.pop_front();
//         in_queue[cur] = false;
        
//         for(auto [next, cost] : graph[cur]) {
//             if(dist[next] > dist[cur] + cost) {
//                 dist[next] = dist[cur] + cost;
                
//                 if(!in_queue[next]) {
//                     if(cost == 0) {
//                         dq.push_front(next);
//                     } else {
//                         dq.push_back(next);
//                     }
//                     in_queue[next] = true;
//                 }
//             }
//         }
//     }
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
    
//     cin >> n >> m;
//     for(int i = 0; i < m; i++) {
//         int a, b, cost;
//         cin >> a >> b >> cost;
//         graph[a].push_back({b, cost});
//         graph[b].push_back({a, cost});
//     }
    
//     bfs_01(1);
    
//     for(int i = 1; i <= n; i++) {
//         if(dist[i] == INF) cout << -1 << ' ';
//         else cout << dist[i] << ' ';
//     }
    
//     return 0;
// }