#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<int> inDegree;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        inDegree.resize(V, 0);
    }

    void addEdge(int v1, int v2) {
        adj[v1].push_back(v2);
        inDegree[v2]++;
    }

    void topologicalSort() {
        queue<int> q;
        vector<int> result;

        for(int i = 0; i < V; i++) {
            if(inDegree[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            result.push_back(curr);

            for(int next : adj[curr]) {
                inDegree[next]--;
                if(inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        if(result.size() != V) {
            cout << "사이클이 존재합니다.\n";
            return;
        }

        for(int v : result) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cout << "정점의 수와 간선의 수를 입력하세요: ";
    cin >> N >> M;

    Graph g(N);
    
    cout << "간선 정보를 입력하세요 (각 줄에 출발 정점과 도착 정점): \n";
    for(int i = 0; i < M; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g.addEdge(v1-1, v2-1);
    }

    cout << "위상 정렬 결과: ";
    g.topologicalSort();

    return 0;
}