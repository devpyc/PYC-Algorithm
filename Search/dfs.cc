// DFS

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
vector<int> graph[MAX];
bool visited[MAX];
int n, m;

void dfs(int cur) {
    visited[cur] = true;
    cout << cur << ' ';
    
    for(int next : graph[cur]) {
        if(!visited[next]) {
            dfs(next);
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
    
    dfs(1);
    return 0;
}