// Maximum Flow

// 1. Dinic
#include <bits/stdc++.h>
using namespace std;
const int MAX = 505;
const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev;
    Edge(int to, int cap, int rev) : to(to), cap(cap), flow(0), rev(rev) {}
};

vector<Edge> graph[MAX];
int level[MAX], work[MAX];
int n, source, sink;

void addEdge(int from, int to, int cap) {
    graph[from].push_back(Edge(to, cap, graph[to].size()));
    graph[to].push_back(Edge(from, 0, graph[from].size()-1));
}

bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(source);
    level[source] = 0;
    
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for(Edge& e : graph[cur]) {
            if(level[e.to] == -1 && e.cap - e.flow > 0) {
                level[e.to] = level[cur] + 1;
                q.push(e.to);
            }
        }
    }
    return level[sink] != -1;
}

int dfs(int cur, int flow) {
    if(cur == sink) return flow;
    
    for(int& i = work[cur]; i < graph[cur].size(); i++) {
        Edge& e = graph[cur][i];
        
        if(level[e.to] == level[cur] + 1 && e.cap - e.flow > 0) {
            int df = dfs(e.to, min(flow, e.cap - e.flow));
            if(df > 0) {
                e.flow += df;
                graph[e.to][e.rev].flow -= df;
                return df;
            }
        }
    }
    return 0;
}

int maxFlow() {
    int ret = 0;
    while(bfs()) {
        memset(work, 0, sizeof(work));
        while(1) {
            int flow = dfs(source, INF);
            if(flow == 0) break;
            ret += flow;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    source = 0;
    sink = n-1;
    
    int m;
    cin >> m;
    
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }
    
    cout << maxFlow() << '\n';
    return 0;
}

// 2. MCMF

// #include <bits/stdc++.h>
// using namespace std;
// const int MAX = 505;
// const int INF = 1e9;

// struct Edge {
//     int to, cap, cost, flow, rev;
//     Edge(int to, int cap, int cost, int rev) : 
//         to(to), cap(cap), cost(cost), flow(0), rev(rev) {}
// };

// vector<Edge> graph[MAX];
// int dist[MAX], prev[MAX], previdx[MAX];
// bool inQ[MAX];
// int n, source, sink;

// void addEdge(int from, int to, int cap, int cost) {
//     graph[from].push_back(Edge(to, cap, cost, graph[to].size()));
//     graph[to].push_back(Edge(from, 0, -cost, graph[from].size()-1));
// }

// pair<int,int> mcmf() {
//     int mflow = 0, mcost = 0;
    
//     while(1) {
//         fill(dist, dist + MAX, INF);
//         fill(inQ, inQ + MAX, false);
//         fill(prev, prev + MAX, -1);
        
//         queue<int> q;
//         q.push(source);
//         dist[source] = 0;
//         inQ[source] = true;
        
//         while(!q.empty()) {
//             int cur = q.front();
//             q.pop();
//             inQ[cur] = false;
            
//             for(int i = 0; i < graph[cur].size(); i++) {
//                 Edge& e = graph[cur][i];
                
//                 if(e.cap - e.flow > 0 && dist[e.to] > dist[cur] + e.cost) {
//                     dist[e.to] = dist[cur] + e.cost;
//                     prev[e.to] = cur;
//                     previdx[e.to] = i;
                    
//                     if(!inQ[e.to]) {
//                         q.push(e.to);
//                         inQ[e.to] = true;
//                     }
//                 }
//             }
//         }
        
//         if(prev[sink] == -1) break;
        
//         int flow = INF;
//         for(int i = sink; i != source; i = prev[i]) {
//             Edge& e = graph[prev[i]][previdx[i]];
//             flow = min(flow, e.cap - e.flow);
//         }
        
//         for(int i = sink; i != source; i = prev[i]) {
//             Edge& e = graph[prev[i]][previdx[i]];
//             e.flow += flow;
//             graph[e.to][e.rev].flow -= flow;
//             mcost += e.cost * flow;
//         }
        
//         mflow += flow;
//     }
    
//     return {mflow, mcost};
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tieO(nullptr);
    
//     cin >> n;
//     source = 0;
//     sink = n-1;
    
//     int m;
//     cin >> m;
    
//     for(int i = 0; i < m; i++) {
//         int u, v, cap, cost;
//         cin >> u >> v >> cap >> cost;
//         addEdge(u, v, cap, cost);
//     }
    
//     auto [flow, cost] = mcmf();
//     cout << flow << ' ' << cost << '\n';
    
//     return 0;
// }