// Bellman-Ford
#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

struct Edge {
    int from, to, cost;
};

const int MAX = 501;
vector<Edge> edges;
long long dist[MAX];
int N, M;

bool bellmanFord(int start) {
    fill(dist, dist + MAX, INF);
    dist[start] = 0;
    
    for(int i = 1; i <= N; i++) {
        for(Edge edge : edges) {
            if(dist[edge.from] != INF && 
               dist[edge.to] > dist[edge.from] + edge.cost) {
                dist[edge.to] = dist[edge.from] + edge.cost;
                if(i == N) return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> M;
    
    for(int i = 0; i < M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges.push_back({from, to, cost});
    }
    
    bool hasCycle = bellmanFord(1);
    
    if(hasCycle) cout << "Negative cycle exists\n";
    else {
        for(int i = 1; i <= N; i++) {
            if(dist[i] == INF) cout << "INF\n";
            else cout << dist[i] << '\n';
        }
    }
    return 0;
}